#include "sounddb.hpp"
#include "sound_lua.hpp"
#include "Lua.hpp"
#include <SFML/Audio/Music.hpp>

int main(int argc, char ** argv)
{
   using namespace ento;

   Lua lua;

   SoundDB db;

   sf::Music m;
   m.OpenFromFile( "data/Artic.ogg" );
   m.Play();
}
