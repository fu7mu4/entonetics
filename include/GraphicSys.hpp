#ifndef ENTO_GRAPHICSYS_HPP_INCLUDED
#define ENTO_GRAPHICSYS_HPP_INCLUDED

#include <SFML/Graphics/RenderWindow.hpp>

#include <list>

namespace ento
{
   class Graphic
   {
   public:
      virtual ~Graphic( void ) {}
      virtual void draw( sf::RenderWindow& app ) =0;
      virtual bool alive( void ) =0;
   };

   class GraphicSys
   {
   public:
      void add( Graphic* g );
      void draw( sf::RenderWindow& app );
      std::size_t numGraphics(void)
      {
         return m_graphics.size();
      }

   private:
      std::list<Graphic*> m_graphics;
   };
}

#endif // ENTO_GRAPHICSYS_HPP_INCLUDED
