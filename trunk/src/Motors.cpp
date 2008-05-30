#include "Motors.hpp"
#include <iostream>

namespace ento
{

Motor::Motor( void )
 : m_dead(false), m_enabled(true)
{}

Motor::~Motor( void ) {}

Linear_motor::Linear_motor( b2Body* body )
 : m_body(body)
{}

void Linear_motor::
apply( float dt )
{
	std::cout << "Linear_motor::apply\n";
	b2Vec2 vel = m_body->GetLinearVelocity();
	float speed = b2Dot( vel, m_direction );
	float speed_diff = m_target_speed - speed;

	// traveling left
	if( speed < 0.f )
	{
		// want to travel left
		if( m_target_speed < 0.f )
		{
			// want to travel left faster
			if( speed_diff < 0.f )
			{
				float accel = std::max( speed_diff / dt, -m_max_accel );
				m_body->ApplyForce( accel * m_body->GetMass() * m_direction,
				                    m_body->GetWorldCenter() );
			}

		}
		// want to travel right
		else
		{
			assert( speed_diff >= 0.f );
			float accel = std::min( speed_diff / dt, m_max_accel );
			m_body->ApplyForce( accel * m_body->GetMass() * m_direction,
									  m_body->GetWorldCenter() );
		}
	}
	// traveling right
	else
	{
		// want to travel left
		if( m_target_speed < 0.f )
		{
			assert( speed_diff <= 0.f );
			float accel = std::max( speed_diff / dt, -m_max_accel );
			m_body->ApplyForce( accel * m_body->GetMass() * m_direction,
									  m_body->GetWorldCenter() );
		}
		// want to travel right
		else
		{
			// want to travel right faster
			if( speed_diff > 0.f )
			{
				float accel = std::min( speed_diff / dt, m_max_accel );
				m_body->ApplyForce( accel * m_body->GetMass() * m_direction,
										  m_body->GetWorldCenter() );
			}
		}
	}
}

}
