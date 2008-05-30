#include "Inputs.hpp"

#include <iostream>

namespace ento
{
Entomon_inputer::Entomon_inputer( void )
 : m_lateral(0.f), m_jumping( 0.f )
{ }

void Entomon_inputer::
update( float dt, const sf::Input& current )
{
	m_jumping = current.IsKeyDown( sf::Key::Space );

	m_lateral = 0.f;
	if( current.IsKeyDown( sf::Key::A ) )
	{
		m_lateral -= 1.f;
	}

	if( current.IsKeyDown( sf::Key::D ) )
	{
		m_lateral += 1.f;
	}
}

}
