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

         float min_len_sqrd;

         b2AABB aabb;
         b2World* world;
      };

      TerrainManager( const Settings& settings );
      ~TerrainManager( void );

      void beginUpdate( void );

      template< typename Iter >
      void newOutline( Iter begin, Iter end );

      void newVertex( const b2Vec2& vec );

      void endUpdate( void );

      template< typename Iter >
      void addOutline( Iter begin, Iter end );

      template< typename Iter >
      void subtractOutline( Iter begin, Iter end );


   private:
      struct Polygon
      {
         b2PolygonShape* s;
         int32 proxyID;
         std::size_t num_points;
         std::size_t points[8];
      };
      std::list<Polygon> m_polygons;
      std::list<Polygon> m_new_polygons;
      std::list<Polygon> m_old_polygons;
      typedef std::list<Polygon>::iterator Poly_iter;
      std::map<Polygon*,Poly_iter> m_poly_lookup;

      void processOldTriangles( void );
      bool processOldTriangles_inner( Poly_iter old_iter );
      void processNewTriangles( void );

      struct Vertex
      {
         Vertex( GLdouble* coords );
         Vertex( const b2Vec2& point );
         GLdouble values[3];
      };
      std::vector<Vertex> m_points;

      /// keys store the indices of the points of the edge that two
      /// polygons share.
      struct Key
      {
         Key( std::size_t a_, std::size_t b_)
          : lo(a_<b_?a_:b_),
            hi(a_<b_?b_:a_)
         { }

         std::size_t lo; ///< index into m_points
         std::size_t hi; ///< index into m_points

         /// simple comparator for keys
         bool operator<( const Key& rhs ) const
         {
            if( lo < rhs.lo )
            {
               return true;
            }

            if( lo == rhs.lo && hi < rhs.hi )
            {
               return true;
            }

            return false;
         }
      };

      /// simply store iterators pointing to both polygons that share the
      /// edge associated with its key
      struct EdgeInfo
      {
         Poly_iter a; ///< polygon share edge in key
         Poly_iter b; ///< polygon sharing edge in key
      };

      typedef std::map<Key,EdgeInfo> edge_map_t;
      typedef edge_map_t::iterator Edge_iter;
      std::map<Key,EdgeInfo> m_edge_lookup;

      void remove_slivers( void );
      bool valid_triangle( const Polygon& p ) const;
      void rotate_to_edge( Polygon& p, const Key& k ) const;
      void get_adjacent_edges( const Polygon& p, b2Vec2& ccw, b2Vec2& cw ) const;
      void process_merge( void );
      void do_merge( Poly_iter a, Poly_iter b );

      static void tess_begin( GLenum type, TerrainManager* self );
      static void tess_end( TerrainManager* self );
      static void tess_vertex( std::size_t i, TerrainManager* self );
      static void tess_edge( GLboolean on_off, TerrainManager* self );
      static void tess_combine( GLdouble coords[3], void* vertex_data,
                                GLfloat weight[4], std::size_t* i, TerrainManager* self );
      static void tess_error( GLenum gl_errno, TerrainManager* self );

      void initAABB( void );
      void processAABB( void );
      b2AABB m_aabb;

      Poly_iter poly2iter( Polygon* poly ) const;
      b2AABB poly2aabb( const Polygon& poly ) const;
      b2Vec2 point2vec( std::size_t point ) const;
      bool same( const Polygon& lhs, const Polygon& rhs ) const;

      Object m_obj;
      b2Body* m_body;
      b2World* m_world;

      class CollDet_cb : public b2PairCallback
      {
      public:
         virtual void* PairAdded(void *proxyUserData1, void *proxyUserData2) { return NULL; }
         virtual void PairRemoved(void *proxyUserData1, void *proxyUserData2, void *pairUserData) { }
      } m_colldet_cb;

      b2BroadPhase m_colldet;
      

      GLUtesselator* m_tess;
      std::size_t m_tri_index;

      b2PolygonDef m_tridef;
      float m_min_len_sqrd;
   };

   template< typename Iter >
   void TerrainManager::
   newOutline( Iter begin, Iter end )
   {
      initAABB();

      gluTessBeginContour( m_tess );
      std::for_each( begin, end,
                     boost::bind( &TerrainManager::newVertex, this, boost::arg<1>() )
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
