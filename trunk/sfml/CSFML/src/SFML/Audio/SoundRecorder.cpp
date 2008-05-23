////////////////////////////////////////////////////////////
//
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007 Laurent Gomila (laurent.gom@gmail.com)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Audio/SoundRecorder.h>
#include <SFML/Audio/SoundRecorder.hpp>
#include <SFML/Internal.h>


struct sfSoundRecorder
{
    typedef sfBool (*FuncType)(const sfInt16*, size_t, void*);

    sfSoundRecorder(FuncType Callback, void* UserData) :
    This      (&sfSoundRecorder::ProcessSamples, this),
    myCallback(Callback),
    myUserData(UserData)
    {

    }

    static bool ProcessSamples(const sf::Int16* Samples, std::size_t SamplesCount, void* UserData)
    {
        // We need to use an extra callback to do the conversion (bool -> sfBool)
        sfSoundRecorder* Obj = static_cast<sfSoundRecorder*>(UserData);

        return Obj->myCallback(Samples, SamplesCount, Obj->myUserData) == sfTrue;
    }

    sf::SoundRecorder This;
    FuncType          myCallback;
    void*             myUserData;
};


////////////////////////////////////////////////////////////
/// Construct a new sound recorder with a callback function
/// for processing captured samples
////////////////////////////////////////////////////////////
sfSoundRecorder* sfSoundRecorder_Create(sfBool (*Callback)(const sfInt16*, size_t, void*), void* UserData)
{
    return new sfSoundRecorder(Callback, UserData);
}


////////////////////////////////////////////////////////////
/// Destroy an existing sound recorder
////////////////////////////////////////////////////////////
void sfSoundRecorder_Destroy(sfSoundRecorder* SoundRecorder)
{
    delete SoundRecorder;
}


////////////////////////////////////////////////////////////
/// Start the capture.
/// Warning : only one capture can happen at the same time
////////////////////////////////////////////////////////////
void sfSoundRecorder_Start(sfSoundRecorder* SoundRecorder, unsigned int SampleRate)
{
    CSFML_CALL(SoundRecorder, Start(SampleRate));
}


////////////////////////////////////////////////////////////
/// Stop the capture
////////////////////////////////////////////////////////////
void sfSoundRecorder_Stop(sfSoundRecorder* SoundRecorder)
{
    CSFML_CALL(SoundRecorder, Stop());
}


////////////////////////////////////////////////////////////
/// Get the sample rate of a sound recorder
////////////////////////////////////////////////////////////
unsigned int sfSoundRecorder_GetSampleRate(sfSoundRecorder* SoundRecorder)
{
    CSFML_CALL_RETURN(SoundRecorder, GetSampleRate(), 0);
}


////////////////////////////////////////////////////////////
/// Tell if the system supports sound capture.
/// If not, this class won't be usable
////////////////////////////////////////////////////////////
sfBool sfSoundRecorder_CanCapture()
{
    return sf::SoundRecorder::CanCapture() ? sfTrue : sfFalse;
}
