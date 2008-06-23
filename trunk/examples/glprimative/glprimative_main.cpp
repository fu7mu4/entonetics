#include <SFML/Graphics.hpp>
#include <algorithm>
#include <cstdlib>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <complex>

#include "GLPrimative.hpp"

template< typename T >
std::ostream& operator<<( std::ostream& out, const sf::Rect<T>& r )
{
   out << '(' << r.Top << ", " << r.Left << ", " << r.Bottom << ", " << r.Right << ')';
   return out;
}

class RawColorSquare : public sf::Drawable
{
public:
   RawColorSquare(): sf::Drawable() {}

   virtual void Render( const sf::RenderWindow& app ) const
   {
      glDisable( GL_TEXTURE_2D );
      glBegin( GL_QUADS );
      {
         glColor4f( 1, 0, 0, 1 ); glVertex2f( 60, 10 );
         glColor4f( 0, 0, 1, 1 ); glVertex2f( 60, 50 );
         glColor4f( 0, 1, 1, 1 ); glVertex2f( 100, 50 );
         glColor4f( 1, 1, 0, 1 ); glVertex2f( 100, 10 );
      }
      glEnd();
   }
};

class RawColorTriangles : public sf::Drawable
{
public:
   RawColorTriangles(): sf::Drawable() {}

   virtual void Render( const sf::RenderWindow& app ) const
   {
      glDisable( GL_TEXTURE_2D );
      glBegin( GL_TRIANGLES );
      {
         glColor4f( 1, 0, 0, 1 ); glVertex2f( 60, 110 );
         glColor4f( 0, 0, 1, 1 ); glVertex2f( 60, 150 );
         glColor4f( 1, 1, 0, 1 ); glVertex2f( 100, 110 );

         glColor4f( 0, 0, 1, 1 ); glVertex2f( 60, 160 );
         glColor4f( 0, 1, 1, 1 ); glVertex2f( 100, 160 );
         glColor4f( 1, 1, 0, 1 ); glVertex2f( 100, 120 );
      }
      glEnd();
   }
};

class RawTexSquare : public sf::Drawable
{
public:
   RawTexSquare(sf::Image& image): sf::Drawable(), m_image(&image) {}

   virtual void Render( const sf::RenderWindow& app ) const
   {
      m_image->Bind();
      sf::IntRect ir( 0, 0, m_image->GetWidth(), m_image->GetHeight() );
      sf::FloatRect fr = m_image->GetTexCoords(ir);

      glBegin( GL_QUADS );
      {
         glTexCoord2f( fr.Left, fr.Top); glVertex2f( 110, 10 );
         glTexCoord2f( fr.Left, fr.Bottom); glVertex2f( 110, 50 );
         glTexCoord2f( fr.Right, fr.Bottom); glVertex2f( 150, 50 );
         glTexCoord2f( fr.Right, fr.Top); glVertex2f( 150, 10 );
      }
      glEnd();
   }

private:
   sf::Image* m_image;
};



int main()
{
   // Create the main rendering window
   sf::RenderWindow App(sf::VideoMode(400, 300, 32), "glprimative");
   App.UseVerticalSync(true);
   App.SetBackgroundColor( sf::Color( 64, 64, 64 ) );
   App.SetPosition( 200, 100 );

   sf::Image i;
   i.LoadFromFile( "examples/glprimative/test.png" );
   i.SetSmooth(false);

   sf::Sprite s(i, sf::Vector2f(10,10));

   sf::Shape sh;
   sh.AddPoint( 10, 60, sf::Color::Red );
   sh.AddPoint( 10, 100, sf::Color::Blue );
   sh.AddPoint( 50, 100, sf::Color::Cyan );
   sh.AddPoint( 50, 60, sf::Color::Yellow );

   RawColorSquare raw_color;
   RawColorTriangles raw_color_tris;
   RawTexSquare raw_tex(i);

   sf::GLPrimative prim_color(sf::Render::Quads);
   prim_color.AddVertex( 60, 60, sf::Color::Red );
   prim_color.AddVertex( 60, 100, sf::Color::Blue );
   prim_color.AddVertex( 100, 100, sf::Color::Cyan );
   prim_color.AddVertex( 100, 60, sf::Color::Yellow );

   sf::GLPrimative prim_tex(sf::Render::Quads);
   prim_tex.SetImage( i );
   prim_tex.AddVertex( 110, 60, 0, 0 );
   prim_tex.AddVertex( 110, 100, 0, i.GetHeight() );
   prim_tex.AddVertex( 150, 100, i.GetWidth(), i.GetHeight() );
   prim_tex.AddVertex( 150, 60, i.GetWidth(), 0 );

   sf::GLPrimative prim_tex_tris(sf::Render::Triangles);
   prim_tex_tris.SetImage( i );
   prim_tex_tris.AddVertex( 110, 110, 0, 0 );
   prim_tex_tris.AddVertex( 110, 150, 0, i.GetHeight());
   prim_tex_tris.AddVertex( 150, 110, i.GetWidth(), 0 );

   prim_tex_tris.AddVertex( 110, 160, 0, i.GetHeight() );
   prim_tex_tris.AddVertex( 150, 160, i.GetWidth(), i.GetHeight());
   prim_tex_tris.AddVertex( 150, 120, i.GetWidth(), 0 );

   std::vector<sf::Drawable*> objs;
   objs.push_back(&s);
   objs.push_back(&sh);
   objs.push_back(&raw_color);
   objs.push_back(&raw_color_tris);
   objs.push_back(&raw_tex);
   objs.push_back(&prim_tex);
   objs.push_back(&prim_color);
   objs.push_back(&prim_tex_tris);

   std::sort( objs.begin(), objs.end() );

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

         case sf::Event::KeyPressed:
            switch ( e.Key.Code )
            {
            case sf::Key::Escape:
            case sf::Key::Q:
               done = true;
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

      done = !std::next_permutation(objs.begin(), objs.end());
      std::vector<sf::Drawable*>::iterator iter, end;
      iter = objs.begin();
      end = objs.end();
      for(; iter!=end; ++iter )
      {
         App.Draw( **iter );
      }

      //App.Draw(raw_tex);
      //App.Draw(raw_color);
      //App.Draw(raw_color_tris);
      //App.Draw(s);
      //App.Draw(sh);
      //App.Draw(prim_color);
      //App.Draw(prim_tex);
      App.Display();
   }
   return EXIT_SUCCESS;
}
