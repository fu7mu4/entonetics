#include <SFML/Graphics.hpp>
#include <Box2D.h>
#include <cstdlib>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <complex>

#include "Animation.hpp"
#include "Terrain.hpp"
#include "Viewing.hpp"
#include "Simulator.hpp"
#include "Entomon.hpp"
#include "Globals.hpp"

sf::Color pickColor( const b2Vec2& vec )
{
	int x = static_cast<int>(vec.x);
	int y = static_cast<int>(vec.y);

	int xval = (x/11) % 2;
	int yval = (y/11) % 2;

	if ( xval ^ yval )
		return sf::Color(85,107,47);
	else
		return sf::Color(0,96,0);
}

void Draw( sf::RenderWindow& app, b2Body* b, b2Shape* s, const sf::Color& c )
{
	if ( s->GetType() == e_polygonShape )
	{
		b2PolygonShape* poly =
		reinterpret_cast<b2PolygonShape*>( s );
		sf::Shape shape;
		const b2Vec2* points = poly->GetVertices();
		for ( int i=0; i<poly->GetVertexCount(); ++i )
		{
			b2Vec2 tmp = b->GetWorldPoint( points[i] );
			shape.AddPoint( sf::Vector2f( tmp.x, -tmp.y), pickColor( tmp) );
		}
		//shape.SetOutline(1);
		app.Draw(shape);
	}
	else
	{

		b2CircleShape* circle = 
		reinterpret_cast<b2CircleShape*>( s );
		b2Vec2 tmp = b->GetWorldPoint(circle->GetLocalPosition());
		app.Draw( sf::Shape::Circle( tmp.x, -tmp.y, circle->GetRadius(), c ) );
	}
}

void Draw( sf::RenderWindow& app, b2Body* b, const sf::Color& c )
{
	for ( b2Shape* s = b->GetShapeList(); s; s = s->GetNext() )
	{
		Draw( app, b, s, c );
	}
}

void Draw( sf::RenderWindow& app, b2World& world, const sf::Color& c )
{
	for ( b2Body* b = world.GetBodyList(); b; b = b->GetNext() )
	{
		Draw( app, b, c );
	}
}

int main()
{
	ento::Simulator::Settings sim_set;
	sim_set.g_accel *= 5;
	ento::Simulator sim(sim_set);
	ento::The_Sim = &sim;

	ento::TerrainManager::Settings terr_set;
	terr_set.world = &sim.world();
	ento::TerrainManager terr( terr_set );
	ento::The_Terrain = &terr;

	sf::Randomizer::SetSeed(1);

	std::vector<b2Vec2> points;
	float x = 40.f;
	while ( x > -40.f )
	{
		points.push_back( b2Vec2( x, sf::Randomizer::Random(8,12) ) );
		x -= sf::Randomizer::Random(5,10);
	}
	points.push_back( b2Vec2(-40, 10.f) );
	points.push_back( b2Vec2(-40, 0.f) );
	points.push_back( b2Vec2(-20, 0.f) );
	points.push_back( b2Vec2(0, 0.f) );
	points.push_back( b2Vec2(20, 0.f) );
	points.push_back( b2Vec2(40, 0.f) );

	terr.addOutline(points.begin(), points.end());

	b2CircleDef circDef;
	circDef.restitution = 0.5f;
	circDef.friction = 0.5f;
	circDef.radius = 1;
	circDef.density = 1;

	b2BodyDef bodyDef;
	bodyDef.position.Set( 0, 50 );

	// Create the main rendering window
	sf::RenderWindow App(sf::VideoMode(800, 600, 32), "Entonetics");
	ento::The_App = &App;
	App.SetBackgroundColor( sf::Color( 64, 64, 64 ) );
	App.SetPosition( 200, 100 );

	ento::InputManager inputs( App );
	ento::The_Inputs = &inputs;

	ento::Viewing v( App );
	ento::The_Viewing = &v;
	v.setWidth( 100 );

	ento::Entomon p1;

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
					break;
				}

			case sf::Event::KeyPressed:
				switch ( e.Key.Code )
				{
				case sf::Key::Escape:
				case sf::Key::Q:
					done = true;
					break;
				case sf::Key::B:
					{
						b2Body* b = sim.world().CreateBody(&bodyDef);
						b->CreateShape(&circDef);
						b->SetMassFromShapes();
						break;
					}
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
						if ( e.Key.Control )
						{
							v.setHeight( v.getHeight() - 1 );
						}
						else if ( e.Key.Shift )
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


		b2Vec2 camera_move = p1.getPosition() - v.lookingAt();
		if ( camera_move.Length() > 1.f )
		{
			camera_move *= 0.5f;
		}
		v.lookAt( v.lookingAt() + camera_move );

		Draw( App, sim.world(), sf::Color::Blue );

		inputs.update( App.GetFrameTime() );
		p1.update( App.GetFrameTime() );
		p1.draw( App );

		// Display window contents on screen
		App.Display();

		sim.update( App.GetFrameTime() );
	}
	return EXIT_SUCCESS;
}
