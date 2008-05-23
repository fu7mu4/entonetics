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

module dsfml.audio.music;

import dsfml.audio.external;
import dsfml.audio.soundstatus;

import dsfml.system.stringutil;
import dsfml.system.vector3;

/**
* Music defines a big sound played using streaming,
* so usually what we call a music :)
*/
class Music
{
    /**
    * Construct the music
    */
    this()
    {
        m_Music = null;
    }

    /**
    *   Destructor
    */ 
    ~this()
    {
        if (m_Music !is null)
            sfMusic_Destroy(m_Music);
    }

    /**
    *   Open a music file (doesn't play it -- call Play for that)
    *   
    *   Params:
    *       filename = Path of the file to open
    *       
    *   Returns:
    *       True if loading has been successful                                                
    */ 
    bool open(char[] filename)
    {
        if(filename !is null && filename.length > 0)
        {
            m_Music = sfMusic_CreateFromFile(toStringz(filename));
            if (m_Music !is null)
                return true;
        }
        return false;
    }

    /**
    *   Open a music file from memory (doesn't play it -- call Play() for that)
    *
    *   Params:
    *       data = Pointer to the file data in memory
    *       sizeInBytes = Size of the data to load, in bytes
    *
    *   Returns:
    *       True if loading has been successful
    */
    bool openFromMemory(byte* data, size_t sizeInBytes)
    {
        if (!data)
            return false;
        m_Music = sfMusic_CreateFromMemory(data, sizeInBytes);
        if (m_Music is null)
            return false;
        return true;
    }


    /**
    *   Start playing the audio stream
    */
    void play()
    {
        if (m_Music !is null)
            sfMusic_Play(m_Music);
    }

    /**
    *   Stop playing the audio stream
    */
    void stop()
    {
        if (m_Music !is null)
            sfMusic_Stop(m_Music);
    }

    /**
    *   Pause the audio stream
    */
    void pause()
    {
        if (m_Music !is null)
            sfMusic_Pause(m_Music);
    }


    /**
    *   Return the number of channels (1 = mono, 2 = stereo)
    *
    *   Returns: 
    *       Number of channels
    */
    uint getChannelsCount()
    {
        if (m_Music is null)
            return 0;
        
        return sfMusic_GetChannelsCount(m_Music);
    }

    /**
    *   Get the stream sample rate
    *
    *   Returns:
    *       Stream frequency (number of samples per second)
    */
    uint getSampleRate() 
    {
        if (m_Music is null)
            return 0;
        
        return sfMusic_GetSampleRate(m_Music);
    }


    /**
    *   Get the music duration
    *
    *   Returns: 
    *       Music duration, in seconds
    */
    float getDuration() 
    {
        if (m_Music is null)
            return 0;

        return sfMusic_GetDuration(m_Music);
    }

    /**
    *   Get the status of the stream (stopped, paused, playing)
    *
    *   Returns: 
    *       Current status of the sound
    */
    SoundStatus getStatus() 
    {
        if (m_Music is null)
            return SoundStatus.Stopped;

        return sfMusic_GetStatus(m_Music);
    }


    /**
    *   Tell whether or not the music is looping
    *
    *   Returns: 
    *       True if the music is looping, false otherwise
    */
    bool getLoop() 
    {
        if (m_Music is null)
            return false;

        return sfMusic_GetLoop(m_Music);
    }

    /**
    *   Get the pitch
    *
    *   Returns: 
    *       Pitch value
    */
    float getPitch() 
    {
        if (m_Music is null)
            return 0.0;

        return sfMusic_GetPitch(m_Music);
    }

    /**
    *   Get the volume
    *
    *   Returns: 
    *       Volume value (in range [1, 100])
    */
    float getVolume() 
    {
        if (m_Music is null)
            return 0.0;

        return sfMusic_GetVolume(m_Music);
    }

    /**
    *   Get the sound position
    *
    *   Returns:
    *       Current position of the music.        
    */
    Vector3f getPosition() 
    {
        Vector3f ret;
        if (m_Music !is null)
        {
            sfMusic_GetPosition(m_Music, &ret.x, &ret.y, &ret.z);
        }
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
        return sfMusic_GetMinDistance(m_Music);
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
        return sfMusic_GetAttenuation(m_Music);
    }


    /**
    *   Set the music loop state.
    *   This parameter is disabled by default
    *
    *   Params: 
    *       loop = True to play in loop, false to play once
    */
    void setLoop(bool loop)
    {
        if (m_Music !is null)
            sfMusic_SetLoop(m_Music, loop);
    }

    /**
    *   Set the sound pitch.
    *   The default pitch is 1
    *
    *   Params: 
    *       pitch = New pitch
    *
    */
    void setPitch(float pitch)
    {
        if (m_Music !is null)
        {
            sfMusic_SetPitch(m_Music, pitch);
        }
    }

    /**
    *   Set the sound volume.
    *   The default volume is 100
    *
    *   Params: 
    *       volume = Volume (in range [0, 100])
    *
    */
    void setVolume(float volume)
    in
    {
        assert (volume >= 0.f && volume <= 100.f);
    }
    body
    {
        if (m_Music !is null)
        {
            sfMusic_SetVolume(m_Music, volume);
        }
    }

    /**
    *   Set the sound position.
    *   The default position is (0, 0, 0)
    *
    *   Params: 
    *       x = X position of the sound in the world
    *       y = Y position of the sound in the world
    *       z = Z position of the sound in the world
    *
    */
    void setPosition(float x, float y, float z)
    {
        if (m_Music !is null)
        {
            sfMusic_SetPosition(m_Music, x, y, z);
        }
    }

    /**
    *   Set the sound position.
    *   The default position is (0, 0, 0)
    *
    *   Params: 
    *       position = new position
    *
    */
    void setPosition(Vector3f position)
    {
        if (m_Music !is null)
        {
            sfMusic_SetPosition(m_Music, position.x, position.y, position.z);
        }
    }


    /**
    *   Set the minimum distance - closer than thsi distance
    *   the listener will hear the sound at its maximum volume.
    *   The default distance is 1.0
    *   
    *   Params:    
    *       minDistance = new minimum distance for the sound 
    */        
    void setMinDistance(float minDistance)
    {
        sfMusic_SetMinDistance(m_Music, minDistance);
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
        sfMusic_SetAttenuation(m_Music, attenuation);
    }

private:
    sfMusic* m_Music;
}

