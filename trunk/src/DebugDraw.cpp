
#include <iostream>

#include "DebugDraw.hpp"
#include "GLPrimative.hpp"
#include "Globals.hpp"

namespace ento
{
   namespace // anonymous
   {
      inline const sf::Color convert( const b2Color& color, sf::Uint8 alpha=255 )
      {
         return sf::Color( roundf( 255.f * color.r),
                           roundf( 255.f * color.g),
                           roundf( 255.f * color.b),
                           alpha );
      }

      inline const sf::Color invert( const b2Color& color, sf::Uint8 alpha=255 )
      {
         return sf::Color( roundf( 255.f * ( 1.f - color.r )),
                           roundf( 255.f * ( 1.f - color.g )),
                           roundf( 255.f * ( 1.f - color.b )),
                           alpha );
      }

      class DebugGraphic : public Graphic
      {
      public:
         DebugGraphic(void)
          : m_version( The_Sim->version() )
         { }

         virtual bool alive(void)
         {
            return m_version <= The_Sim->version();
         }

         virtual void draw( sf::RenderWindow& app )
         {
            app.Draw(m_primative);
         }

         sf::GLPrimative& primative( void )
         {
            return m_primative;
         }

      private:
         sf::GLPrimative m_primative;
         const unsigned m_version;
      };

   }
   
   void DebugDraw::
   DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
   {
      DebugGraphic* dg = new DebugGraphic;
      The_Graphics->add(dg);
      sf::GLPrimative& p = dg->primative();
      p.SetRenderMode( sf::Render::Line_Loop );

      for( int32 i=vertexCount-1; i>=0; --i )
      {
         p.AddVertex( The_Viewing->world2draw(vertices[i]), convert(color) );
      }
   }
   
   void DebugDraw::
   DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
   {
      DebugGraphic* dg = new DebugGraphic;
      The_Graphics->add(dg);
      sf::GLPrimative& p = dg->primative();
      p.SetRenderMode( sf::Render::Polygon );

      for( int32 i=vertexCount-1; i>0; --i )
      {
         p.AddVertex( The_Viewing->world2draw(vertices[i]), convert(color) );
      }
      p.AddVertex( The_Viewing->world2draw( vertices[0] ), invert(color) );
   }
   
   void DebugDraw::
   DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
   {
      DebugGraphic* dg = new DebugGraphic;
      The_Graphics->add(dg);
      //sf::Shape& s = dg->shape();

      const float angle_step = b2_pi * (1.f/11.f);
      for( float angle=0.f; angle<b2_pi; angle += angle_step )
      {
         //s.AddPoint( The_Viewing->world2draw(center + radius*b2Vec2(cos(angle), sin(angle))), convert(color) );
      }
   }
   
   void DebugDraw::
   DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
   {
      DebugGraphic* dg = new DebugGraphic;
      The_Graphics->add(dg);
      //sf::Shape& s = dg->shape();

      const float angle_step = b2_pi * (1.f/11.f);
      float origin = atan2( axis.y, axis.x );
      //s.AddPoint( The_Viewing->world2draw(center + b2Vec2(cos(origin), sin(origin))), invert(color) );
      for( unsigned i=1; i<11; ++i )
      {
         const float angle = origin + i * angle_step;
         //s.AddPoint( The_Viewing->world2draw(center + radius*b2Vec2(cos(angle), sin(angle))), convert(color) );
      }

   }
   
   void DebugDraw::
   DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
   {
   }
   
   void DebugDraw::
   DrawXForm(const b2XForm& xf)
   {
   }

}
