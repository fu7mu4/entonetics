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

module dsfml.audio.external;

import dsfml.audio.soundstatus;

version(Dynamic)
{
    extern(C)
    {

        ////////////////////////////////////////////////////////////
        //listener.d
        ////////////////////////////////////////////////////////////
    	typedef void function(float) pf_sfListener_SetGlobalVolume;
    	typedef float function() pf_sfListener_GetGlobalVolume;
    	typedef void function(float, float, float) pf_sfListener_SetPosition;
    	typedef void function(float*, float*, float*) pf_sfListener_GetPosition;
    	typedef void function(float, float, float) pf_sfListener_SetTarget;
    	typedef void function(float*, float*, float*) pf_sfListener_GetTarget;
    	
    	pf_sfListener_SetGlobalVolume sfListener_SetGlobalVolume;
    	pf_sfListener_GetGlobalVolume sfListener_GetGlobalVolume;
    	pf_sfListener_SetPosition sfListener_SetPosition;
    	pf_sfListener_GetPosition sfListener_GetPosition;
    	pf_sfListener_SetTarget sfListener_SetTarget;
    	pf_sfListener_GetTarget sfListener_GetTarget;
    

        ////////////////////////////////////////////////////////////
        //music.d
        ////////////////////////////////////////////////////////////
        struct sfMusic {};
    
    	typedef sfMusic* function(char *) pf_sfMusic_CreateFromFile;
    	typedef sfMusic* function(byte *, size_t) pf_sfMusic_CreateFromMemory;
    	typedef void function(sfMusic*) pf_sfMusic_Destroy;
    	typedef void function(sfMusic*, int) pf_sfMusic_SetLoop;
    	typedef bool function(sfMusic*) pf_sfMusic_GetLoop;
    	typedef float function(sfMusic*) pf_sfMusic_GetDuration;
    	typedef void function(sfMusic*) pf_sfMusic_Play;
    	typedef void function(sfMusic*) pf_sfMusic_Pause;
    	typedef void function(sfMusic*) pf_sfMusic_Stop;
    	typedef uint function(sfMusic*) pf_sfMusic_GetChannelsCount;
    	typedef uint function(sfMusic*) pf_sfMusic_GetSampleRate;
    	typedef SoundStatus function(sfMusic*) pf_sfMusic_GetStatus;
    	typedef void function(sfMusic *Music, float) pf_sfMusic_SetPitch;
    	typedef void function(sfMusic *Music, float) pf_sfMusic_SetVolume;
    	typedef void function(sfMusic *Music, float, float, float) pf_sfMusic_SetPosition;
    	typedef float function(sfMusic*) pf_sfMusic_GetPitch;
    	typedef float function(sfMusic*) pf_sfMusic_GetVolume;
    	typedef void function(sfMusic*, float*, float*, float*) pf_sfMusic_GetPosition;
    	typedef float function(sfMusic*) pf_sfMusic_GetMinDistance;
    	typedef float function(sfMusic*) pf_sfMusic_GetAttenuation;
    	typedef void function(sfMusic*, float) pf_sfMusic_SetMinDistance;
    	typedef void function(sfMusic*, float) pf_sfMusic_SetAttenuation;

    
    	pf_sfMusic_CreateFromFile sfMusic_CreateFromFile;
    	pf_sfMusic_CreateFromMemory sfMusic_CreateFromMemory;
    	pf_sfMusic_Destroy sfMusic_Destroy;
    	pf_sfMusic_SetLoop sfMusic_SetLoop;
    	pf_sfMusic_GetLoop sfMusic_GetLoop;
    	pf_sfMusic_GetDuration sfMusic_GetDuration;
    	pf_sfMusic_Play sfMusic_Play;
    	pf_sfMusic_Pause sfMusic_Pause;
    	pf_sfMusic_Stop sfMusic_Stop;
    	pf_sfMusic_GetChannelsCount sfMusic_GetChannelsCount;
    	pf_sfMusic_GetSampleRate sfMusic_GetSampleRate;
    	pf_sfMusic_GetStatus sfMusic_GetStatus;
    	pf_sfMusic_SetPitch sfMusic_SetPitch;
    	pf_sfMusic_SetVolume sfMusic_SetVolume;
    	pf_sfMusic_SetPosition sfMusic_SetPosition;
    	pf_sfMusic_GetPitch sfMusic_GetPitch;
    	pf_sfMusic_GetVolume sfMusic_GetVolume;
    	pf_sfMusic_GetPosition sfMusic_GetPosition;
    	pf_sfMusic_GetMinDistance sfMusic_GetMinDistance;
    	pf_sfMusic_GetAttenuation sfMusic_GetAttenuation;
    	pf_sfMusic_SetMinDistance sfMusic_SetMinDistance;
    	pf_sfMusic_SetAttenuation sfMusic_SetAttenuation;

    
    
    
        ////////////////////////////////////////////////////////////
        //soundbuffer.d
        ////////////////////////////////////////////////////////////
    
    
        struct sfSoundBuffer {};
    
    	typedef sfSoundBuffer* function(char *) pf_sfSoundBuffer_CreateFromFile;
    	typedef sfSoundBuffer* function(byte*, size_t) pf_sfSoundBuffer_CreateFromMemory;
    	typedef sfSoundBuffer* function(short*, size_t, uint, uint) pf_sfSoundBuffer_CreateFromSamples;
    	typedef void function(sfSoundBuffer*) pf_sfSoundBuffer_Destroy;
    	typedef bool function(sfSoundBuffer*, char*) pf_sfSoundBuffer_SaveToFile;
    	typedef short* function(sfSoundBuffer*) pf_sfSoundBuffer_GetSamples;
    	typedef size_t function(sfSoundBuffer*) pf_sfSoundBuffer_GetSamplesCount;
    	typedef uint function(sfSoundBuffer*) pf_sfSoundBuffer_GetSampleRate;
    	typedef uint function(sfSoundBuffer*) pf_sfSoundBuffer_GetChannelsCount;
    	typedef float function(sfSoundBuffer*) pf_sfSoundBuffer_GetDuration;
    	
    	pf_sfSoundBuffer_CreateFromFile sfSoundBuffer_CreateFromFile;
    	pf_sfSoundBuffer_CreateFromMemory sfSoundBuffer_CreateFromMemory;
    	pf_sfSoundBuffer_CreateFromSamples sfSoundBuffer_CreateFromSamples;
    	pf_sfSoundBuffer_Destroy sfSoundBuffer_Destroy;
    	pf_sfSoundBuffer_SaveToFile sfSoundBuffer_SaveToFile;
    	pf_sfSoundBuffer_GetSamples sfSoundBuffer_GetSamples;
    	pf_sfSoundBuffer_GetSamplesCount sfSoundBuffer_GetSamplesCount;
    	pf_sfSoundBuffer_GetSampleRate sfSoundBuffer_GetSampleRate;
    	pf_sfSoundBuffer_GetChannelsCount sfSoundBuffer_GetChannelsCount;
    	pf_sfSoundBuffer_GetDuration sfSoundBuffer_GetDuration;

    
    
    
        ////////////////////////////////////////////////////////////
        //soundbufferrecorder.d
        ////////////////////////////////////////////////////////////
        
        
        struct sfSoundBufferRecorder {};
    
    	typedef sfSoundBufferRecorder* function() pf_sfSoundBufferRecorder_Create;
    	typedef void function(sfSoundBufferRecorder*) pf_sfSoundBufferRecorder_Destroy;
    	typedef void function(sfSoundBufferRecorder*, uint) pf_sfSoundBufferRecorder_Start;
    	typedef void function(sfSoundBufferRecorder*) pf_sfSoundBufferRecorder_Stop;
    	typedef uint function(sfSoundBufferRecorder*) pf_sfSoundBufferRecorder_GetSampleRate;
    	typedef sfSoundBuffer* function(sfSoundBufferRecorder*) pf_sfSoundBufferRecorder_GetBuffer;
    
    	pf_sfSoundBufferRecorder_Create sfSoundBufferRecorder_Create;
    	pf_sfSoundBufferRecorder_Destroy sfSoundBufferRecorder_Destroy;
    	pf_sfSoundBufferRecorder_Start sfSoundBufferRecorder_Start;
    	pf_sfSoundBufferRecorder_Stop sfSoundBufferRecorder_Stop;
    	pf_sfSoundBufferRecorder_GetSampleRate sfSoundBufferRecorder_GetSampleRate;
    	pf_sfSoundBufferRecorder_GetBuffer sfSoundBufferRecorder_GetBuffer;

    
    
    
        ////////////////////////////////////////////////////////////
        //soundrecorder.d
        ////////////////////////////////////////////////////////////
    
    
        struct sfSoundRecorder {};
    

    	typedef sfSoundRecorder* function(int function(short*, size_t, void*), void*) pf_sfSoundRecorder_Create;
    	typedef void function(sfSoundRecorder*) pf_sfSoundRecorder_Destroy;
    	typedef void function(sfSoundRecorder*, uint SampleRate) pf_sfSoundRecorder_Start;
    	typedef void function(sfSoundRecorder*) pf_sfSoundRecorder_Stop;
    	typedef uint function(sfSoundRecorder*) pf_sfSoundRecorder_GetSampleRate;
    	typedef bool function() pf_sfSoundRecorder_CanCapture;
    
    	pf_sfSoundRecorder_Create sfSoundRecorder_Create;
    	pf_sfSoundRecorder_Destroy sfSoundRecorder_Destroy;
    	pf_sfSoundRecorder_Start sfSoundRecorder_Start;
    	pf_sfSoundRecorder_Stop sfSoundRecorder_Stop;
    	pf_sfSoundRecorder_GetSampleRate sfSoundRecorder_GetSampleRate;
    	pf_sfSoundRecorder_CanCapture sfSoundRecorder_CanCapture;

    
        ////////////////////////////////////////////////////////////
        //sound.d
        ////////////////////////////////////////////////////////////
    
    
        struct sfSound {};
    
    	typedef sfSound* function() pf_sfSound_Create;
    	typedef void function(sfSound*) pf_sfSound_Destroy;
    	typedef void function(sfSound*) pf_sfSound_Play;
    	typedef void function(sfSound*) pf_sfSound_Pause;
    	typedef void function(sfSound*) pf_sfSound_Stop;
    	typedef void function(sfSound*, sfSoundBuffer*) pf_sfSound_SetBuffer;
    	typedef sfSoundBuffer* function(sfSound*) pf_sfSound_GetBuffer;
    	typedef void function(sfSound*, int) pf_sfSound_SetLoop;
    	typedef bool function(sfSound*) pf_sfSound_GetLoop;
    	typedef SoundStatus function(sfSound*) pf_sfSound_GetStatus;
    	typedef void function(sfSound*, float) pf_sfSound_SetPitch;
    	typedef void function(sfSound*, float) pf_sfSound_SetVolume;
    	typedef void function(sfSound*, float, float, float) pf_sfSound_SetPosition;
    	typedef float function(sfSound*) pf_sfSound_GetPitch;
    	typedef float function(sfSound*) pf_sfSound_GetVolume;
    	typedef void function(sfSound*, float*, float*, float*) pf_sfSound_GetPosition;
    	typedef float function(sfSound*) pf_sfSound_GetPlayingOffset;
    	typedef float function(sfSound*) pf_sfSound_GetMinDistance;
    	typedef float function(sfSound*) pf_sfSound_GetAttenuation;
    	typedef void function(sfSound*, float) pf_sfSound_SetMinDistance;
    	typedef void function(sfSound*, float) pf_sfSound_SetAttenuation;

    	
    
    
    	pf_sfSound_Create sfSound_Create;
    	pf_sfSound_Destroy sfSound_Destroy;
    	pf_sfSound_Play sfSound_Play;
    	pf_sfSound_Pause sfSound_Pause;
    	pf_sfSound_Stop sfSound_Stop;
    	pf_sfSound_SetBuffer sfSound_SetBuffer;
    	pf_sfSound_GetBuffer sfSound_GetBuffer;
    	pf_sfSound_SetLoop sfSound_SetLoop;
    	pf_sfSound_GetLoop sfSound_GetLoop;
    	pf_sfSound_GetStatus sfSound_GetStatus;
    	pf_sfSound_SetPitch sfSound_SetPitch;
    	pf_sfSound_SetVolume sfSound_SetVolume;
    	pf_sfSound_SetPosition sfSound_SetPosition;
    	pf_sfSound_GetPitch sfSound_GetPitch;
    	pf_sfSound_GetVolume sfSound_GetVolume;
    	pf_sfSound_GetPosition sfSound_GetPosition;
    	pf_sfSound_GetPlayingOffset sfSound_GetPlayingOffset;
    	pf_sfSound_GetMinDistance sfSound_GetMinDistance;
    	pf_sfSound_GetAttenuation sfSound_GetAttenuation;
    	pf_sfSound_SetMinDistance sfSound_SetMinDistance;
    	pf_sfSound_SetAttenuation sfSound_SetAttenuation;
    }
}
else
{
    extern(C)
    {
        //listener.d
        void sfListener_SetGlobalVolume(float);
        float sfListener_GetGlobalVolume();
        void sfListener_SetPosition(float, float, float);
        void sfListener_GetPosition(float*, float*, float*);
        void sfListener_SetTarget(float, float, float);
        void sfListener_GetTarget(float*, float*, float*);
        
        //music.d
        struct sfMusic {};
        
        sfMusic* sfMusic_CreateFromFile(char *);
        sfMusic* sfMusic_CreateFromMemory(byte *, size_t);
        void sfMusic_Destroy(sfMusic*);
        void sfMusic_SetLoop(sfMusic*, int);
        bool sfMusic_GetLoop(sfMusic*);
        float sfMusic_GetDuration(sfMusic*);
        void sfMusic_Play(sfMusic*);
        void sfMusic_Pause(sfMusic*);
        void sfMusic_Stop(sfMusic*);
        uint sfMusic_GetChannelsCount(sfMusic*);
        uint sfMusic_GetSampleRate(sfMusic*);
        SoundStatus sfMusic_GetStatus(sfMusic*);
        void sfMusic_SetPitch(sfMusic *Music, float);
        void sfMusic_SetVolume(sfMusic *Music, float);
        void sfMusic_SetPosition(sfMusic *Music, float, float, float);
        float sfMusic_GetPitch(sfMusic*);
        float sfMusic_GetVolume(sfMusic*);
        void sfMusic_GetPosition(sfMusic*, float*, float*, float*);
        float sfMusic_GetMinDistance(sfMusic*);
        float sfMusic_GetAttenuation(sfMusic*);
        void sfMusic_SetMinDistance(sfMusic*, float);
        void sfMusic_SetAttenuation(sfMusic*, float);

    
        //soundbuffer.d
        struct sfSoundBuffer {};
        
        sfSoundBuffer* sfSoundBuffer_CreateFromFile(char *);
        sfSoundBuffer* sfSoundBuffer_CreateFromMemory(byte*, size_t);
        sfSoundBuffer* sfSoundBuffer_CreateFromSamples(short*, size_t, uint, uint);
        void sfSoundBuffer_Destroy(sfSoundBuffer*);
        bool sfSoundBuffer_SaveToFile(sfSoundBuffer*, char*);
        short* sfSoundBuffer_GetSamples(sfSoundBuffer*);
        size_t sfSoundBuffer_GetSamplesCount(sfSoundBuffer*);
        uint sfSoundBuffer_GetSampleRate(sfSoundBuffer*);
        uint sfSoundBuffer_GetChannelsCount(sfSoundBuffer*);
        float sfSoundBuffer_GetDuration(sfSoundBuffer*);
    
        //soundbufferrecorder.d
        struct sfSoundBufferRecorder {};
        
        sfSoundBufferRecorder* sfSoundBufferRecorder_Create();
        void sfSoundBufferRecorder_Destroy(sfSoundBufferRecorder*);
        void sfSoundBufferRecorder_Start(sfSoundBufferRecorder*, uint);
        void sfSoundBufferRecorder_Stop(sfSoundBufferRecorder*);
        uint sfSoundBufferRecorder_GetSampleRate(sfSoundBufferRecorder*);
        sfSoundBuffer* sfSoundBufferRecorder_GetBuffer(sfSoundBufferRecorder*);
        
        //soundrecorder.d
        struct sfSoundRecorder {};
        
        sfSoundRecorder* sfSoundRecorder_Create(int function(short*, size_t, void*), void*);
        void sfSoundRecorder_Destroy(sfSoundRecorder*);
        void sfSoundRecorder_Start(sfSoundRecorder*, uint SampleRate);
        void sfSoundRecorder_Stop(sfSoundRecorder*);
        uint sfSoundRecorder_GetSampleRate(sfSoundRecorder*);
        bool sfSoundRecorder_CanCapture();
        
        //sound.d
        struct sfSound{} ;
        
        sfSound* sfSound_Create();
        void sfSound_Destroy(sfSound*);
        void sfSound_Play(sfSound*);
        void sfSound_Pause(sfSound*);
        void sfSound_Stop(sfSound*);
        void sfSound_SetBuffer(sfSound*, sfSoundBuffer*);
        sfSoundBuffer* sfSound_GetBuffer(sfSound*);
        void sfSound_SetLoop(sfSound*, int);
        bool sfSound_GetLoop(sfSound*);
        SoundStatus sfSound_GetStatus(sfSound*);
        void sfSound_SetPitch(sfSound*, float);
        void sfSound_SetVolume(sfSound*, float);
        void sfSound_SetPosition(sfSound*, float, float, float);
        float sfSound_GetPitch(sfSound*);
        float sfSound_GetVolume(sfSound*);
        void sfSound_GetPosition(sfSound*, float*, float*, float*);
        float sfSound_GetPlayingOffset(sfSound*);
        float sfSound_GetMinDistance(sfSound*);
        float sfSound_GetAttenuation(sfSound*);
        void sfSound_SetMinDistance(sfSound*, float);
        void sfSound_SetAttenuation(sfSound*, float);

    
    }
}
