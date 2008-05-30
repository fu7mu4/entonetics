#include <sounddb.hpp>
#include <cassert>
#include <sstream>

namespace ento
{

SoundDB::SoundDB( void )
 : m_anon_count(0)
{ }


bool SoundDB::isSound( const std::string& name )
{
   std::map<std::string,SoundEntry>::iterator found;
   found = m_sounds.find(name);
   return found != m_sounds.end();
}

SoundDB::Ref SoundDB::addSound( const std::string& name, const std::string& file )
{

   SoundEntry se;
   se.file_name = file;
   se.references = 0;
   se.sb = NULL;

   std::pair< std::map<std::string,SoundEntry>::iterator, bool > inserted;
   inserted = m_sounds.insert( std::make_pair(name, se ) );

   if( ! inserted.second )
   {
      std::ostringstream oss;
      oss << "sound '" << name << "' already exists";
      throw SoundError( oss.str() );
   }

   return &((inserted.first)->second);
}

SoundDB::Ref SoundDB::getSoundRef( const std::string& name )
{
   std::map<std::string,SoundEntry>::iterator found;
   found = m_sounds.find(name);
   if( found == m_sounds.end() )
   {
      std::ostringstream oss;
      oss << "'" << name << "' not found";
      throw SoundError( oss.str() );
   }
   return &found->second;
}

Sound SoundDB::getSound( const std::string& name )
{
   return getSound( getSoundRef( name ) );
}

Sound SoundDB::getSound( SoundDB::Ref ref )
{
   SoundEntry& se = *static_cast<SoundEntry*>(ref);
   init_entry( se );
   std::list<SoundInstance>::iterator inst;
   inst = m_active.insert(m_active.begin(), SoundInstance( se ) );
   return Sound( *this, inst );
}

Sound SoundDB::newSound( const std::string& file )
{
   std::ostringstream oss;
   oss << this << m_anon_count++;
   return newSound( oss.str(), file );
}

Sound SoundDB::newSound( const std::string& name, const std::string& file )
{
   return getSound( addSound( name, file ) );
}

void SoundDB::init_entry( SoundEntry& se )
{
   ++se.references;
   if( se.sb != NULL ) return;

   se.sb = new sf::SoundBuffer();
   if( ! se.sb->LoadFromFile(se.file_name) )
   {
      std::ostringstream oss;
      oss << "unable to load sound from file '" << se.file_name << "'";
      throw SoundError( oss.str() );
   }
}

void SoundDB::collect( void )
{
   m_playing.remove_if( SoundDB::soundDone );
}

bool SoundDB::soundDone( SoundInstance& si )
{
   return si.sound.GetStatus() != sf::Sound::Playing;
}

void SoundDB::incr_inst( std::list<SoundInstance>::iterator& inst )
{
   ++(inst->references);
}

void SoundDB::decr_inst( std::list<SoundInstance>::iterator& inst )
{
   --(inst->references);
   if( inst->references == 0 )
   {
      if( inst->sound.GetStatus() == sf::Sound::Playing )
      {
         // move the SoundInstance to the playing list
         m_playing.splice( m_playing.begin(), m_active, inst );
      }
      else
      {
         // delete the SoundInstance
         --(inst->se->references);
         m_active.erase( inst );
      }
   }
}

//
// ---------------------------- Sound::SoundInstance ---------------------------
//
SoundDB::SoundInstance::SoundInstance( SoundDB::SoundEntry& se_ )
:sound(*se_.sb),references(0),se(&se_)
{
}


//
// ----------------------------------- Sound -----------------------------------
//

Sound::Sound( SoundDB& db, std::list<SoundDB::SoundInstance>::iterator inst):m_db(db), m_inst(inst)
{
   m_db.incr_inst(m_inst);
}

Sound::Sound( const Sound& other ):m_db(other.m_db), m_inst(other.m_inst)
{
   m_db.incr_inst(m_inst);
}

Sound& Sound::operator = ( const Sound& rhs )
{
   assert( &m_db == &rhs.m_db );
   m_db.decr_inst(m_inst);
   m_inst = rhs.m_inst;
   m_db.incr_inst(m_inst);
   return *this;
}

Sound::~Sound( void )
{
   m_db.decr_inst(m_inst);
}

void Sound::play( void )
{
   m_inst->sound.Play();
}

Sound::Status Sound::getStatus( void )
{
   switch( m_inst->sound.GetStatus() )
   {
   case sf::Sound::Playing: return e_Playing;
   case sf::Sound::Paused:  return e_Playing;
   default: return e_Playing;
   }
}

} // namespace ento
