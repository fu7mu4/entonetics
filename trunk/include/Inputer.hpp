#ifndef ENTO_INPUTER_HPP_INCLUDED
#define ENTO_INPUTER_HPP_INCLUDED

#include <SFML/Window/Input.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <list>

namespace ento
{
class Inputer;

class InputManager
{
public:
	InputManager( sf::RenderWindow& app );

	template< typename T >
	T* createInputer( void );

	void update( float dt );

private:
	sf::RenderWindow* m_app;
	std::list<Inputer*> m_inputers;
};

template< typename T >
T* InputManager::
createInputer( void )
{
	T* ret = new T();
	m_inputers.push_back( ret );
	return ret;
}

class Inputer
{
	friend class InputManager;
public:
	Inputer( void );
	virtual ~Inputer( void ) {}

	bool isValid( void ) const
	{ return m_is_valid; }

	void isValid( bool valid )
	{ m_is_valid = valid; }

protected:
	virtual void update( float dt, const sf::Input& current ) =0;
private:
	bool m_is_valid;
};

}

#endif // ENTO_INPUTER_HPP_INCLUDED
