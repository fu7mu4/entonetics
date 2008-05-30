#include "Animation.hpp"

#include <functional>
#include <numeric>

namespace ento
{

Animation::Animation( void )
 : m_current_frame(0), m_time(0.f),
 	m_total_time(0.f), m_life_time(123456789.f)
{}

void Animation::
addSequence( std::size_t idx, float time )
{
	Anim_seq s = {idx, time};
	m_sequence.push_back(s);
}

bool Animation::
update( float delta )
{
	m_total_time += delta;
	if( m_total_time >= m_life_time )
		{ return false; }

	m_time += delta;
	while( m_time > m_sequence[m_current_frame].frame_time )
	{
		m_time -= m_sequence[m_current_frame].frame_time;
		++m_current_frame;
		if( m_current_frame >= m_sequence.size() )
			{ m_current_frame = 0; }
	}

	return true;
}

const sf::Sprite& Animation::
currentSprite( void ) const
{
	return m_sprites.at( m_sequence[m_current_frame].idx );
}

float Animation::
fullTime( void ) const
{
	struct Local
	{
		static float func( float acc, const Anim_seq& seq )
		{ return acc + seq.frame_time; }
	};

	return std::accumulate( m_sequence.begin(), m_sequence.end(),
		0.f, Local::func );
}

}
