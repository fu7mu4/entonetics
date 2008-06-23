#ifndef ENTO_ENTOMON_HPP_INCLUDED
#define ENTO_ENTOMON_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <Box2D.h>
#include <map>

#include "Inputs.hpp"
#include "Object.hpp"
#include "Motors.hpp"

namespace ento
{
   class Entomon;

   struct Contact
   {
      b2Shape* self;
      b2Shape* other;
      b2Vec2 position;
      b2Vec2 normal;
      float normalImpulse;
      float tangentImpulse;
      b2ContactID id;
   };

   class Entomon : public Object
   {
   public:
      Entomon( void );

      void update( float dt );
      void draw( sf::RenderWindow& app );

      b2Vec2 getPosition( void )
      {
         return m_body->GetWorldCenter();
      }

      bool addCollision( const b2ContactPoint& point, b2Shape* self );
      bool addContact( const b2ContactResult& point, b2Shape* self );

      void preStep ( float dt );
      void postStep( float dt );

   private:
      sf::Shape m_shape;
      sf::Shape m_normal;
      Entomon_inputer* m_input;

      enum State
      {
         e_Resting,
         e_StartJump,
         e_Jumping,
         e_Falling
      };

      State m_state;
      float m_timer;

      void do_resting( float dt );

      bool m_jump_cont;
      float m_jump_cooldown;
      void do_start_jump( float dt );

      void do_jumping( float dt );

      void do_falling( float dt );

      void apply_lateral( float dt );

      b2Body* m_body;

      b2Vec2 m_rest_norm;
      bool m_resting;
      std::vector<Contact> m_contacts;
      std::vector<Contact> m_collisions;

      float m_lateral_speed;
      float m_lateral_accel;
   };
}

#endif // ENTO_ENTOMON_HPP_INCLUDED
