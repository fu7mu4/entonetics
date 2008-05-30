#ifndef ENTO_MOTORS_HPP_INCLUDED
#define ENTO_MOTORS_HPP_INCLUDED

#include "Box2D.h"

namespace ento
{

class Simulator;
class Motor
{
	friend class Simulator;
public:
	Motor( void );
	virtual ~Motor( void );

	virtual void apply( float dt ) =0;

	bool enabled( void ) const
	{ return m_enabled; }

	void enable( bool enable )
	{ m_enabled = enable; }

	void kill( void )
	{ m_dead = true; }

protected:
	bool dead( void ) const
	{ return m_dead; }

private:
	bool m_dead;
	bool m_enabled;

};

class Linear_motor : public Motor
{
public:
	Linear_motor( b2Body* body );
	
	virtual void apply( float dt );
	
	const b2Vec2& getDirection( void ) const
	{ return m_direction; }

	void setDirection( const b2Vec2& dir )
	{ m_direction = dir; }

	float getTargetSpeed( void ) const
	{ return m_target_speed; }

	void setTargetSpeed( float speed )
	{ m_target_speed = speed; }

	float getMaxAccel( void ) const
	{ return m_max_accel; }

	void setMaxAccel( float accel )
	{ m_max_accel = accel; }

private:
	b2Body* m_body;

	b2Vec2 m_direction;
	float m_target_speed;
	float m_max_accel;
};

}

#endif // ENTO_MOTORS_HPP_INCLUDED
