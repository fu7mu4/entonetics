#ifndef ENTO_GLOBALS_HPP_INCLUDED
#define ENTO_GLOBALS_HPP_INCLUDED

#include <SFML/Graphics/RenderWindow.hpp>
#include "Inputer.hpp"
#include "GraphicSys.hpp"
#include "Simulator.hpp"
#include "Terrain.hpp"
#include "Viewing.hpp"

namespace ento
{
   extern sf::RenderWindow* The_App;
   extern GraphicSys*       The_Graphics;
   extern InputManager*     The_Inputs;
   extern Simulator*        The_Sim;
   extern TerrainManager*   The_Terrain;
   extern Viewing*          The_Viewing;
}

#endif // ENTO_GLOBALS_HPP_INCLUDED
