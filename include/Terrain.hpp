#ifndef TERRAIN_HPP_INCLUDED
#define TERRAIN_HPP_INCLUDED

#include <algorithm>
#include <boost/bind.hpp>
#include <Box2D.h>
#include <GL/glu.h>
#include <list>
#include <map>
#include <vector>

#include "Object.hpp"

namespace ento
{
	class TerrainManager
	{
	public:
		struct Settings
		{
			Settings( void );

			b2PolygonDef ground_def;

			float flat_threshold;

			b2World* world;
		};

		TerrainManager( const Settings& settings );
		~TerrainManager( void );
		
		void beginUpdate( void );

		template< typename Iter >
		void newOutline( Iter begin, Iter end );

		void endUpdate( void );

		template< typename Iter >
		void addOutline( Iter begin, Iter end );

		template< typename Iter >
		void subtractOutline( Iter begin, Iter end );


	private:
		struct Triangle
		{
			b2PolygonShape* s;
			std::size_t points[3];
			bool matching( const Triangle& other );
		};
		std::list<Triangle> m_triangles;
		std::list<Triangle> m_new_triangles;
		std::list<Triangle> m_old_triangles;
		typedef std::list<Triangle>::iterator Tri_iter;
		std::map<Triangle*,Tri_iter> m_tri_lookup;

		void processOldTriangles( void );
		bool processOldTriangles_inner( Tri_iter old_iter );
		void processNewTriangles( void );

		struct Vertex
		{
			Vertex( GLdouble* coords );
			Vertex( const b2Vec2& point );

			const b2Vec2 to_b2Vec2( void );

			GLdouble values[3];
		};
		std::vector<Vertex> m_points;

		static void tess_begin( GLenum type, TerrainManager* self );
		static void tess_end( TerrainManager* self );
		static void tess_vertex( std::size_t i, TerrainManager* self );
		static void tess_edge( GLboolean on_off, TerrainManager* self );
		static void tess_combine( GLdouble coords[3], void* vertex_data,
			GLfloat weight[4], std::size_t* i, TerrainManager* self );
		static void tess_error( GLenum gl_errno, TerrainManager* self );

		void send2tess( const b2Vec2& v );
		b2Vec2 vert2vec( std::size_t idx ) const;

		void initAABB( void );
		void processAABB( void );
		Tri_iter getIterFromTri( Triangle* tri );
		b2AABB m_aabb;

		Object m_obj;
		b2Body* m_body;
		b2World* m_world;

		GLUtesselator* m_tess;
		std::size_t m_tri_index;

		b2PolygonDef m_tridef;
		float m_flat_threshold;
	};

	template< typename Iter >
	void TerrainManager::
	newOutline( Iter begin, Iter end )
	{
		initAABB();

		gluTessBeginContour( m_tess );
		std::for_each( begin, end,
			boost::bind( &TerrainManager::send2tess, this, boost::arg<1>() )
		);
		gluTessEndContour( m_tess );

		processAABB();
	}

	template< typename Iter >
	void TerrainManager::
	addOutline( Iter begin, Iter end )
	{
		beginUpdate();
		newOutline( begin, end );
		endUpdate();
	}

	template< typename Iter >
	void TerrainManager::
	subtractOutline( Iter begin, Iter end )
	{
		beginUpdate();
		newOutline( std::reverse_iterator<Iter>(end),
						std::reverse_iterator<Iter>(begin) );
		endUpdate();
	}

}

#endif // TERRAIN_HPP_INCLUDED
