#include "Lua.hpp"
#include <sstream>

#include <cassert>

namespace ento
{

   Lua::Lua()
   :m_lua( luaL_newstate(), lua_close )
   {
   }

   static void do_nothing( lua_State* state )
   {
   }

   Lua::Lua( lua_State* state )
   :m_lua( state, do_nothing )
   {
   }

   lua_Number Lua::getGlobalNumber( const std::string& num_name )
   {
      lua_getglobal( m_lua.get(), num_name.c_str() );
      lua_Number number;
      if( l_isnumber() )
      {
         number = l_tonumber();
         l_pop();
      }
      else
      {
         l_pop();
         throw Lua_Error( num_name + " is not a number" );
      }
      return number;
   }

   const std::string Lua::getGlobalString( const std::string& string_name )
   {
      l_getglobal( string_name );

      if( ! l_isstring() )
      {
         l_pop();
         throw Lua_Error( string_name + " is not a string" );
      }

      std::string ret = l_tostring();
      l_pop();
      return ret;
   }

   void Lua::doFile( const std::string& file_name )
   {
      int status = luaL_loadfile( m_lua.get(), file_name.c_str() );
      if( status == LUA_ERRSYNTAX )
      {
         std::string err = l_tostring();
         l_pop();
         throw Lua_Error( err );
      }

      assert( status == 0 );

      status = lua_pcall( m_lua.get(), 0, 0, 0 );

      if( status == LUA_ERRRUN )
      {
         std::string err = l_tostring();
         l_pop();
         throw Lua_Error( err );
      }

      assert( status == 0 );
   }

   void Lua::push( const b2Vec2& v )
   {
      assert(false);
      l_getglobal( "kinetica" );
      l_getfield( "vec" );
      l_remove( -2 );
      push( v.x );
      push( v.y );
      l_call( 2, 1 );
   }

   const b2Vec2 Lua::check_complex( int index )
   {
      assert( false );
      return b2Vec2_zero;

      if( ! l_istable(index) )
         L_typerror( index, "kinetica.vec" );

      if( index < 0 )
         index += this->l_gettop() + 1;

      l_getfield(index,"x");
      double x = L_optnumber();
      l_getfield(index,"y");
      double y = L_optnumber();
      l_pop(2);
      return b2Vec2(x,y);
   }


   void Lua::kwargerror( const std::string& kwarg, const std::string& extramsg )
   {
      std::ostringstream oss;
      oss << "bad argument '" << kwarg << "'";
      lua_Debug ar;
      if( l_getstack( ar ) )
      {
         l_getinfo( "n", ar );
         oss << " to '";
         if( ar.name == NULL )
         {
            oss << '?';
         }
         else
         {
            oss << ar.name;
         }
         oss << "'";
      }
      oss << " (" << extramsg << ")";
      L_error( oss.str().c_str() );
   }

   static void do_error( Lua& lua, const std::string& key, int exp_type, const std::string& act_type )
   {
      std::ostringstream oss;
      oss << "expected " << lua.l_typename(exp_type) << ", got " << act_type;
      lua.kwargerror( key, oss.str() );
   }

   static const std::string kcheckstring_impl( Lua& lua, const std::string& key )
   {
      if( lua.l_isstring() )
      {
         const std::string str = lua.l_tostring();
         lua.l_pop();
         return str;
      }

      do_error( lua, key, LUA_TSTRING, lua.L_typename() );
      return "";
   }

   const std::string Lua::koptstring( int table_index, const std::string& key, const std::string& def )
   {
      push(key);
      l_rawget( table_index );

      if( l_isnoneornil() )
      {
         return def;
      }

      return kcheckstring_impl( *this, key );
   }

   const std::string Lua::kcheckstring( int table_index, const std::string& key )
   {
      push(key);
      l_rawget( table_index );

      return kcheckstring_impl( *this, key );
   }

   static lua_Integer kcheckinteger_impl( Lua& lua, const std::string& key )
   {
      if( lua.l_isnumber() )
      {
         lua_Integer i = lua.l_tointeger();
         lua.l_pop();
         return i;
      }

      do_error( lua, key, LUA_TNUMBER, lua.L_typename() );
      return 0;
   }

   lua_Integer Lua::kcheckinteger( int table_index, const std::string& key )
   {
      push(key);
      l_rawget( table_index );
      return kcheckinteger_impl( *this, key );
   }

   lua_Integer Lua::koptinteger( int table_index, const std::string& key, lua_Integer def )
   {
      push(key);
      l_rawget( table_index );

      if( l_isnoneornil() )
      {
         return def;
      }

      return kcheckinteger_impl( *this, key );
   }

   static lua_Integer kcheckboolean_impl( Lua& lua, const std::string& key )
   {
      if( lua.l_isboolean() )
      {
         bool b = lua.l_toboolean();
         lua.l_pop();
         return b;
      }

      do_error( lua, key, LUA_TBOOLEAN, lua.L_typename() );
      return false;
   }

   bool Lua::kcheckboolean( int table_index, const std::string& key )
   {
      push(key);
      l_rawget( table_index );
      return kcheckboolean_impl( *this, key );
   }

   bool Lua::koptboolean( int table_index, const std::string& key, bool def )
   {
      push(key);
      l_rawget( table_index );

      if( l_isnoneornil() )
      {
         return def;
      }

      return kcheckboolean_impl( *this, key );
   }

}
