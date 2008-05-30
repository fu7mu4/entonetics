#ifndef ENTO_GLOBALS_HPP_INCLUDED
#define ENTO_GLOBALS_HPP_INCLUDED

#include "Simulator.hpp"
#include "Viewing.hpp"
#include "Terrain.hpp"
#include "Inputer.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

namespace ento
{
	extern Simulator* The_Sim;
	extern Viewing* The_Viewing;
	extern TerrainManager* The_Terrain;
	extern InputManager* The_Inputs;
	extern sf::RenderWindow* The_App;
}

#endif // ENTO_GLOBALS_HPP_INCLUDED
