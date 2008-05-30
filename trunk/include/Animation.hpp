#ifndef ANIMATION_HPP_INCLUDED
#define ANIMATION_HPP_INCLUDED

#include <SFML/Graphics/Sprite.hpp>
#include <Box2D.h>
#include <vector>

namespace ento
{
	class Animation
	{
	public:
		
		Animation( void );

		const b2Vec2& getPosition( void ) const
		{ return m_pos; }
		void setPosition( const b2Vec2& pos)
		{ m_pos = pos; }

		void addSprite( const sf::Sprite& sprite )
		{ m_sprites.push_back( sprite ); }

		void addSequence( std::size_t idx, float time );

		bool update( float delta );

		const sf::Sprite& currentSprite( void ) const;

		float getLifeTime( void ) const
		{ return m_life_time; }

		void setLifeTime( float time )
		{ m_life_time = time; }

		float fullTime( void ) const;

	private:
		struct Anim_seq
		{
			std::size_t idx;
			float frame_time;
		};
		std::vector<Anim_seq> m_sequence;

		std::vector<sf::Sprite> m_sprites;

		b2Vec2 m_pos;
		std::size_t m_current_frame;
		float m_time;
		float m_total_time;
		float m_life_time;
	};
}

#endif // ANIMATION_HPP_INCLUDED
