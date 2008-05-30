#ifndef VIEWING_HPP_INCLUDED
#define VIEWING_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <Box2D.h>

namespace ento
{
   class Viewing
   {
   public:
      Viewing( sf::RenderWindow& app );

      void lookAt( const b2Vec2& pos );
      b2Vec2 lookingAt( void ) const;

      void zoom( float factor );

      float getWidth( void ) const;
      void setWidth( float width );

      float getHeight( void ) const;
      void setHeight( float height );

      void HUDview( bool hud );

      sf::Vector2f world2draw( const b2Vec2& vec ) const;
      b2Vec2 draw2world( const sf::Vector2f& vec ) const;

      sf::Vector2f world2HUD( const b2Vec2& vec ) const;
      b2Vec2 HUD2world( const sf::Vector2f& vec ) const;

   private:
      void update_view( void );

      sf::RenderWindow* m_app;
      bool m_is_hud;
      sf::View m_world_view;
   };
}//namespace ento

#endif // VIEWING_HPP_INCLUDED
