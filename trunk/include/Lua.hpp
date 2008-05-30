#ifndef ENTO_LUA_HPP_INCLUDED
#define ENTO_LUA_HPP_INCLUDED

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include <boost/shared_ptr.hpp>
#include <stdexcept>
#include <string>
#include "strand.hpp"
#include "Box2D.h"

namespace ento
{

   class Lua_Error: public std::runtime_error
   {
   public:
      Lua_Error( const std::string& err )
       : std::runtime_error( err )
      { }
   };

   class Lua
   {
   public:
      Lua();
      Lua( lua_State* state );

      typedef int Ref;
      static const Ref NO_REF = LUA_NOREF;

      lua_Number getGlobalNumber( const std::string& num_name );
      const std::string getGlobalString( const std::string& string_name);
      const b2Vec2 check_complex( int index =-1 );

      template< typename K >
      void* getRegistryDataPtr( K* reg_key )
      {
         push( reg_key );
         l_gettable( LUA_REGISTRYINDEX );

         if( ! l_islightuserdata() )
         {
            l_pop();
            throw Lua_Error( "not user_data" );
         }

         void* data = l_touserdata();
         l_pop();
         return data;
      }

      template< typename D, typename K >
      D* getRegistryData( K* reg_key )
      {
         return static_cast<D*>( getRegistryDataPtr( reg_key ) );
      }

      template< typename K >
      void setRegistryDataPtr( K* reg_key, void * data )
      {
         push( reg_key );
         push( data );
         l_settable( LUA_REGISTRYINDEX );
      }

      template< typename K, typename D >
      void setRegistryData( K* reg_key, D* data )
      {
         setRegistryDataPtr( reg_key, static_cast<void*>(data) );
      }

      void doFile( const std::string& file_name );

      void push( void )
      {
         l_pushnil();
      }

      void push( double number )
      {
         l_pushnumber( number );
      }

      void push( const std::string& str )
      {
         l_pushstring( str );
      }

      void push( const b2Vec2& v);

      template< typename T >
      void push( T* t )
      {
         l_pushlightuserdata( static_cast<void*>(t) );
      }

      template< typename T >
      void touserdata( int index,T*& ptr_ref )
      {
         ptr_ref = static_cast<T*>( l_touserdata( index ) );
      }

      template< typename T>
      T* touserdata( int index=-1 )
      {
         return reinterpret_cast<T*>( l_touserdata( index ) );
      }

      template< typename T>
      void checkudata( int index, const std::string& type,  T*& ptr_ref )
      {
         ptr_ref = *static_cast<T**>( L_checkudata( index, type ) );
      }

      template< typename T>
      void newuserdata( const T& copy )
      {
         void* lua_mem = l_newuserdata( sizeof(T) );
         new(lua_mem) T(copy);
      }

      void kwargerror( const std::string& kwarg, const std::string& extramsg );

      const std::string koptstring( int table_index, const std::string& key, const std::string& def );
      const std::string kcheckstring( int table_index, const std::string& key );

      lua_Integer koptinteger( int table_index, const std::string& key, lua_Integer def );
      lua_Integer kcheckinteger( int table_index, const std::string& key);

      bool koptboolean( int table_index, const std::string& key, bool def );
      bool kcheckboolean( int table_index, const std::string& key);

      void l_call( int narg, int nret )
      {
         lua_call( m_lua.get(), narg, nret );
      }

      void l_getfield( const std::string& key )
      {
         l_getfield( -1, key);
      }
      void l_getfield( int index, const std::string& key )
      {
         lua_getfield( m_lua.get(), index, key.c_str() );
      }

      void l_getglobal( const std::string& g_name)
      {
         lua_getglobal( m_lua.get(), g_name.c_str() );
      }

      void l_getinfo( const std::string& what, lua_Debug& debug )
      {
         lua_getinfo( m_lua.get(), what.c_str(), &debug );
      }

      bool l_getstack( lua_Debug& ar )
      {
         return lua_getstack( m_lua.get(), 0, &ar );
      }
      bool l_getstack( int level, lua_Debug& ar )
      {
         return lua_getstack( m_lua.get(), level, &ar );
      }

      void l_gettable( int index=-1 )
      {
         lua_gettable( m_lua.get(), index );
      }

      int l_gettop()
      {
         return lua_gettop( m_lua.get() );
      }

      bool l_isboolean( int index=-1 )
      {
         return lua_isboolean( m_lua.get(), index );
      }

      bool l_islightuserdata( int index=-1 )
      {
         return lua_islightuserdata( m_lua.get(), index );
      }

      bool l_isnil( int index=-1 )
      {
         return lua_isnil( m_lua.get(), index );
      }

      bool l_isnoneornil( int index=-1 )
      {
         return lua_isnoneornil( m_lua.get(), index );
      }

      bool l_isnumber( int index=-1 )
      {
         return lua_isnumber( m_lua.get(), index );
      }

      bool l_isstring( int index=-1 )
      {
         return lua_isstring( m_lua.get(), index );
      }

      bool l_istable( int index=-1 )
      {
         return lua_istable( m_lua.get(), index );
      }

      void l_newtable()
      {
         return lua_newtable( m_lua.get() );
      }

      void* l_newuserdata( std::size_t size )
      {
         return lua_newuserdata( m_lua.get(), size);
      }

      bool l_next( int table_index )
      {
         return lua_next( m_lua.get(), table_index );
      }

      void l_pop( int num2pop=1)
      {
         lua_pop( m_lua.get(), num2pop );
      }

      void l_pushcclosure( lua_CFunction func, int num_ups )
      {
         lua_pushcclosure( m_lua.get(), func, num_ups );
      }

      void l_pushcfunction( lua_CFunction func )
      {
         lua_pushcfunction( m_lua.get(), func );
      }

      void l_pushlightuserdata( void* data )
      {
         lua_pushlightuserdata( m_lua.get(), data );
      }

      void l_pushnil( void )
      {
         lua_pushnil( m_lua.get() );
      }

      void l_pushnumber( lua_Number number )
      {
         lua_pushnumber( m_lua.get(), number );
      }

      void l_pushstring( const std::string& str )
      {
         lua_pushstring( m_lua.get(), str.c_str() );
      }

      void l_pushvalue( int index=-1 )
      {
         lua_pushvalue( m_lua.get(), index );
      }

      void l_rawget( int table_index )
      {
         lua_rawget( m_lua.get(), table_index );
      }

      void l_rawset( int table_index )
      {
         lua_rawset( m_lua.get(), table_index );
      }

      void l_register( const std::string& name, lua_CFunction func )
      {
         lua_register( m_lua.get(), name.c_str(), func);
      }

      void l_remove( int index )
      {
         lua_remove( m_lua.get(), index );
      }

      void l_setglobal( const std::string& str )
      {
         lua_setglobal( m_lua.get(), str.c_str() );
      }

      void l_setmetatable( int index=-2 )
      {
         lua_setmetatable( m_lua.get(), index );
      }

      void l_settable( int index=-1 )
      {
         lua_settable( m_lua.get(), index );
      }

      bool l_toboolean( int index=-1 )
      {
         return lua_toboolean( m_lua.get(), index );
      }

      lua_Integer l_tointeger( int index=-1 )
      {
         return lua_tointeger( m_lua.get(), index );
      }

      const std::string l_tostring( int index=-1 )
      {
         return lua_tostring( m_lua.get(), index );
      }

      lua_Number l_tonumber( int index=-1 )
      {
         return lua_tonumber( m_lua.get(), index);
      }

      void* l_touserdata( int index=-1 )
      {
         return lua_touserdata( m_lua.get(), index);
      }

      int l_type( int index=-1 )
      {
         return lua_type( m_lua.get(), index );
      }

      const std::string l_typename( int type )
      {
         return lua_typename( m_lua.get(), type );
      }

      int l_upvalueindex( int upval )
      {
         return lua_upvalueindex( upval );
      }

      lua_Number L_checknumber( int index=-1 )
      {
         return luaL_checknumber( m_lua.get(), index);
      }

      long L_checklong( int index=-1 )
      {
         return luaL_checklong( m_lua.get(), index);
      }

      int L_checkoption( int index, const std::string& def, const char* const enums[] )
      {
         return luaL_checkoption( m_lua.get(), index, def.c_str(), enums );
      }
      int L_checkoption( const std::string& def, const char* const enums[] )
      {
         return luaL_checkoption( m_lua.get(), -1, def.c_str(), enums );
      }
      int L_checkoption( int index, const char* const enums[] )
      {
         return luaL_checkoption( m_lua.get(), index, NULL, enums );
      }
      int L_checkoption( const char* const enums[] )
      {
         return luaL_checkoption( m_lua.get(), -1, NULL, enums );
      }

      const std::string L_checkstring( int index=-1 )
      {
         return luaL_checkstring( m_lua.get(), index );
      }

      void L_checktype( int param, int lua_type )
      {
         luaL_checktype( m_lua.get(), param, lua_type );
      }

      void* L_checkudata( int index, const std::string& type )
      {
         return luaL_checkudata( m_lua.get(), index, type.c_str() );
      }

      void L_error( const std::string& error )
      {
         luaL_error( m_lua.get(), error.c_str() );
      }

      bool L_newmetatable( const std::string& type )
      {
         return luaL_newmetatable( m_lua.get(), type.c_str() );
      }

      void L_openlibs()
      {
         luaL_openlibs( m_lua.get() );
      }

      lua_Number L_optnumber( int index =-1, lua_Number def = 0.0 )
      {
         return luaL_optnumber( m_lua.get(), index, def );
      }

      const std::string L_optstring( int index, const std::string& def )
      {
         return luaL_optlstring( m_lua.get(), index, def.c_str(), NULL );
      }

      int L_ref( int table_index =LUA_REGISTRYINDEX )
      {
         return luaL_ref( m_lua.get(), table_index );
      }

      void L_register( const std::string& lib_name, const luaL_Reg* reg_array )
      {
         luaL_register( m_lua.get(), lib_name.c_str(), reg_array);
      }
      void L_register( const luaL_Reg* reg_array )
      {
         luaL_register( m_lua.get(), NULL, reg_array);
      }

      void L_typerror( int param, const std::string& error )
      {
         luaL_typerror( m_lua.get(), param, error.c_str() );
      }

      const std::string L_typename( int index =-1 )
      {
         return luaL_typename( m_lua.get(), index );
      }

      void L_unref( int ref )
      {
         luaL_unref( m_lua.get(), LUA_REGISTRYINDEX, ref );
      }
      void L_unref( int table_index, int ref )
      {
         luaL_unref( m_lua.get(), table_index, ref );
      }

   private:
      boost::shared_ptr<lua_State> m_lua;
   };

} // namespace ento

#endif // ENTO_LUA_HPP_INCLUDED
