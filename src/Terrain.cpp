#include "Terrain.hpp"

#include "Object.hpp"

#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <iostream>
#include <complex>

namespace
{
   std::ostream& operator << ( std::ostream& out, b2Vec2 const& vec )
   {
      out << std::complex<float>(vec.x,vec.y);
      return out;
   }
}

namespace ento
{
   namespace // anonymous
   {
      /// initialize and AABB so that any point expanding it will
      /// set upper and lower bounds to that value
      /// @param aabb
      inline void initAABB( b2AABB& aabb )
      {
         const float infinity = std::numeric_limits<float>::infinity();
         aabb.lowerBound.Set( infinity, infinity );
         aabb.upperBound.Set( -infinity, -infinity );
      }

      /// expand an AABB so that it encompasses vec
      /// @param aabb [IN-OUT] AABB to update
      /// @param vec point to encompass
      inline void expandAABB( b2AABB& aabb, const b2Vec2& vec )
      {
         if( vec.x < aabb.lowerBound.x )
         {
            aabb.lowerBound.x = vec.x;
         }
         if( vec.y < aabb.lowerBound.y )
         {
            aabb.lowerBound.y = vec.y;
         }

         if( vec.x > aabb.upperBound.x )
         {
            aabb.upperBound.x = vec.x;
         }
         if( vec.y > aabb.upperBound.y )
         {
            aabb.upperBound.y = vec.y;
         }
      }

   } // anonymous namespace

   /// threshold formula:
   /// let A be equilateral triangle.
   /// min dist from centroid is b2_toiSlop
   /// centroid is 1/3 of height
   /// height ie 3 * b2_toiSlop
   /// tan(60) = height / (width/2)
   /// width = 2 * height / tan(60)
   /// width = 2 * height * sqrt(3) / 3 
   /// width = 2 * b2_toiSlop * sqrt(3)
   /// width**2 = 4 * b2_toiSlop**2 * 3
   /// width**2 = 12 * b2_toiSlop**2
   /// width**2 = 12 * 0.04**2
   /// width**2 = 0.0195
   TerrainManager::Settings::Settings( void )
    : min_len_sqrd( 12 * b2_toiSlop * b2_toiSlop + 0.005f ), world(NULL)
   {
      ground_def.friction = 0.5f;
      ground_def.restitution = 0.5f;
      ground_def.vertexCount = 3;
   }

   TerrainManager::TerrainManager( const TerrainManager::Settings& settings )
    : m_obj(Object::e_Static_Terrain), m_world( settings.world ),
      m_colldet( settings.aabb, &m_colldet_cb ),
      m_tess( gluNewTess() ), m_tri_index(0),
      m_tridef( settings.ground_def ),
      m_min_len_sqrd( settings.min_len_sqrd )
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
   newVertex( const b2Vec2& v )
   {
      expandAABB( m_aabb, v );

      m_points.push_back( Vertex(v) );

      gluTessVertex( m_tess, m_points.back().values,
                     reinterpret_cast<void*>( m_points.size()-1 ) );
   }

   void TerrainManager::
   endUpdate( void )
   {
      gluTessEndPolygon( m_tess );
      processOldTriangles();
      processNewTriangles();
   }

   void TerrainManager::
   tess_begin( GLenum type, TerrainManager* self )
   {
      if( type != GL_TRIANGLES )
         throw std::runtime_error( "GLtessellator must only use GL_TRIANGLES" );
   }

   void TerrainManager::
   tess_end( TerrainManager* self )
   {
   }

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
   tess_edge( GLboolean, TerrainManager* self )
   {
   }

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
      ento::initAABB( m_aabb );
   }

   void TerrainManager::
   processAABB( void )
   {
      const int32 max_query = 64;
      Triangle* query[max_query];
      int32 count = m_colldet.Query(m_aabb, reinterpret_cast<void**>(query), max_query);
      assert( count < max_query );
      for( int32 i=0; i<count; ++i )
      {
         Triangle& t = *query[i];
         //move triangle into old triangles list
         m_old_triangles.splice( m_old_triangles.end(), m_triangles, 
                                 tri2iter( &t ) );

         gluTessBeginContour( m_tess );
         gluTessVertex( m_tess, m_points[t.points[0]].values,
                        reinterpret_cast<void*>( t.points[0] ) );
         gluTessVertex( m_tess, m_points[t.points[1]].values,
                        reinterpret_cast<void*>( t.points[1] ) );
         gluTessVertex( m_tess, m_points[t.points[2]].values,
                        reinterpret_cast<void*>( t.points[2] ) );
         gluTessEndContour( m_tess );
      }
   }

/// the inner loop for processOldTriangles
/// @remarks removes 'new' triangles if they match existing triangles
/// @return true if matching triangle found
   bool TerrainManager::
   processOldTriangles_inner( Tri_iter old_iter )
   {
      Tri_iter new_iter = m_new_triangles.begin();
      Tri_iter new_end = m_new_triangles.end();
      while( new_iter != new_end )
      {
         if( same( *new_iter, *old_iter ) )
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
         }
         else
         {
            if( old_iter->s )
            {
               m_body->DestroyShape( old_iter->s );
            }
            m_colldet.DestroyProxy( old_iter->proxyID );
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

         m_tridef.vertices[0] = point2vec( iter->points[0] );
         m_tridef.vertices[1] = point2vec( iter->points[1] );
         m_tridef.vertices[2] = point2vec( iter->points[2] );

         b2Vec2 side_a = m_tridef.vertices[1] - m_tridef.vertices[0];
         b2Vec2 side_b = m_tridef.vertices[2] - m_tridef.vertices[0];
         b2Vec2 side_c = m_tridef.vertices[2] - m_tridef.vertices[1];

         float len_a = side_a.LengthSquared();
         float len_b = side_b.LengthSquared();
         float len_c = side_c.LengthSquared();

         float area = b2Cross( side_a, side_b ) * 0.5f;

         if( area <= std::numeric_limits<float>::epsilon() )
         {
            std::cerr << "Ignoring degenerate triangle\n";
            iter = m_new_triangles.erase(iter);
         }
         else
         {
            iter->proxyID = m_colldet.CreateProxy( tri2aabb(*iter), &(*iter) );
            if( side_a.LengthSquared() > m_min_len_sqrd &&
                side_b.LengthSquared() > m_min_len_sqrd &&
                side_c.LengthSquared() > m_min_len_sqrd &&
                area > 0.06f )
            {
               iter->s = static_cast<b2PolygonShape*>( m_body->CreateShape(&m_tridef));
            }
            else
            {
               std::cerr << "Intangible triangle\n";
               iter->s = NULL;
            }
            m_tri_lookup[&(*iter)] = iter;
            ++iter;
         }
      }
      // move entire new list into tri list
      m_triangles.splice( m_triangles.end(), m_new_triangles );
   }

   b2Vec2 TerrainManager::
   point2vec( std::size_t point ) const
   {
      return b2Vec2( m_points[point].values[0], m_points[point].values[1] );
   }

   TerrainManager::Tri_iter TerrainManager::
   tri2iter( Triangle* tri ) const
   {
      std::map<Triangle*,Tri_iter>::const_iterator found;
      found = m_tri_lookup.find(tri);
      if( found == m_tri_lookup.end() )
      {
         throw std::runtime_error("Triangle lookup failed");
      }
      return found->second;
   }

   b2AABB TerrainManager::
   tri2aabb( const TerrainManager::Triangle& tri ) const
   {
      b2AABB aabb;
      ento::initAABB(aabb);

      ento::expandAABB( aabb, point2vec(tri.points[0]) );
      ento::expandAABB( aabb, point2vec(tri.points[1]) );
      ento::expandAABB( aabb, point2vec(tri.points[2]) );

      return aabb;
   }

   /// @return whether lhs is the same triangle as rhs
   /// @param lhs
   /// @param rhs
   bool TerrainManager::
   same ( const TerrainManager::Triangle& lhs,
          const TerrainManager::Triangle& rhs ) const
   {
      if( rhs.points[0] == lhs.points[0] &&
          rhs.points[1] == lhs.points[1] &&
          rhs.points[2] == lhs.points[2] )
      {
         return true;
      }
      else if( rhs.points[1] == lhs.points[0] &&
               rhs.points[2] == lhs.points[1] &&
               rhs.points[0] == lhs.points[2] )
      {
         return true;
      }
      else if( rhs.points[2] == lhs.points[0] &&
               rhs.points[0] == lhs.points[1] &&
               rhs.points[1] == lhs.points[2] )
      {
         return true;
      }
      return false;
   }

//
// --- TerrainManager::Vertex ---
//
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


}
