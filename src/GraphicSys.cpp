#include "GraphicSys.hpp"

namespace ento
{
   void GraphicSys::
   add( Graphic* g )
   {
      m_graphics.push_back( g );
   }

   void GraphicSys::
   draw( sf::RenderWindow& app )
   {
      std::list<Graphic*>::iterator iter = m_graphics.begin();
      std::list<Graphic*>::iterator end = m_graphics.end();

      while( iter != end )
      {
         Graphic& g = **iter;
         if( g.alive() )
         {
            g.draw(app);
            ++iter;
         }
         else
         {
            delete &g;
            iter = m_graphics.erase(iter);
         }
      }
   }
}
