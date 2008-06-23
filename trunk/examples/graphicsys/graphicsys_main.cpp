#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <complex>

#include "GraphicSys.hpp"
#include "Viewing.hpp"
#include "Globals.hpp"
#include "GLPrimative.hpp"

namespace
{
   class SpriteGraphic : public ento::Graphic
   {
   public:
      SpriteGraphic( const sf::Sprite& sprite ) : cnt(200), m_sprite(sprite) {}

      void draw( sf::RenderWindow& app )
      {
         app.Draw(m_sprite);
      }

      bool alive()
      {
         return --cnt > 0;
      }

   private:
      int cnt;
      sf::Sprite m_sprite;
   };
}

int main()
{
   ento::GraphicSys graphics;
   ento::The_Graphics = &graphics;

   // Create the main rendering window
   sf::RenderWindow App(sf::VideoMode(800, 600, 32), "Entonetics");//, sf::Style::Fullscreen );
   ento::The_App = &App;
   App.UseVerticalSync(true);
   App.SetBackgroundColor( sf::Color( 64, 64, 64 ) );
   App.SetPosition( 200, 100 );

   ento::Viewing v( App );
   ento::The_Viewing = &v;
   v.setWidth( 100 );

   sf::Image i;
   i.LoadFromFile( "examples/graphicsys/data/test.png" );
   i.SetSmooth(false);

   graphics.add( new SpriteGraphic( sf::Sprite(i) ) );

   bool done = false;
   while ( !done )
   {
      // Process events
      sf::Event e;
      while (App.GetEvent(e))
      {
         switch ( e.Type )
         {
         case sf::Event::Closed:
            done = true;
            break;

         case sf::Event::MouseButtonPressed:
            {
               std::complex<float> c;
               c.real() = App.GetInput().GetMouseX();
               c.imag() = App.GetInput().GetMouseY();
               std::cout << c << std::endl;

               b2Vec2 vec = v.HUD2world( sf::Vector2f(c.real(), c.imag()) );
               c.real() = vec.x;
               c.imag() = vec.y;
               std::cout << c << std::endl;
               graphics.add( new SpriteGraphic(sf::Sprite(i,v.world2draw(vec))));
               break;
            }

         case sf::Event::KeyPressed:
            switch ( e.Key.Code )
            {
            case sf::Key::Escape:
            case sf::Key::Q:
               done = true;
               break;
            case sf::Key::L:
               {
                  std::complex<float> c;
                  c.real() = v.lookingAt().x;
                  c.imag() = v.lookingAt().y;
                  std::cout << c << std::endl;
                  c.real() = v.getWidth();
                  c.imag() = v.getHeight();
                  std::cout << c << std::endl;
                  break;
               }
            case sf::Key::Z:
               {
                  if ( e.Key.Shift )
                  {
                     v.setHeight( v.getHeight() - 1 );
                  }
                  else
                  {
                     v.setHeight( v.getHeight() + 1 );
                  }
                  break;
               }
            case sf::Key::Up:
               v.lookAt( v.lookingAt() + b2Vec2(0,1) );
               break;
            case sf::Key::Down:
               v.lookAt( v.lookingAt() + b2Vec2(0,-1) );
               break;
            case sf::Key::Left:
               v.lookAt( v.lookingAt() + b2Vec2(-1,0) );
               break;
            case sf::Key::Right:
               v.lookAt( v.lookingAt() + b2Vec2(1,0) );
               break;
            default:
               //std::cout << "unknown key\n";
               break;
            }
            break;
         default:
            //std::cout << "unknown event\n";
            break;
         }

      }

      graphics.draw(App);
      App.Display();
   }
   return EXIT_SUCCESS;
}
