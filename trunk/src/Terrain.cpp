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

   b2PolygonDef m_tridef;
   std::ostream& operator << ( std::ostream& out, const b2PolygonDef& p )
   {
      unsigned last = p.vertexCount-1;
      float area = 0.f;
      float perimeter = 0.f;
      out << p.vertexCount;
      for( unsigned i=0; i<p.vertexCount; ++i )
      {
         area += b2Cross( p.vertices[last], p.vertices[i] );
         perimeter += (p.vertices[i] - p.vertices[last]).Length();
         last = i;
      }
      area *= 0.5;

      //out << " Area: " << area << " Permeter: " << perimeter;
      //out << " p/a: " << perimeter/area << " p^2/a: " << (perimeter*perimeter)/area;
      out << " p^2/a: " << (perimeter*perimeter)/area;
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
         const float epsilon = 0.1f;
         if( vec.x < aabb.lowerBound.x )
         {
            aabb.lowerBound.x = vec.x - epsilon;
         }
         if( vec.y < aabb.lowerBound.y )
         {
            aabb.lowerBound.y = vec.y - epsilon;
         }

         if( vec.x > aabb.upperBound.x )
         {
            aabb.upperBound.x = vec.x + epsilon;
         }
         if( vec.y > aabb.upperBound.y )
         {
            aabb.upperBound.y = vec.y + epsilon;
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
         self->m_new_polygons.push_back( Polygon() );
         self->m_new_polygons.back().num_points = 3;
      }

      Polygon& t = self->m_new_polygons.back();
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
      Polygon* query[max_query];
      int32 count = m_colldet.Query(m_aabb, reinterpret_cast<void**>(query), max_query);
      assert( count < max_query );
      for( int32 i=0; i<count; ++i )
      {
         Polygon& p = *query[i];
         //move triangle into old triangles list
         m_old_polygons.splice( m_old_polygons.end(), m_polygons, 
                                 poly2iter( &p ) );

         gluTessBeginContour( m_tess );
         for( unsigned i=0; i<p.num_points; ++i )
         {
            gluTessVertex( m_tess, m_points[p.points[i]].values,
                           reinterpret_cast<void*>( p.points[i] ) );
         }
         gluTessEndContour( m_tess );
      }
   }

/// the inner loop for processOldTriangles
/// @remarks removes 'new' triangles if they match existing triangles
/// @return true if matching triangle found
   bool TerrainManager::
   processOldTriangles_inner( Poly_iter old_iter )
   {
      Poly_iter new_iter = m_new_polygons.begin();
      Poly_iter new_end = m_new_polygons.end();
      while( new_iter != new_end )
      {
         if( false && same( *new_iter, *old_iter ) )
         {
            new_iter = m_new_polygons.erase(new_iter);
            return true;
         }
         ++new_iter;
      }
      return false;
   }

   void TerrainManager::
   processOldTriangles( void )
   {
      Poly_iter old_iter = m_old_polygons.begin();
      Poly_iter old_end = m_old_polygons.end();
      std::size_t old_size = m_old_polygons.size();
      std::cerr << old_size << " to be updated\n";
      while( old_iter != old_end )
      {
         if( processOldTriangles_inner( old_iter ) )
         {
            Poly_iter tmp = old_iter++;
            // move tmp from old tri list to tri list
            m_polygons.splice( m_polygons.end(), m_old_polygons, tmp );
            std::cerr << "1 polygon merge\n";
         }
         else
         {
            if( old_iter->s )
            {
               m_body->DestroyShape( old_iter->s );
            }
            m_colldet.DestroyProxy( old_iter->proxyID );
            m_poly_lookup.erase( m_poly_lookup.find(&(*old_iter)) );
            ++old_iter;
         }
      }
      m_old_polygons.clear();
   }

   void TerrainManager::
   processNewTriangles( void )
   {
      remove_slivers();

      Poly_iter iter = m_new_polygons.begin();
      Poly_iter end = m_new_polygons.end();
      std::cerr << m_new_polygons.size() << " new triangles to be added\n";
      while( iter != end )
      {
         if( ! valid_triangle(*iter) )
         {
            iter = m_new_polygons.erase(iter);
            std::cerr << "throwing away a triangle!\n";
            continue;
         }

         // build up edge info for this polygon
         unsigned last = iter->num_points-1;
         unsigned i = 0;
         while( i < iter->num_points )
         {
            Key k( iter->points[last],iter->points[i]);;
            std::map<Key,EdgeInfo>::iterator found;
            found = m_edge_lookup.find(k);
            // update current edge
            if( found != m_edge_lookup.end() )
            {
               assert( found->second.b == end );
               found->second.b = iter;
            }
            else // create new edge
            {
               EdgeInfo ei;
               ei.a = iter;
               ei.b = end;
               bool success = m_edge_lookup.insert( std::make_pair(k,ei) ).second;
               assert(success);
            }
            last = i++;
         }// for  all points
         ++iter;
      }// while iter is not end

      // ignore all unshared edges
      Edge_iter e_iter = m_edge_lookup.begin();
      Edge_iter e_end = m_edge_lookup.end();
      while( e_iter != e_end )
      {
         if( e_iter->second.a == end ||
             e_iter->second.b == end )
         {
            m_edge_lookup.erase(e_iter++);
         }
         else
         {
            ++e_iter;
         }
      }

      std::cerr << m_edge_lookup.size() << " shared edges\n";

      process_merge();

      std::cerr << m_new_polygons.size() << " new polygons to be added\n";

      // finish all remaining new polygons
      iter = m_new_polygons.begin();
      while( iter != end )
      {
         m_tridef.userData = &(*iter);
         m_tridef.vertexCount = iter->num_points;
         for( int i=0; i<m_tridef.vertexCount; ++i )
         {
            m_tridef.vertices[i] = point2vec( iter->points[i] );
         }
         std::cerr << "creating polygon: " << m_tridef << '\n';
         iter->proxyID = m_colldet.CreateProxy( poly2aabb(*iter), &(*iter) );
         iter->s = static_cast<b2PolygonShape*>( m_body->CreateShape(&m_tridef));
         m_poly_lookup[&(*iter)] = iter;
         ++iter;
      }

      // move entire new list into the real list
      m_polygons.splice( m_polygons.end(), m_new_polygons );
      assert( m_new_polygons.empty() );
   }

   void TerrainManager::
   remove_slivers( void )
   {
      Poly_iter iter = m_new_polygons.begin();
      Poly_iter end = m_new_polygons.end();

      while( iter != end )
      {
         assert( iter->num_points == 3 );

         bool  removed_triangle = false;
         unsigned last = 2;
         for( unsigned i=0; i<3; ++i )
         {
            b2Vec2 edge = point2vec( iter->points[i]) - point2vec( iter->points[last]);
            if( edge.LengthSquared() < 1 )
            {
               removed_triangle = true;
               // keep the lower index, that way we won't invalidate any of the
               //  current polygons, this is the same reason the merge point
               //  is only deleted instead of merged
               std::size_t keep = std::min( iter->points[i], iter->points[last] );
               std::size_t merge = std::max( iter->points[i], iter->points[last] );
               iter = m_new_polygons.erase( iter );
               std::cerr << "removed a sliver " << edge << "\n";

               // update all other triangles
               Poly_iter iter2 = m_new_polygons.begin();
               while( iter2 != end )
               {
                  std::size_t* points = iter2->points;
                  std::size_t* end_ptr = points + iter2->num_points;

                  std::size_t* merge_ptr = std::find( points, end_ptr, merge );
                  if( merge_ptr != end_ptr )
                  {  // remove the ones losing and edge
                     // these will have both the keep and merge ends of the edge
                     if( std::find( points, end_ptr, keep ) != end_ptr )
                     {
                        std::cerr << "chain removing a sliver\n";
                        // in case we're removing iter
                        if( iter == iter2 )
                           { iter = iter2 = m_new_polygons.erase( iter2 ); }
                        else
                           { iter2 = m_new_polygons.erase( iter2 ); }
                     }
                     else
                     { // just updating a point, still has three edges
                        *merge_ptr = keep;
                     }
                  }// if merge present
                  else
                  {
                     ++iter2;
                  }
               }// update all new triangles

               break; // just removed this triangle stop
                      // iterating over its edges
            }// if edge too short

            last = i;
         }// for each edge

         // removing a triangle advances the iterator.
         if( !removed_triangle  )
            { ++iter; }
      }// loop over all new triangles
   }

   /// detect degenerate (flat) triangles
   /// @param p triangle to check ( must be 3 sided poly )
   /// @return whether p is a valid triangle
   bool TerrainManager::
   valid_triangle( const TerrainManager::Polygon& p ) const
   {
      assert( p.num_points == 3 );
      b2Vec2 one;
      b2Vec2 two;
      get_adjacent_edges(p,one,two);
      return b2Cross( two, one) > std::numeric_limits<float>::epsilon();
   }

   /// process each edge info, if the polygons can be merged, send them to do_merge
   void TerrainManager::
   process_merge( void )
   {
      while( !m_edge_lookup.empty() )
      {
         std::map<Key,EdgeInfo>::iterator iter = m_edge_lookup.begin();
         const Key k = iter->first;
         Poly_iter a = iter->second.a;
         Poly_iter b = iter->second.b;

         assert( a != m_new_polygons.end() );
         assert( b != m_new_polygons.end() );

         rotate_to_edge( *a, k );
         b2Vec2 a_ccw;
         b2Vec2 a_cw;
         get_adjacent_edges( *a, a_ccw, a_cw );

         rotate_to_edge( *b, k );
         b2Vec2 b_ccw;
         b2Vec2 b_cw;
         get_adjacent_edges( *b, b_ccw, b_cw );

         m_edge_lookup.erase(iter);

         const float epsilon = std::numeric_limits<float>::epsilon();

         if( b2Cross( a_ccw, b_cw ) > epsilon &&
             b2Cross( b_ccw, a_cw ) > epsilon )
         {
            do_merge( a, b );
            m_new_polygons.erase( b );
         }
      }// while
   }

   /// rotate polygons points so that the start and end point are the shared edge
   /// @param p polygon to rotate
   /// @param k key of edge to rotate to
   void TerrainManager::
   rotate_to_edge( TerrainManager::Polygon& p, const TerrainManager::Key& k ) const
   {
      // find index of end of edge
      std::size_t index;
      if( p.points[0] == k.lo || p.points[0] == k.hi )
      {
         if( p.points[p.num_points-1] == k.lo || p.points[p.num_points-1] == k.hi )
         {
            index = 0;
         }
         else
         {
            assert( p.points[1] == k.lo || p.points[1] == k.hi );
            index = 1;
         }
      }
      else
      {
         for( unsigned i=1; i<p.num_points; ++i )
         {
            if( p.points[i] == k.lo || p.points[i] == k.hi )
            {
               assert( p.points[i+1] == k.lo || p.points[i+1] == k.hi );
               index = i + 1;
               break;
            }
         }
      }

      std::rotate( p.points, p.points+index, p.points+p.num_points );
   }

   /// get the normalized edge leading away from the shared edge
   /// @param primary will contain CCW edge
   /// @param secondary will contain CW edge
   void TerrainManager::
   get_adjacent_edges( const TerrainManager::Polygon& p,
                       b2Vec2& ccw, b2Vec2& cw ) const
   {
      assert( p.num_points > 2 );
      ccw = point2vec(p.points[1]) - point2vec(p.points[0]);
      ccw *= b2InvSqrt(ccw.LengthSquared());
      cw = point2vec(p.points[p.num_points - 2]) -
                  point2vec(p.points[p.num_points - 1]);
      cw *= b2InvSqrt(cw.LengthSquared());
   }

   /// merge b into a
   /// @param a polygon sharing an edge
   /// @param b polygon sharing an edge
   void TerrainManager::
   do_merge( TerrainManager::Poly_iter a, TerrainManager::Poly_iter b )
   {
      assert( a->points[0] == b->points[ b->num_points-1] );
      assert( b->points[0] == a->points[ a->num_points-1] );
      
      // skip the edge points (the first and last point)
      for( unsigned i=1; i<b->num_points-1; ++i )
      {
         a->points[ a->num_points++ ] = b->points[i];
      }

      // update edge list so that edges that used to be shared with b
      // are now shared with a
      std::map<Key,EdgeInfo>::iterator iter, end;
      iter = m_edge_lookup.begin();
      end = m_edge_lookup.end();
      while( iter != end )
      {
         if( b == iter->second.a )
         {
            if( iter->second.b->num_points + a->num_points > b2_maxPolygonVertices + 2 )
            {
               // the combined polygon would have too many vertices, so just
               // discard it
               m_edge_lookup.erase( iter++ );
            }
            else
            {
               iter->second.a = a;
               ++iter;
            }
         }
         else if( b == iter->second.b )
         {
            if( iter->second.a->num_points + a->num_points > b2_maxPolygonVertices + 2 )
            {
               m_edge_lookup.erase( iter++ );
            }
            else
            {
               iter->second.b = a;
               ++iter;
            }
         }
         else
         {
            ++iter;
         }
      }

   }

   b2Vec2 TerrainManager::
   point2vec( std::size_t point ) const
   {
      return b2Vec2( m_points[point].values[0], m_points[point].values[1] );
   }

   TerrainManager::Poly_iter TerrainManager::
   poly2iter( Polygon* poly ) const
   {
      std::map<Polygon*,Poly_iter>::const_iterator found;
      found = m_poly_lookup.find(poly);
      if( found == m_poly_lookup.end() )
      {
         throw std::runtime_error("Triangle lookup failed");
      }
      return found->second;
   }

   b2AABB TerrainManager::
   poly2aabb( const TerrainManager::Polygon& poly ) const
   {
      b2AABB aabb;
      ento::initAABB(aabb);

      for( unsigned i=0; i<poly.num_points; ++i )
      {
         ento::expandAABB( aabb, point2vec(poly.points[i]) );
      }

      return aabb;
   }

   /// @return whether lhs is the same triangle as rhs
   /// @param lhs
   /// @param rhs
   bool TerrainManager::
   same ( const TerrainManager::Polygon& lhs,
          const TerrainManager::Polygon& rhs ) const
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
