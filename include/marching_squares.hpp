#ifndef ENTO_MARCHING_SQUARES_HPP_INCLUDED
#define ENTO_MARCHING_SQUARES_HPP_INCLUDED

#include <boost/function.hpp>
#include <vector>
#include <complex>

namespace ento
{
   class Marching_squares
   {
   public:
      typedef boost::function<bool(unsigned x, unsigned y)> func_t;

      void setFunction( const func_t& func )
      {
         m_func = func;
      }

      void setMaxDim( unsigned x, unsigned y )
      {
         m_max_x = x;
         m_max_y = y;
      }

      void reset( void )
      {
         m_points.clear();
      }

      std::vector<std::complex<float> >::const_iterator points_begin( void ) const
      {
         return m_points.begin();
      }

      std::vector<std::complex<float> >::const_iterator points_end( void ) const
      {
         return m_points.end();
      }

      std::vector<std::complex<float> >::size_type points_size( void ) const
      {
         return m_points.size();
      }

      void execute( const std::complex<float>& start );
      void execute( void )
      { execute( std::complex<float>(0,0) ); }

   private:
      std::vector<std::complex<float> > m_points;
      unsigned m_max_x;
      unsigned m_max_y;
      func_t m_func;
   };
}

#endif // ENTO_MARCHING_SQUARES_HPP_INCLUDED
