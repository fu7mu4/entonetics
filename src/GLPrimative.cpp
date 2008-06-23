


////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "GLPrimative.hpp"
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <GL/gl.h>


namespace sf
{
////////////////////////////////////////////////////////////
/// Default constructor
////////////////////////////////////////////////////////////
GLPrimative::GLPrimative( Render::Mode Mode ) :
Drawable(),
myImage     (NULL),
myRenderMode(Mode),
myIsCompiled(false)
{

}


////////////////////////////////////////////////////////////
/// Set the render mode for the primative.
////////////////////////////////////////////////////////////
void GLPrimative::SetRenderMode( Render::Mode Mode )
{
   myRenderMode = Mode;
}


////////////////////////////////////////////////////////////
/// Get the currnet render mode for the primative.
////////////////////////////////////////////////////////////
Render::Mode GLPrimative::GetRenderMode() const
{
   return myRenderMode;
}


////////////////////////////////////////////////////////////
/// Set the image used to render the primative
////////////////////////////////////////////////////////////
void GLPrimative::SetImage(const Image& Img)
{
    // Assign the new image
    myImage = &Img;
    myIsCompiled = false;
}


////////////////////////////////////////////////////////////
/// Get the image used to render the primative
////////////////////////////////////////////////////////////
const Image* GLPrimative::GetImage( void ) const
{
    return myImage;
}


////////////////////////////////////////////////////////////
/// Add a point to the primative
////////////////////////////////////////////////////////////
void GLPrimative::AddVertex( float X, float Y )
{
    AddVertex( Vector2f(X,Y), GetColor() );
}


////////////////////////////////////////////////////////////
/// Add a point to the primative
////////////////////////////////////////////////////////////
void GLPrimative::AddVertex( const Vector2f& Position )
{
    AddVertex(Position, GetColor());
}


////////////////////////////////////////////////////////////
/// Add a point to the primative
////////////////////////////////////////////////////////////
void GLPrimative::AddVertex( float X, float Y, const Color& Col )
{
    AddVertex(Vector2f(X, Y), Col );
}


////////////////////////////////////////////////////////////
/// Add a point to the primative
////////////////////////////////////////////////////////////
void GLPrimative::AddVertex( const Vector2f& Position, const Color& Col )
{
    myVertices.push_back(Vertex(Position, Col));
    myIsCompiled = false;
}


////////////////////////////////////////////////////////////
/// Add a point to the primative
////////////////////////////////////////////////////////////
void GLPrimative::AddVertex( float X, float Y, unsigned U, unsigned V )
{
    AddVertex(Vector2f(X, Y), Vector2i(U, V));
}


////////////////////////////////////////////////////////////
/// Add a point to the primative
////////////////////////////////////////////////////////////
void GLPrimative::AddVertex( const Vector2f& Position, const Vector2i& Pixel )
{
    myVertices.push_back(Vertex(Position, Pixel));
    myIsCompiled = false;
}

static inline sf::Vector2f GetTexCoords( const Image& Img, const Vector2i& P )
{
   const IntRect ir(0, 0, P.x, P.y );
   const FloatRect fr = Img.GetTexCoords( ir, false );
   return Vector2f( fr.Right, fr.Bottom );
}

////////////////////////////////////////////////////////////
/// Compile the primative : compute its UV coords
///
////////////////////////////////////////////////////////////
void GLPrimative::Compile() const
{
   std::vector<Vertex>::const_iterator iter, end;
   iter = myVertices.begin();
   end = myVertices.end();
   for(; iter!=end; ++iter )
   {
      if (myImage)
      {
         // this should be an Image method
         iter->UV = GetTexCoords( *myImage, iter->Pixel );
      }

      const float scale = 1/255.f;
      iter->R = iter->Col.r * scale;
      iter->G = iter->Col.g * scale;
      iter->B = iter->Col.b * scale;
      iter->A = iter->Col.a * scale;
   }
   myIsCompiled = true;
}

////////////////////////////////////////////////////////////
/// Use Render::Mode to start an OpenGL render mode
///
/// \param M : The render mode to start
///
////////////////////////////////////////////////////////////
static void do_glBegin( Render::Mode Mode )
{
    using namespace Render;
    switch (Mode)
    {
        case Points :         glBegin(GL_POINTS);         break;
        case Lines :          glBegin(GL_LINES);          break;
        case Line_Loop :      glBegin(GL_LINE_LOOP);      break;
        case Line_Strip :     glBegin(GL_LINE_STRIP);     break;
        case Triangles :      glBegin(GL_TRIANGLES);      break;
        case Triangle_Strip : glBegin(GL_TRIANGLE_STRIP); break;
        case Triangle_Fan :   glBegin(GL_TRIANGLE_FAN);   break;
        case Quads :          glBegin(GL_QUADS);          break;
        case Quad_Strip :     glBegin(GL_QUAD_STRIP);     break;
        case Polygon :        glBegin(GL_POLYGON);        break;
    }
}

////////////////////////////////////////////////////////////
/// /see Drawable::Render
////////////////////////////////////////////////////////////
void GLPrimative::Render( const RenderWindow& Window ) const
{
   if (!myIsCompiled)
      Compile();

   if (myImage)
   {
      myImage->Bind();

      do_glBegin(myRenderMode);
      {
         std::vector<Vertex>::const_iterator iter, end;
         iter = myVertices.begin();
         end = myVertices.end();
         for(; iter!=end; ++iter)
         {
            iter->glTexCoord();
            iter->glVertex();
         }
      }
      glEnd();
   }
   else
   {
      // Only use color, no texture
      //GLCheck(glDisable(GL_TEXTURE_2D));
      glDisable(GL_TEXTURE_2D);

      do_glBegin(myRenderMode);
      {
         std::vector<Vertex>::const_iterator iter, end;
         iter = myVertices.begin();
         end = myVertices.end();
         for(; iter!=end; ++iter )
         {
            iter->glColor();
            iter->glVertex();
         }
      }
      glEnd();
   }
}


////////////////////////////////////////////////////////////
// GLPrimative::Vertex
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
/// Construct a color vertex
////////////////////////////////////////////////////////////
GLPrimative::Vertex::Vertex(const Vector2f& XY, const Color& C) :
Vert(XY),
Col(C)
{

}


////////////////////////////////////////////////////////////
/// Construct a texture vertex
////////////////////////////////////////////////////////////
GLPrimative::Vertex::Vertex(const Vector2f& XY, const Vector2i& P) :
Vert(XY),
Pixel(P)
{

}


////////////////////////////////////////////////////////////
/// execute the glColor* command for this vertex
////////////////////////////////////////////////////////////
void GLPrimative::Vertex::glColor() const
{
   glColor4f( Col.r/255.f, Col.g/255.f, Col.b/255.f, Col.a/255.f );
}


////////////////////////////////////////////////////////////
/// execute the glTexCoord* command for this vertex
////////////////////////////////////////////////////////////
void GLPrimative::Vertex::glTexCoord() const
{
   glTexCoord2f( UV.x, UV.y );
}


////////////////////////////////////////////////////////////
/// execute the glVertex* command for this vertex
////////////////////////////////////////////////////////////
void GLPrimative::Vertex::glVertex() const
{
   glVertex2f(Vert.x, Vert.y);
}

} // namespace sf
