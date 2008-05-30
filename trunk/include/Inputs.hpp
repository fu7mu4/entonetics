#ifndef ENTO_INPUTS_HPP_INCLUDED
#define ENTO_INPUTS_HPP_INCLUDED

#include "Inputer.hpp"

namespace ento
{

class Entomon_inputer : public Inputer
{
public:
	Entomon_inputer( void );

	float lateral( void ) const
	{ return m_lateral; }

	bool jumping( void ) const
	{ return m_jumping; }

protected:
	virtual void update( float dt, const sf::Input& current );

private:
	float m_lateral;
	bool m_jumping;
};

}

#endif //  ENTO_INPUTS_HPP_INCLUDED
