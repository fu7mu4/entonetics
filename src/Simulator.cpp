#include "Simulator.hpp"

#include "Object.hpp"
#include <iostream>

namespace ento
{

void Contact_cb::
Add( const b2ContactPoint* point )
{
	ento::Object* obj;

	obj = reinterpret_cast<ento::Object*>(
			point->shape1->GetBody()->GetUserData() );
	obj->addCollision( *point, point->shape1 );

	obj = reinterpret_cast<ento::Object*>(
			point->shape2->GetBody()->GetUserData() );
	obj->addCollision( *point, point->shape2 );
}

void Contact_cb::
Persist( const b2ContactPoint* point )
{
	ento::Object* obj;

	obj = reinterpret_cast<ento::Object*>(
			point->shape1->GetBody()->GetUserData() );
	obj->addCollision( *point, point->shape1 );

	obj = reinterpret_cast<ento::Object*>(
			point->shape2->GetBody()->GetUserData() );
	obj->addCollision( *point, point->shape2 );
}

void Contact_cb::
Remove( const b2ContactPoint* p )
{ }

void Contact_cb::
Result( const b2ContactResult* point )
{
	ento::Object* obj;

	obj = reinterpret_cast<ento::Object*>(
			point->shape1->GetBody()->GetUserData() );
	obj->addContact( *point, point->shape1 );

	obj = reinterpret_cast<ento::Object*>(
			point->shape2->GetBody()->GetUserData() );
	obj->addContact( *point, point->shape2 );
}



Simulator::Settings::Settings( void )
 : step_size( 1.f/30.f ),
   max_time( 1.f ),
	iterations( 10 ),
	gravity( 0.f, -1.f ), g_accel(9.80665f), g_point(false)
{
	boundries.lowerBound.Set( -1000.f, -1000.f );
	boundries.upperBound.Set( 1000.f, 1000.f );
}

Simulator::Simulator( const Simulator::Settings& settings )
 : m_time(0.f),
   m_step_size( settings.step_size ),
	m_max_time( settings.max_time ),
   m_iterations( settings.iterations ),
	m_gravity(settings.gravity), m_g_accel(settings.g_accel),
	m_g_point( settings.g_point ),
	m_world( settings.boundries, b2Vec2(0.f,0.f), true ) ,
	m_total_steps(0)
{
	m_world.SetContactListener( &m_contact_cb );
}

b2World& Simulator::
world( void )
{ return m_world; }

b2Vec2 Simulator::
getGravityNormal( const b2Vec2& position ) const
{
	if( m_g_point )
	{
		b2Vec2 g_dir = m_gravity - position;
		g_dir.Normalize();
		return g_dir;
	}
	else
	{
		return m_gravity;
	}
}

float Simulator::
getGravityAccel( const b2Vec2& position ) const
{
	return m_g_accel;
}

unsigned Simulator::
update( float dt )
{
	m_time += dt;
	m_time = std::min( m_time, m_max_time );

	unsigned steps = 0;
	while( m_step_size < m_time )
	{
		m_time -= m_step_size;
		preStep( dt );
		m_world.Step( m_step_size, m_iterations );
		++steps;
		postStep( dt );
	}
	m_total_steps += steps;
	return steps;
}

void Simulator::
applyMotors( float dt )
{
	std::list<Motor*>::iterator iter = m_motors.begin();
	std::list<Motor*>::iterator end = m_motors.end();

	while( iter != end )
	{
		if( (*iter)->dead() )
		{
			delete *iter;
			iter = m_motors.erase( iter );
		}
		else
		{
			if( (*iter)->enabled() )
			{
				(*iter)->apply(dt);
			}
			++iter;
		}
	}
}

void Simulator::
preStep( float dt )
{
	b2Body* body = m_world.GetBodyList();
	while( body )
	{
		reinterpret_cast<Object*>( body->GetUserData() )->preStep(dt);
		applyGravity( body );

		body = body->GetNext();
	}
}

void Simulator::
postStep( float dt )
{
	b2Body* body = m_world.GetBodyList();
	while( body )
	{
		reinterpret_cast<Object*>( body->GetUserData() )->postStep(dt);
		body = body->GetNext();
	}
}

void Simulator::
applyGravity( b2Body* body )
{
	b2Vec2 g_force = getGravityNormal( body->GetWorldCenter() );
	g_force *= getGravityAccel( body->GetWorldCenter() );

	if( ! body->IsSleeping() )
	{
		body->ApplyForce( body->GetMass()*g_force, body->GetWorldCenter() );
	}
}

}
