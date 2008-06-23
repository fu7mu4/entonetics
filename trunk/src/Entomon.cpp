#include "Entomon.hpp"

#include "Globals.hpp"

#include <iostream>

namespace ento
{

Entomon::Entomon( void )
 : Object(Object::e_Entomon),
   m_shape( sf::Shape::Circle( 0, 0, 0.5, sf::Color::Yellow ) ),
   m_input( The_Inputs->createInputer<Entomon_inputer>() ),
   m_state( Entomon::e_Falling ), m_timer(0.f),
   m_lateral_speed(100.f), m_lateral_accel(100.f)
{
   b2CircleDef circDef;
   circDef.restitution = 0.f;
   circDef.friction = 1.f;
   circDef.radius = 0.5f;
   circDef.density = 1;

   b2BodyDef bodyDef;
   bodyDef.position.Set( 20, 50 );
   bodyDef.userData = static_cast<Object*>(this);

   m_body = The_Sim->world().CreateBody(&bodyDef);
   m_body->CreateShape( &circDef );
   m_body->SetMassFromShapes();

   update( 0.f );
}

bool Entomon::
addContact( const b2ContactResult& point, b2Shape* self )
{
   m_contacts.push_back( Contact() );
   Contact& con = m_contacts.back();

   con.id.key = point.id.key;
   con.position = point.position;

   if( point.shape1 == self )
   {
      con.self = point.shape1;
      con.other = point.shape2;
      con.normal = -point.normal;
      con.tangentImpulse = -point.tangentImpulse;
   }
   else
   {
      con.self = point.shape2;
      con.other = point.shape1;
      con.normal = point.normal;
      con.tangentImpulse = point.tangentImpulse;
   }

   return true;
}

bool Entomon::
addCollision( const b2ContactPoint& point, b2Shape* self )
{
   m_contacts.push_back( Contact() );
   Contact& con = m_contacts.back();

   con.id.key = point.id.key;
   con.position = point.position;

   if( point.shape1 == self )
   {
      con.self = point.shape1;
      con.other = point.shape2;
      con.normal = -point.normal;
   }
   else
   {
      con.self = point.shape2;
      con.other = point.shape1;
      con.normal = point.normal;
   }

   return true;
}


void Entomon::
preStep( float dt )
{
   if( m_state == e_Resting && m_input->jumping() )
   {
      b2Vec2 impulse = The_Sim->getGravityNormal( getPosition() );
      impulse *= -0.25f * The_Sim->getGravityAccel( getPosition() );
      std::cout << "jump\n";
      m_body->ApplyImpulse( impulse , getPosition() );

      m_state = e_Jumping;
   }

   apply_lateral( dt );

   m_contacts.clear();
   m_collisions.clear();
}

void Entomon::
postStep( float dt )
{
   m_rest_norm.Set(0.f,0.f);
   m_resting = false;
   if( !m_contacts.empty() )
   {
      b2Vec2 g_norm = -The_Sim->getGravityNormal( m_body->GetWorldCenter() );
      unsigned found = 0;
      for( unsigned i=0; i<m_contacts.size(); ++i )
      {
         if( b2Dot( g_norm, m_contacts[i].normal ) > 0.f )
         {
            m_rest_norm += m_contacts[i].normal;
            ++found;
         }
      }
      if( found > 1 )
      {
         m_rest_norm.Normalize();
      }
      m_resting = found;
   }

   switch( m_state )
   {
      case e_Resting:
         m_shape.SetColor( sf::Color::Yellow );
         do_resting( dt );
         break;
      case e_Jumping:
         m_shape.SetColor( sf::Color::Red );
         do_jumping( dt );
         break;
      case e_Falling:
         m_shape.SetColor( sf::Color(128,128,128) );
         do_falling( dt );
         break;
      default:
         std::cout << "error\n";
         break;
   }
}

void Entomon::
do_resting( float dt )
{
   if( m_input->jumping() )
   {
      m_state = e_StartJump;
   }
   else if( ! m_resting )
   {
      m_state = e_Falling;
   }
}

void Entomon::
do_jumping( float dt )
{
   if( ! m_input->jumping() )
   {
      m_state = e_Falling;
   }
   else if ( m_resting )
   {
      m_state = e_Resting;
   }
}

void Entomon::
do_falling( float dt )
{
   if( m_resting )
   {
      m_state = e_Resting;
   }
}

void Entomon::
update( float dt )
{
   m_timer += dt;
   if( m_timer > 0.5f )
   {
      std::cout << m_contacts.size() << ", ";
      std::cout << m_collisions.size() <<  ", ";
      std::cout << m_body->GetAngle() << " + ";
      std::cout << m_body->GetAngularVelocity() << std::endl;
      m_timer = 0.f;
   }

   if( m_state == e_Resting )
   {
      b2Vec2 center = m_body->GetWorldCenter();
      b2Vec2 end = center + 2.f * m_rest_norm;
      sf::Vector2f draw_center = The_Viewing->world2draw( center );
      sf::Vector2f draw_end = The_Viewing->world2draw( end );
      m_normal = sf::Shape::Line( draw_center.x, draw_center.y, draw_end.x, draw_end.y, 0.1, sf::Color::Black );
   }

   m_shape.SetPosition( The_Viewing->world2draw( m_body->GetWorldCenter() ) );
}

void Entomon::
draw( sf::RenderWindow& app )
{
   app.Draw( m_shape );

   if( m_state == e_Resting )
      app.Draw( m_normal );
}

void Entomon::
apply_lateral( float dt )
{
   // lateral is significant
   if( std::abs( m_input->lateral() ) > 0.01f )
   {
      std::cout << "lateral movement\n";
      b2Vec2 direction( m_rest_norm.y, -m_rest_norm.x);
      b2Vec2 vel = m_body->GetLinearVelocity();
      float speed = b2Dot( vel, direction );
      float target_speed = m_input->lateral() * m_lateral_speed;
      float speed_diff = target_speed - speed;

      // traveling left
      if( speed < 0.f )
      {
         // want to travel left
         if( target_speed < 0.f )
         {
            // want to travel left faster
            if( speed_diff < 0.f )
            {
               float accel = std::max( speed_diff / dt, -m_lateral_accel );
               m_body->ApplyForce( accel * m_body->GetMass() * direction,
                     m_body->GetWorldCenter() );
            }
         }
         // want to travel right
         else
         {
            assert( speed_diff >= 0.f );
            float accel = std::min( speed_diff / dt, m_lateral_accel );
            m_body->ApplyForce( accel * m_body->GetMass() * direction,
                  m_body->GetWorldCenter() );
         }
      }
      // traveling right
      else
      {
         // want to travel left
         if( target_speed < 0.f )
         {
            assert( speed_diff <= 0.f );
            float accel = std::max( speed_diff / dt, -m_lateral_accel );
            m_body->ApplyForce( accel * m_body->GetMass() * direction,
                  m_body->GetWorldCenter() );
         }
         // want to travel right
         else
         {
            // want to travel right faster
            if( speed_diff > 0.f )
            {
               float accel = std::min( speed_diff / dt, m_lateral_accel );
               m_body->ApplyForce( accel * m_body->GetMass() * direction,
                     m_body->GetWorldCenter() );
            }
         }
      }
   }// if abs lateral
   else
   {
      m_body->SetAngularVelocity( 0 );
      
      //m_body->ApplyTorque(
      //m_body->GetInertia() *
      //( -m_body->GetAngularVelocity()/dt ) );
   }
}


}
