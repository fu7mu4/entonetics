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

module dsfml.audio.soundbuffer;

import dsfml.audio.external;

import dsfml.system.stringutil;


/**
*   SoundBuffer is the low-level for loading and manipulating
*   sound buffers
*/
class SoundBuffer
{
    /**
    *   Default constructor
    *
    */
    this()
	{
		m_SoundBuffer = null;
		m_callDestructor = true;
	}

    /**
    *   Destructor
    *
    */
    ~this()
	{
		if (m_SoundBuffer !is null && m_callDestructor)
			sfSoundBuffer_Destroy(m_SoundBuffer);
	}

    /**
    *   Load the sound buffer from a file
    *
    *   Params: 
    *       filename = Path of the sound file to load
    *
    *   Returns: 
    *       True if loading has been successful
    */
    bool loadFromFile(char[] filename)
	{
		m_SoundBuffer = sfSoundBuffer_CreateFromFile(toStringz(filename));

		if (m_SoundBuffer is null)
			return false;

		return true;
	}

    /**
    *   Load the sound buffer from a file in memory
    *
    *   Params:     
    *       data = Pointer to the file data in memory
    *       sizeInBytes = Size of the data to load, in bytes
    *
    *   Returns: 
    *       True if loading has been successful
    */
    bool loadFromMemory(byte* data, size_t sizeInBytes)
	{
		m_SoundBuffer = sfSoundBuffer_CreateFromMemory(data, sizeInBytes);

		if (m_SoundBuffer is null)
			return false;

		return true;
	}

    /**
    *   Load the sound buffer from an array of samples - assumed format for
    *   samples is 16 bits signed integer
    *
    *   Params:     
    *       samples = Pointer to the samples in memory
    *       samplesCount = Number of samples pointed by Samples
    *       channelsCount = Number of channels (1 = mono, 2 = stereo, ...)
    *       sampleRate = Frequency (number of samples to play per second)
    *
    *   Returns: 
    *       True if loading has been successful
    */
    bool loadFromSamples(short* samples, size_t samplesCount, uint channelsCount, uint sampleRate)
	{
		m_SoundBuffer = sfSoundBuffer_CreateFromSamples(samples, samplesCount, channelsCount, sampleRate);

		return m_SoundBuffer is null ? false : true;
	}

    /**
    *   Save the sound buffer to a file
    *
    *   Params: 
    *       filename = Path of the sound file to write
    *
    *   Returns: 
    *       True if saving has been successful
    */
    bool saveToFile(char[] filename) 
    {
		if (m_SoundBuffer !is null && filename !is null && filename.length > 0 )
		{
			return sfSoundBuffer_SaveToFile(m_SoundBuffer, toStringz(filename));
		}
		return false;
	}

    /**
    *   Return the sound samples
    *
    *   Returns: 
    *       Pointer to the array of sound samples, in 16 bits signed integer format
    */
    short* getSamples() 
	{
		if (m_SoundBuffer !is null)
			return sfSoundBuffer_GetSamples(m_SoundBuffer);

		return null;
	}

    /**
    *   Return the samples count
    *
    *   Returns: 
    *       Number of samples
    *
    */
    size_t getSamplesCount() 
	{
		if (m_SoundBuffer !is null)
			return sfSoundBuffer_GetSamplesCount(m_SoundBuffer);

		return 0;
	}

    /**
    *   Get the sample rate
    *
    *   Returns: 
    *       Sound frequency (number of samples per second)
    */
    uint getSampleRate() 
	{
		if (m_SoundBuffer !is null)
			return sfSoundBuffer_GetSampleRate(m_SoundBuffer);

		return 0;
	}

    /**
    *   Return the number of channels (1 = mono, 2 = stereo, ...)
    *
    *   Returns:
    *       Number of channels
    */
    uint getChannelsCount() 
	{
		if (m_SoundBuffer !is null)
			return sfSoundBuffer_GetChannelsCount(m_SoundBuffer);

		return 0;
	}

    /**
    *   Get the sound duration
    *
    *   Returns: 
    *       Sound duration, in seconds
    */
    float getDuration() 
	{
		if (m_SoundBuffer !is null)
			return sfSoundBuffer_GetDuration(m_SoundBuffer);

		return 0;
	}

package:
    sfSoundBuffer* toCSoundBuffer()
    {
        assert(m_SoundBuffer !is null, "Attempt to access an invalid SoundBuffer");
        return m_SoundBuffer;
    }
    
    this(sfSoundBuffer* ptr)
    {
        m_SoundBuffer = ptr;
        m_callDestructor = false;
    }

private:
	sfSoundBuffer* m_SoundBuffer;
	bool m_callDestructor; // To prevent multiple call to delete when buffer come from a recorder
}

