#include "Inputer.hpp"

#include <cassert>

namespace ento
{

InputManager::InputManager( sf::RenderWindow& app )
 : m_app( &app )
{ }

void InputManager::
update( float dt )
{
	std::list<Inputer*>::iterator iter = m_inputers.begin();
	std::list<Inputer*>::iterator end = m_inputers.end();

	while( iter != end )
	{
		if( (*iter)->isValid() )
		{
			(*iter)->update( dt, m_app->GetInput() );
			++iter;
		}
		else
		{
			iter = m_inputers.erase( iter );
		}
	}
}

Inputer::Inputer( void )
 : m_is_valid(true)
{}

}
