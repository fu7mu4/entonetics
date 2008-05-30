#ifndef SINGLETON_HPP_INCLUDED
#define SINGLETON_HPP_INCLUDED

#include <boost/typetraits/aligned_storage.hpp>
#include <boost/typetraits/alignment_of.hpp>
#include <new>

namespace ento
{
   /**
    * usage: singleton<Foo>().bar()
    * 
    * There is no need to call desingleton.  It is very hard problem to 
    * get static objects to destruct in the correct order.  Our solution
    *  is to not destruct them
    * 
    * @param T      Type of the singleton
    * 
    * @return reference to Singleton of type T
    */
   template< typename T >
   T& singleton( void )
   {
      using namespace boost;
      aligned_storage<sizeof(T),alignment_of<T>::value> buffer;
      static T* s_single = new(reinterpret_cast<void*>(&buffer)) T;
      return *s_single;
   }
   
   /**
    * Destruct the singleton of type T
    * 
    * @param T      Type of singleton
    */
   template< typename T >
   void desingleton( void )
   {
      T& t = singleton<T>();
      t.~T();
   }
   
   /**
    * Recreate a singleton of type T after it has been destructed with desingleton
    * 
    * @param T      Type of singleton
    */
   template< typename T >
   void resingleton( void )
   {
      T& t = singleton<T>();
      new( reinterpret_cast<void*>(&t) ) T;
   }

} // namespace ento

#endif // SINGLETON_HPP_INCLUDED
