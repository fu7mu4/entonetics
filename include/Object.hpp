#ifndef ENTO_OBJECT_HPP_INCLUDED
#define ENTO_OBJECT_HPP_INCLUDED

#include <Box2D.h>

namespace ento
{
   /// Base for all game objects
   class Object
   {
   public:

      /// list of all game object types
      enum Type
      {
         e_Static_Terrain,
         e_Entomon,
         e_Shot
      };

      Object( Type type );

      virtual ~Object( void )
      {
      }

      /// @return whether the next object should see the contact
      virtual bool addContact( const b2ContactResult& point, b2Shape* s )
      {
         return true;
      }

      /// @return whether the next object should see the collision
      virtual bool addCollision( const b2ContactPoint& point, b2Shape* s )
      {
         return true;
      }

      virtual int collisionPriority( void ) 
      {
         return 0;
      }

      virtual void preStep( float dt )
      {
      }

      virtual void postStep( float dt )
      {
      }

      inline Type type( void );

   private:
      const Type m_type; ///< the game object type
   };

   /// @return the object type
   inline Object::Type Object::
   type( void )
   {
      return m_type;
   }
}// namespace ento

#endif // ENTO_OBJECT_HPP_INCLUDED
