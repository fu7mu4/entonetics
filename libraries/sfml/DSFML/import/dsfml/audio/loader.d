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


module dsfml.audio.loader;

import dsfml.audio.external;

import dsfml.system.dllloader;

version (Windows)
{
    const char[] LIBNAME = "csfml-audio.dll";
}
version (linux)
{
    const char[] LIBNAME = "libcsfml-audio.so.1";
}

DLLloader s_lib;

void init()
{
    s_lib = DLLloader.load(LIBNAME);

    // music.d
    sfMusic_CreateFromFile = cast(pf_sfMusic_CreateFromFile)s_lib.getSymbol("sfMusic_CreateFromFile");
    sfMusic_CreateFromMemory = cast(pf_sfMusic_CreateFromMemory)s_lib.getSymbol("sfMusic_CreateFromMemory");
    sfMusic_Destroy = cast(pf_sfMusic_Destroy)s_lib.getSymbol("sfMusic_Destroy");
    sfMusic_SetLoop = cast(pf_sfMusic_SetLoop)s_lib.getSymbol("sfMusic_SetLoop");
    sfMusic_GetLoop = cast(pf_sfMusic_GetLoop)s_lib.getSymbol("sfMusic_GetLoop");
    sfMusic_GetDuration = cast(pf_sfMusic_GetDuration)s_lib.getSymbol("sfMusic_GetDuration");
    sfMusic_Play = cast(pf_sfMusic_Play)s_lib.getSymbol("sfMusic_Play");
    sfMusic_Pause = cast(pf_sfMusic_Pause)s_lib.getSymbol("sfMusic_Pause");
    sfMusic_Stop = cast(pf_sfMusic_Stop)s_lib.getSymbol("sfMusic_Stop");
    sfMusic_GetChannelsCount = cast(pf_sfMusic_GetChannelsCount)s_lib.getSymbol("sfMusic_GetChannelsCount");
    sfMusic_GetSampleRate = cast(pf_sfMusic_GetSampleRate)s_lib.getSymbol("sfMusic_GetSampleRate");
    sfMusic_GetStatus = cast(pf_sfMusic_GetStatus)s_lib.getSymbol("sfMusic_GetStatus");
    sfMusic_SetPitch = cast(pf_sfMusic_SetPitch)s_lib.getSymbol("sfMusic_SetPitch");
    sfMusic_SetVolume = cast(pf_sfMusic_SetVolume)s_lib.getSymbol("sfMusic_SetVolume");
    sfMusic_SetPosition = cast(pf_sfMusic_SetPosition)s_lib.getSymbol("sfMusic_SetPosition");
    sfMusic_GetPitch = cast(pf_sfMusic_GetPitch)s_lib.getSymbol("sfMusic_GetPitch");
    sfMusic_GetVolume = cast(pf_sfMusic_GetVolume)s_lib.getSymbol("sfMusic_GetVolume");
    sfMusic_GetPosition = cast(pf_sfMusic_GetPosition)s_lib.getSymbol("sfMusic_GetPosition");
    sfMusic_GetMinDistance = cast(pf_sfMusic_GetMinDistance)s_lib.getSymbol("sfMusic_GetMinDistance");
    sfMusic_GetAttenuation = cast(pf_sfMusic_GetAttenuation)s_lib.getSymbol("sfMusic_GetAttenuation");
    sfMusic_SetMinDistance = cast(pf_sfMusic_SetMinDistance)s_lib.getSymbol("sfMusic_SetMinDistance");
    sfMusic_SetAttenuation = cast(pf_sfMusic_SetAttenuation)s_lib.getSymbol("sfMusic_SetAttenuation");

	// soundbuffer.d
    sfSoundBuffer_CreateFromFile = cast(pf_sfSoundBuffer_CreateFromFile)s_lib.getSymbol("sfSoundBuffer_CreateFromFile");
    sfSoundBuffer_CreateFromMemory = cast(pf_sfSoundBuffer_CreateFromMemory)s_lib.getSymbol("sfSoundBuffer_CreateFromMemory");
    sfSoundBuffer_CreateFromSamples = cast(pf_sfSoundBuffer_CreateFromSamples)s_lib.getSymbol("sfSoundBuffer_CreateFromSamples");
    sfSoundBuffer_Destroy = cast(pf_sfSoundBuffer_Destroy)s_lib.getSymbol("sfSoundBuffer_Destroy");
    sfSoundBuffer_SaveToFile = cast(pf_sfSoundBuffer_SaveToFile)s_lib.getSymbol("sfSoundBuffer_SaveToFile");
    sfSoundBuffer_GetSamples = cast(pf_sfSoundBuffer_GetSamples)s_lib.getSymbol("sfSoundBuffer_GetSamples");
    sfSoundBuffer_GetSamplesCount = cast(pf_sfSoundBuffer_GetSamplesCount)s_lib.getSymbol("sfSoundBuffer_GetSamplesCount");
    sfSoundBuffer_GetSampleRate = cast(pf_sfSoundBuffer_GetSampleRate)s_lib.getSymbol("sfSoundBuffer_GetSampleRate");
    sfSoundBuffer_GetChannelsCount = cast(pf_sfSoundBuffer_GetChannelsCount)s_lib.getSymbol("sfSoundBuffer_GetChannelsCount");
    sfSoundBuffer_GetDuration = cast(pf_sfSoundBuffer_GetDuration)s_lib.getSymbol("sfSoundBuffer_GetDuration");

	// soundbufferrecorder.d
    sfSoundBufferRecorder_Create = cast(pf_sfSoundBufferRecorder_Create)s_lib.getSymbol("sfSoundBufferRecorder_Create");
    sfSoundBufferRecorder_Destroy = cast(pf_sfSoundBufferRecorder_Destroy)s_lib.getSymbol("sfSoundBufferRecorder_Destroy");
    sfSoundBufferRecorder_Start = cast(pf_sfSoundBufferRecorder_Start)s_lib.getSymbol("sfSoundBufferRecorder_Start");
    sfSoundBufferRecorder_Stop = cast(pf_sfSoundBufferRecorder_Stop)s_lib.getSymbol("sfSoundBufferRecorder_Stop");
    sfSoundBufferRecorder_GetSampleRate = cast(pf_sfSoundBufferRecorder_GetSampleRate)s_lib.getSymbol("sfSoundBufferRecorder_GetSampleRate");
    sfSoundBufferRecorder_GetBuffer = cast(pf_sfSoundBufferRecorder_GetBuffer)s_lib.getSymbol("sfSoundBufferRecorder_GetBuffer");
    
	// soundrecorder.d
    sfSoundRecorder_Create = cast(pf_sfSoundRecorder_Create)s_lib.getSymbol("sfSoundRecorder_Create");
    sfSoundRecorder_Destroy = cast(pf_sfSoundRecorder_Destroy)s_lib.getSymbol("sfSoundRecorder_Destroy");
    sfSoundRecorder_Start = cast(pf_sfSoundRecorder_Start)s_lib.getSymbol("sfSoundRecorder_Start");
    sfSoundRecorder_Stop = cast(pf_sfSoundRecorder_Stop)s_lib.getSymbol("sfSoundRecorder_Stop");
    sfSoundRecorder_GetSampleRate = cast(pf_sfSoundRecorder_GetSampleRate)s_lib.getSymbol("sfSoundRecorder_GetSampleRate");
    sfSoundRecorder_CanCapture = cast(pf_sfSoundRecorder_CanCapture)s_lib.getSymbol("sfSoundRecorder_CanCapture");

	// sound.d
    sfSound_Create = cast(pf_sfSound_Create)s_lib.getSymbol("sfSound_Create");
    sfSound_Destroy = cast(pf_sfSound_Destroy)s_lib.getSymbol("sfSound_Destroy");
    sfSound_Play = cast(pf_sfSound_Play)s_lib.getSymbol("sfSound_Play");
    sfSound_Pause = cast(pf_sfSound_Pause)s_lib.getSymbol("sfSound_Pause");
    sfSound_Stop = cast(pf_sfSound_Stop)s_lib.getSymbol("sfSound_Stop");
    sfSound_SetBuffer = cast(pf_sfSound_SetBuffer)s_lib.getSymbol("sfSound_SetBuffer");
    sfSound_GetBuffer = cast(pf_sfSound_GetBuffer)s_lib.getSymbol("sfSound_GetBuffer");
    sfSound_SetLoop = cast(pf_sfSound_SetLoop)s_lib.getSymbol("sfSound_SetLoop");
    sfSound_GetLoop = cast(pf_sfSound_GetLoop)s_lib.getSymbol("sfSound_GetLoop");
    sfSound_GetStatus = cast(pf_sfSound_GetStatus)s_lib.getSymbol("sfSound_GetStatus");
    sfSound_SetPitch = cast(pf_sfSound_SetPitch)s_lib.getSymbol("sfSound_SetPitch");
    sfSound_SetVolume = cast(pf_sfSound_SetVolume)s_lib.getSymbol("sfSound_SetVolume");
    sfSound_SetPosition = cast(pf_sfSound_SetPosition)s_lib.getSymbol("sfSound_SetPosition");
    sfSound_GetPitch = cast(pf_sfSound_GetPitch)s_lib.getSymbol("sfSound_GetPitch");
    sfSound_GetVolume = cast(pf_sfSound_GetVolume)s_lib.getSymbol("sfSound_GetVolume");
    sfSound_GetPosition = cast(pf_sfSound_GetPosition)s_lib.getSymbol("sfSound_GetPosition");
    sfSound_GetPlayingOffset = cast(pf_sfSound_GetPlayingOffset)s_lib.getSymbol("sfSound_GetPlayingOffset");
    sfSound_GetMinDistance = cast(pf_sfSound_GetMinDistance)s_lib.getSymbol("sfSound_GetMinDistance");
    sfSound_GetAttenuation = cast(pf_sfSound_GetAttenuation)s_lib.getSymbol("sfSound_GetAttenuation");
    sfSound_SetMinDistance = cast(pf_sfSound_SetMinDistance)s_lib.getSymbol("sfSound_SetMinDistance");
    sfSound_SetAttenuation = cast(pf_sfSound_SetAttenuation)s_lib.getSymbol("sfSound_SetAttenuation");

    
    // listener.d
    sfListener_SetGlobalVolume = cast(pf_sfListener_SetGlobalVolume)s_lib.getSymbol("sfListener_SetGlobalVolume");
    sfListener_GetGlobalVolume = cast(pf_sfListener_GetGlobalVolume)s_lib.getSymbol("sfListener_GetGlobalVolume");
    sfListener_SetPosition = cast(pf_sfListener_SetPosition)s_lib.getSymbol("sfListener_SetPosition");
    sfListener_GetPosition = cast(pf_sfListener_GetPosition)s_lib.getSymbol("sfListener_GetPosition");
    sfListener_SetTarget = cast(pf_sfListener_SetTarget)s_lib.getSymbol("sfListener_SetTarget");
    sfListener_GetTarget = cast(pf_sfListener_GetTarget)s_lib.getSymbol("sfListener_GetTarget");

}
