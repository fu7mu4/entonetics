#ifndef ENTO_SIMULATOR_HPP_INCLUDED
#define ENTO_SIMULATOR_HPP_INCLUDED

#include <Box2D.h>
#include <list>
#include "Motors.hpp"

namespace ento
{
	
	class Contact_cb : public b2ContactListener
	{
	public:
		virtual void Add( const b2ContactPoint* point );
		virtual void Persist( const b2ContactPoint* point );
		virtual void Remove( const b2ContactPoint* point );
		virtual void Result( const b2ContactResult* point );
	};

	class Simulator
	{
	public:
		struct Settings
		{
			Settings( void );

			float step_size;
			float max_time;
			unsigned iterations;
			b2Vec2 gravity;
			float g_accel;
			bool g_point;
			b2AABB boundries;
		};

		Simulator( const Settings& settings);

		b2World& world( void );

		void addMotor( Motor* m )
		{ m_motors.push_back(m); }

		unsigned update( float dt );

		b2Vec2 getGravityNormal( const b2Vec2& position ) const;
		float getGravityAccel( const b2Vec2& position ) const;

		unsigned version( void )
		{ return m_total_steps; }

	private:
		void applyMotors( float dt );
		void preStep( float dt );
		void postStep( float dt );
		void applyGravity( b2Body* body );
		void resetObject( b2Body* body );

		float m_time;
		float m_step_size;
		float m_max_time;
		unsigned m_iterations;
		b2Vec2 m_gravity;
		float m_g_accel;
		bool m_g_point;
		b2World m_world;
		Contact_cb m_contact_cb;

		unsigned m_total_steps;

		std::list<Motor*> m_motors;
	};
}

#endif // ENTO_SIMULATOR_HPP_INCLUDED
