#include "sound_lua.hpp"

namespace ento
{

   namespace
   {
      static int Sounds_lua_prt2( lua_State* state );
      
      static int Sounds_lua_prt1( lua_State* state )
      {
         ento::Lua lua(state);
      
         std::string prefix = lua.L_optstring( 1, "" );
         lua.l_pushvalue( lua.l_upvalueindex(1) );
         lua.push(prefix);
         lua.l_pushcclosure( Sounds_lua_prt2, 2 );
         return 1;
      }
      
      static int Sounds_lua_prt2( lua_State* state )
      {
         ento::Lua lua(state);
         SoundDB* s_db = lua.touserdata<SoundDB>( lua.l_upvalueindex(1) );
         if( s_db == NULL )
         {
            lua.L_error( "internal error: SoundDB is NULL" );
            return 0;
         }
      
         std::string prefix = lua.l_tostring( lua.l_upvalueindex(2) );
      
         lua.L_checktype( 1, LUA_TTABLE );
      
         lua.push();
         while( lua.l_next(1) )
         {
            if( ! (lua.l_isstring() && lua.l_isstring(-2) ) )
            {
               lua.L_error( "invalid sound entry" );
            }
      
            const std::string file = lua.l_tostring();
            lua.l_pop();
            const std::string name = lua.l_tostring();
            try
            {
               s_db->addSound( name, prefix+file );
            }
            catch( SoundError& e )
            {
               lua.L_error( e.what() );
            }
         }
         return 0;
      }
      
   } // anonymous namespace

void load_sounds( SoundDB& s_db, ento::Lua& lua, const std::string& sound_file )
{
   lua.push( &s_db );
   lua.l_pushcclosure( &Sounds_lua_prt1, 1 );
   lua.l_setglobal( "Sounds" );

   lua.doFile( sound_file );
}

} // namespace ento
