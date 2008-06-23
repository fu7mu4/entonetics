#ifndef ENTO_DEBUGDRAW_HPP_INCLUDED
#define ENTO_DEBUGDRAW_HPP_INCLUDED

#include <Box2D.h>

namespace ento
{
   
   class DebugDraw : public b2DebugDraw
   {
   public:
      virtual void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
   
      virtual void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
   
      virtual void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color);
   
      virtual void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color);
   
      virtual void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color);
   
      virtual void DrawXForm(const b2XForm& xf);
   };

}

#endif // ENTO_DEBUGDRAW_HPP_INCLUDED
