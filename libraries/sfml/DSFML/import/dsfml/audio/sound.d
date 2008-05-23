/*
*   
*   
*   This file is part of DSFML
*
*   This software is provided 'as-is', without any express or
*   implied warranty. In no event will the authors be held
*   liable for any damages arising from the use of this software.
*
*   Permission is granted to anyone to use this software for any purpose,
*   including commercial applications, and to alter it and redistribute
*   it freely, subject to the following restrictions:
*
*   1.  The origin of this software must not be misrepresented;
*       you must not claim that you wrote the original software.
*       If you use this software in a product, an acknowledgment
*       in the product documentation would be appreciated but
*       is not required.
*
*   2.  Altered source versions must be plainly marked as such,
*       and must not be misrepresented as being the original software.
*
*   3.  This notice may not be removed or altered from any
*       source distribution.
*/

module dsfml.audio.sound;

import dsfml.audio.external;
import dsfml.audio.soundbuffer;
import dsfml.audio.soundstatus;

import dsfml.system.pointerchecker;
import dsfml.system.vector3;

/**
*   Sound defines the properties of the sound such as position,
*   volume, pitch, etc.
*/
class Sound
{
    /**
    *   Default constructor
    */
    this()
	{
		m_Sound = sfSound_Create();
	}

    /**
    *   Construct the sound from its parameters
    *
    *   Params:    
    *       buffer = Sound buffer to play
    *       loop = Loop flag (false by default)
    *       pitch = Value of the pitch (1 by default)
    *       volume = Volume (100 by default)
    *       x = X position (0 by default)
    *       y = Y position (0 by default)
    *       z = Z position (0 by default)
    */
    this(SoundBuffer buffer, bool loop = false, float pitch = 1.f, float volume = 100.f, float x = 0.f, float y = 0.f, float z = 0.f)
	{
		m_Buffer = buffer;
		m_Sound = sfSound_Create();
		sfSound_SetBuffer(m_Sound, buffer.toCSoundBuffer());
		sfSound_SetLoop(m_Sound, loop);
		sfSound_SetPitch(m_Sound, pitch);
		sfSound_SetVolume(m_Sound, volume);
		sfSound_SetPosition(m_Sound, x, y, z);
	}


    /**
    *   Destructor
    */
    ~this()
	{
		sfSound_Destroy(m_Sound);
	}

    /**
    *   Play the sound
    */
    void play()
	{
		sfSound_Play(m_Sound);
	}

    /**
    *   Pause the sound
    */
    void pause()
	{
		sfSound_Pause(m_Sound);
	}

    /**
    *   Stop the sound
    */
    void stop()
	{
		sfSound_Stop(m_Sound);
	}

    /**
    *   Set the source buffer
    *
    *   Params: 
    *       buffer = New sound buffer to bind to the sound
    */
    void setBuffer(SoundBuffer buffer)
	{
		m_Buffer = buffer;
		sfSound_SetBuffer(m_Sound, buffer.toCSoundBuffer());
	}

    /**
    *   Set the sound loop state.
    *   This parameter is disabled by default
    *
    *   Params: 
    *       loop = True to play in loop, false to play once
    */
    void setLoop(bool loop)
	{
		sfSound_SetLoop(m_Sound, loop);
	}

    /**
    *   Set the sound pitch.
    *   The default pitch is 1
    *
    *   Params: 
    *       pitch = New pitch
    */
    void setPitch(float pitch)
	{
		sfSound_SetPitch(m_Sound, pitch);
	}

    /**
    *   Set the sound volume.
    *   The default volume is 100
    *
    *   Params: 
    *       volume = Volume (in range [0, 100])
    */
    void setVolume(float volume)
    in
    {
        assert(volume >= 0 && volume <= 100);
    }
    body
	{
		sfSound_SetVolume(m_Sound, volume);
	}

    /**
    *   Set the sound position.
    *   The default position is (0, 0, 0)
    *
    *   Params: 
    *       x = X position of the sound in the world
    *       y = Y position of the sound in the world
    *       z = Z position of the sound in the world
    */
    void setPosition(float x, float y, float z)
	{
		sfSound_SetPosition(m_Sound, x, y, z);
	}

    /**
    *   Set the sound position.
    *   The default position is (0, 0, 0)
    *   
    *   Params :
    *       position = new position                
    */        
    void setPosition(Vector3f position)
    {
        sfSound_SetPosition(m_Sound, position.x, position.y, position.z);
    }

    /**
    *   Set the minimum distance - closer than this distance
    *   the listener will hear the sound at its maximum volume.
    *   The default distance is 1.0
    *   
    *   Params:    
    *       minDistance = new minimum distance for the sound 
    */        
    void setMinDistance(float minDistance)
    {
        sfSound_SetMinDistance(m_Sound, minDistance);
    }

    /**
    *   Set the attenuation factor - the higher the attenuation, the
    *   more the sound will be attenuated with distance from listener.
    *   The default attenuation factor 1.0
    *   
    *   Params:
    *       attenuation = new attenuation factor for the sound            
    */        
    void setAttenuation(float attenuation)
    {
        sfSound_SetAttenuation(m_Sound, attenuation);
    }

    /**
    *   Get the source buffer
    *
    *   Returns: 
    *       Sound buffer bound to the sound (can be NULL)
    */
    SoundBuffer getBuffer() 
	{
		return m_Buffer;
	}

    /**
    *   Tell whether or not the sound is looping
    *
    *   Returns: 
    *       True if the sound is looping, false otherwise
    */
    bool getLoop() 
	{

		return cast(bool)(sfSound_GetLoop(m_Sound));
	}

    /**
    *   Get the pitch
    *
    *   Returns: 
    *       Pitch value
    */
    float getPitch() 
	{
		return sfSound_GetPitch(m_Sound);
	}

    /**
    *   Get the volume
    *
    *   Returns: 
    *       Volume value (in range [1, 100])
    */
    float getVolume() 
	{
		return sfSound_GetVolume(m_Sound);
	}

    /**
    *   Get the sound position
    *
    *   Params:    
    *       x = X position of the sound in the world
    *       y = Y position of the sound in the world
    *       z = Z position of the sound in the world
    */
    Vector3f getPosition() 
	{
        Vector3f ret;
		sfSound_GetPosition(m_Sound, &ret.x, &ret.y, &ret.z);
		return ret;
	}

    /**
    *   Get the minimum distance
    *
    *   Returns:
    *      Minimum distance for the sound
    */
    float getMinDistance()
    {
        return sfSound_GetMinDistance(m_Sound);
    }

    /**
    *   Get the attenuation factor
    *
    *   Returns:
    *       Attenuation factor of the sound
    *
    */
    float getAttenuation() 
    {
        return sfSound_GetAttenuation(m_Sound);
    }


    /**
    *   Get the status of the sound (stopped, paused, playing)
    *
    *   Returns: 
    *       Current status of the sound
    */
    SoundStatus getStatus() 
	{
		return sfSound_GetStatus(m_Sound);
	}

    /**
    *   Get the current playing position of the sound
    *
    *   Returns:  
    *       Current playing position, expressed in seconds
    */
    float getPlayingOffset() 
	{
		return sfSound_GetPlayingOffset(m_Sound);
	}


private:
	sfSound* m_Sound;
	SoundBuffer m_Buffer; //Prevent GC cleaning
	
	mixin TEnforcePointer!(m_Sound);
}
