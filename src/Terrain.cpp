#include "Terrain.hpp"

#include "Object.hpp"

#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <iostream>

namespace ento
{

TerrainManager::Settings::Settings( void )
 : flat_threshold( 0.01f ), world(NULL)
{
	ground_def.friction = 0.5f;
	ground_def.restitution = 0.5f;
	ground_def.vertexCount = 3;
}

TerrainManager::TerrainManager( const TerrainManager::Settings& settings )
 : m_obj(Object::STATIC_TERRAIN), m_world( settings.world ),
	m_tess( gluNewTess() ), m_tri_index(0),
	m_tridef( settings.ground_def ),
	m_flat_threshold( settings.flat_threshold )
{
	if( ! m_tess )
		throw std::runtime_error( "out of memory for OpenGL" );
	
	gluTessNormal( m_tess, 0.0, 0.0, 1.0 );
	gluTessProperty( m_tess, GLU_TESS_WINDING_RULE, GLU_TESS_WINDING_POSITIVE );

	gluTessCallback( m_tess, GLU_TESS_BEGIN_DATA,
		reinterpret_cast<void(*)()>(&TerrainManager::tess_begin) );

	gluTessCallback( m_tess, GLU_TESS_END_DATA,
		reinterpret_cast<void(*)()>(&TerrainManager::tess_end) );

	gluTessCallback( m_tess, GLU_TESS_EDGE_FLAG_DATA,
		reinterpret_cast<void(*)()>(&TerrainManager::tess_edge) );

	gluTessCallback( m_tess, GLU_TESS_VERTEX_DATA,
		reinterpret_cast<void(*)()>(&TerrainManager::tess_vertex) );

	gluTessCallback( m_tess, GLU_TESS_COMBINE_DATA,
		reinterpret_cast<void(*)()>(&TerrainManager::tess_combine) );

	gluTessCallback( m_tess, GLU_TESS_ERROR_DATA,
		reinterpret_cast<void(*)()>(&TerrainManager::tess_error) );

	m_body = m_world->GetGroundBody();
	m_body->SetUserData( &m_obj );
}

TerrainManager::~TerrainManager( void )
{
	gluDeleteTess(m_tess);
}

void TerrainManager::
beginUpdate( void )
{
	gluTessBeginPolygon( m_tess, this );
}

void TerrainManager::
endUpdate( void )
{
	gluTessEndPolygon( m_tess );
	processOldTriangles();
	processNewTriangles();
}

void TerrainManager::
send2tess( const b2Vec2& v )
{
	if( v.x < m_aabb.lowerBound.x )
		{ m_aabb.lowerBound.x = v.x; }
	if( v.y < m_aabb.lowerBound.y )
		{ m_aabb.lowerBound.y = v.y; }

	if( v.x > m_aabb.upperBound.x )
		{ m_aabb.upperBound.x = v.x; }
	if( v.y > m_aabb.upperBound.y )
		{ m_aabb.upperBound.y = v.y; }

	m_points.push_back( Vertex(v) );
	
	gluTessVertex( m_tess, m_points.back().values,
			reinterpret_cast<void*>( m_points.size()-1 ) 
		);
}
void TerrainManager::
tess_begin( GLenum type, TerrainManager* self )
{
	if( type != GL_TRIANGLES )
		throw std::runtime_error( "GLtessellator must only use GL_TRIANGLES" );
}

void TerrainManager::
tess_end( TerrainManager* self )
{ }

void TerrainManager::
tess_vertex( std::size_t i, TerrainManager *self )
{
	if( self->m_tri_index == 0 )
	{
		self->m_new_triangles.push_back( Triangle() );
	}

	Triangle& t = self->m_new_triangles.back();
	t.points[self->m_tri_index] = i;
	++self->m_tri_index;

	if( self->m_tri_index == 3 )
	{
		self->m_tri_index = 0;
	}
}

void TerrainManager::
tess_edge( GLboolean, TerrainManager* self ) {}

void TerrainManager::
tess_combine( GLdouble coords[3], void* vertex_data, GLfloat weight[4],
					std::size_t * i, TerrainManager* self )
{
	self->m_points.push_back( Vertex( coords ) );
	*i = self->m_points.size()-1;
}

void TerrainManager::tess_error( GLenum gl_errno, TerrainManager *self )
{
	throw std::runtime_error( reinterpret_cast<const char*>(gluErrorString( gl_errno )) );
}

void TerrainManager::
initAABB( void )
{
	const float infinity = std::numeric_limits<float>::infinity();
	m_aabb.lowerBound.Set( infinity, infinity );
	m_aabb.upperBound.Set( -infinity, -infinity );
}

void TerrainManager::
processAABB( void )
{
	const std::size_t max_query = 16;
	b2Shape* query[max_query];
	std::size_t count = m_world->Query(m_aabb, query, max_query);
	for( unsigned i=0; i<count; ++i )
	{
		Object* o = reinterpret_cast<Object*>( query[i]->GetBody()->GetUserData());
		if( o->type() == Object::STATIC_TERRAIN )
		{
			Triangle* t = reinterpret_cast<Triangle*>(query[i]->GetUserData());
			//move triangle into old triangles list
			m_old_triangles.splice( m_old_triangles.end(), m_triangles, getIterFromTri(t) );

			gluTessBeginContour( m_tess );
			gluTessVertex( m_tess, m_points[t->points[0]].values,
					reinterpret_cast<void*>( t->points[0] ) );
			gluTessVertex( m_tess, m_points[t->points[1]].values,
					reinterpret_cast<void*>( t->points[1] ) );
			gluTessVertex( m_tess, m_points[t->points[2]].values,
					reinterpret_cast<void*>( t->points[2] ) );
			gluTessEndContour( m_tess );
		}
	}
}

TerrainManager::Tri_iter TerrainManager::
getIterFromTri( Triangle* tri )
{
	std::map<Triangle*,Tri_iter>::iterator found;
	found = m_tri_lookup.find(tri);
	if( found == m_tri_lookup.end() )
	{
		throw std::runtime_error("Triangle lookup failed");
	}
	return found->second;
}

/// the inner loop for processOldTriangles
/// @remarks removes 'new' triangles is they match existing triangles
/// @return true if matching triangle found
bool TerrainManager::
processOldTriangles_inner( Tri_iter old_iter )
{
	Tri_iter new_iter = m_new_triangles.begin();
	Tri_iter new_end = m_new_triangles.end();
	while( new_iter != new_end )
	{
		if( new_iter->matching( *old_iter ) )
		{
			new_iter = m_new_triangles.erase(new_iter);
			return true;
		}
		++new_iter;
	}
	return false;
}

void TerrainManager::
processOldTriangles( void )
{
	Tri_iter old_iter = m_old_triangles.begin();
	Tri_iter old_end = m_old_triangles.end();
	while( old_iter != old_end )
	{
		if( processOldTriangles_inner( old_iter ) )
		{
			Tri_iter tmp = old_iter++;
			// move tmp from old tri list to tri list
			m_triangles.splice( m_triangles.end(), m_old_triangles, tmp );
			assert(false); // this should eventually happen
		}
		else
		{
			m_body->DestroyShape( old_iter->s );
			m_tri_lookup.erase( m_tri_lookup.find(&(*old_iter)) );
			++old_iter;
		}
	}
	m_old_triangles.clear();
}

void TerrainManager::
processNewTriangles( void )
{
	Tri_iter iter = m_new_triangles.begin();
	Tri_iter end = m_new_triangles.end();
	while( iter != end )
	{
		m_tridef.userData = &(*iter);

		m_tridef.vertices[0] = m_points[iter->points[0]].to_b2Vec2();
		m_tridef.vertices[1] = m_points[iter->points[1]].to_b2Vec2();
		m_tridef.vertices[2] = m_points[iter->points[2]].to_b2Vec2();

		b2Vec2 side_a = m_tridef.vertices[0] - m_tridef.vertices[1];
		b2Vec2 side_b = m_tridef.vertices[2] - m_tridef.vertices[1];

		side_a.Normalize();
		side_b.Normalize();

		if( std::abs(b2Cross( side_a, side_b )) < m_flat_threshold )
		{
			std::cout << "erased Triangle!!!" << std::endl;
			iter = m_new_triangles.erase(iter);
		}
		else
		{
			iter->s = reinterpret_cast<b2PolygonShape*>(
					m_body->CreateShape(&m_tridef));
			m_tri_lookup[&(*iter)] = iter;
			++iter;
		}
	}
	// move entire new list into tri list
	m_triangles.splice( m_triangles.end(), m_new_triangles );
}

bool TerrainManager::Triangle::
matching( const TerrainManager::Triangle& other )
{
	if( points[0] == other.points[0] &&
		 points[1] == other.points[1] &&
		 points[2] == other.points[2] )
	{
		return true;
	}
	else if( points[1] == other.points[0] &&
	         points[2] == other.points[1] &&
				points[0] == other.points[2] )
	{
		return true;
	}
	else if( points[2] == other.points[0] &&
	         points[0] == other.points[1] &&
				points[1] == other.points[2] )
	{
		return true;
	}
	return false;
}

TerrainManager::Vertex::Vertex( GLdouble* coords )
{
	values[0] = coords[0];
	values[1] = coords[1];
	values[2] = 0.0;
}

TerrainManager::Vertex::Vertex( const b2Vec2& vec )
{
	values[0] = vec.x;
	values[1] = vec.y;
	values[2] = 0.0;
}

const b2Vec2 TerrainManager::Vertex::
to_b2Vec2( void )
{
	return b2Vec2( values[0], values[1] );
}


}
