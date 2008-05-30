#ifndef SOUND_LUA_HPP_INCLUDED
#define SOUND_LUA_HPP_INCLUDED

#include <string>
#include "Lua.hpp"
#include "sounddb.hpp"

namespace ento
{
   void load_sounds( SoundDB& s_db, Lua& lua, const std::string& sound_file );
}

#endif // SOUND_LUA_HPP_INCLUDED
