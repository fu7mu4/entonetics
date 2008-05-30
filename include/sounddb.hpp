#ifndef SOUNDDB_HPP_INCLUDED
#define SOUNDDB_HPP_INCLUDED

#include <SFML/Audio.hpp>
#include <list>
#include <map>
#include <string>
#include <stdexcept>

namespace ento
{

   class SoundError: public std::runtime_error
   {
   public:
      SoundError(const std::string& str)
       : std::runtime_error(str)
      { }
   };

   class Sound;

   class SoundDB
   {
      friend class Sound;
   private:
      struct SoundEntry
      {
         std::string file_name;
         std::size_t references;
         sf::SoundBuffer* sb;
      };

      struct SoundInstance
      {
         SoundInstance( SoundEntry& se );
         sf::Sound sound;
         std::size_t references;
         SoundEntry* se;
      };

   public:
      SoundDB();

      typedef SoundEntry* Ref;

      bool isSound( const std::string& name );

      Ref addSound( const std::string& name, const std::string& file );
      Ref getSoundRef( const std::string& name );
      Sound getSound( const std::string& name );
      Sound getSound( Ref ref );

      Sound newSound( const std::string& file );
      Sound newSound( const std::string& name, const std::string& file );

      void collect( void );

   private:

      static bool soundDone( SoundInstance& si );
      void init_entry( SoundEntry& se );
      void incr_inst( std::list<SoundInstance>::iterator& inst );
      void decr_inst( std::list<SoundInstance>::iterator& inst );
      std::map<std::string,SoundEntry> m_sounds;
      std::list<SoundInstance> m_active;
      std::list<SoundInstance> m_playing;
      std::size_t m_anon_count;
   };

   class Sound
   {
      friend class SoundDB;
   public:
      Sound( const Sound& other );
      Sound& operator = ( const Sound& rhs );
      ~Sound( void );

      enum Status
      {
         e_Playing,
         e_Paused,
         e_Stopped
      };

      void play( void );
      Status getStatus( void );

   private:
      Sound( SoundDB& db, std::list<SoundDB::SoundInstance>::iterator inst);
      SoundDB& m_db;
      std::list<SoundDB::SoundInstance>::iterator m_inst;
   };

}

#endif // SOUNDDB_HPP_INCLUDED
