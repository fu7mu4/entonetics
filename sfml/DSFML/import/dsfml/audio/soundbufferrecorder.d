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

module dsfml.audio.soundbufferrecorder;

import dsfml.audio.soundbuffer;
import dsfml.audio.external;
import dsfml.audio.soundrecorder;

/**
*   Specialized sfSoundRecorder which saves the captured
*   audio data into a sound buffer
*/
class SoundBufferRecorder : SoundRecorder
{
    /**
    *   Constructor
    */
    this()
    {
        m_SoundRecorder = cast(sfSoundRecorder*) sfSoundBufferRecorder_Create();
        super();
    }

    /**
    *   Destructor
    */
    ~this()
    {
        sfSoundBufferRecorder_Destroy(cast(sfSoundBufferRecorder*) m_SoundRecorder);
        m_disposed = true;
    }

    /**
    *   Get the sound buffer containing the captured audio data
    *
    *   Returns: 
    *       SoundBuffer containing the captured audio data 
    *
    */
    SoundBuffer getBuffer()
    {
        return new SoundBuffer(sfSoundBufferRecorder_GetBuffer( cast(sfSoundBufferRecorder*) m_SoundRecorder));
    }
}

