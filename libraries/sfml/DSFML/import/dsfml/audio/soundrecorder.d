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

module dsfml.audio.soundrecorder;

import dsfml.audio.external;
import dsfml.audio.soundbuffer;

import dsfml.system.pointerchecker;


/**
*   SoundRecorder is an interface for capturing sound data,
*   it is meant to be used as a base class
*   
*   Examples:
*   
*   Can be used directly :
*   -------
*   bool callback(short* data, size_t size, void* userData)
*   {
*       //Process data
*       
*       return true; //return true to continue capture, else return false  
*   }
*
*   void main()
*   {
*       SoundRecorder record = new SoundRecorder(&callback);
*       record.Start(); //Start recording with default sample rate.
*   }
*   -------
*   
*   or as base class
*   
*   -------
*   
*   class MySoundRecorder : SoundRecorder
*   {
*       this()
*       {
*             
*       }
*       
*       //Override this method
*       protected bool processSamples(short* data, size_t size)
*       {
*           // Process data here
*           
*           return true; //return true to continue capture, else return false  
*       }
*   } 
*   -------
*/
class SoundRecorder
{
    alias bool function(short*, size_t, void*) FuncType;
    alias bool delegate(short*, size_t, void*) DelegType;
    
    /**
    *   Construct the sound recorder with a callback function for processing captured samples
    *
    *   Params: 
    *       callback = Callback for processing captured samples
    *       userData = Data to pass to the callback function (null by default)
    */
    this(bool function(short*, size_t, void*) callback, void* userData = null)
    {
        m_fcallback = callback;
        m_userData = userData;
        m_id = ++seed;
        m_type = Type.FUNCTION;
        
        // if pointer has not been already created
        if (m_SoundRecorder is null)
        {
            m_instances[m_id] = this;
            m_SoundRecorder = sfSoundRecorder_Create(&internalCallback, cast(void*)seed);
        }
    }

    /**
    *   Construct the sound recorder with a delegate for processing captured samples
    *
    *   Params: 
    *       callback = Callback for processing captured samples
    *       userData = Data to pass to the callback function (null by default)
    */
    this(bool delegate(short*, size_t, void*) callback, void* userData = null)
    {
        m_dcallback = callback;
        m_userData = userData;
        m_id = ++seed;
        m_type = Type.DELEGATE;
        
        // if pointer has not been already created
        if (m_SoundRecorder is null)
        {
            m_instances[m_id] = this;
            m_SoundRecorder = sfSoundRecorder_Create(&internalCallback, cast(void*)seed);
        }
    }

    /**
    *   Destructor
    */
    ~this()
    {
        if (!m_disposed)
        {
            sfSoundRecorder_Destroy(m_SoundRecorder);
            m_instances.remove(m_id);
        }
    }


    /**
    *   Start the capture.
    *   
    *   Only one capture can happen at the same time
    *
    *   Params: 
    *       sampleRate : Sound frequency (the more samples, the higher the quality)
    *                    (44100 by default = CD quality)
    */
    void start(uint sampleRate = 44100)
    {
        sfSoundRecorder_Start(m_SoundRecorder, sampleRate);
    }

    /**
    *   Stop the capture
    */
    void stop()
    {
        sfSoundRecorder_Stop(m_SoundRecorder);
    }

    /**
    *   Get the sample rate
    *
    *   Returns: 
    *       Frequency, in samples per second
    */
    uint getSampleRate() 
    {
        if (m_SoundRecorder !is null)
            return sfSoundRecorder_GetSampleRate(m_SoundRecorder);
        else return 0;
    }

    /**
    *   Tell if the system supports sound capture.
    *   If not, this class won't be usable
    *
    *   Returns:
    *       True if audio capture is supported
    *
    */
    static bool canCapture()
    {
        return sfSoundRecorder_CanCapture();
    }

protected:
    this()
    {
        m_type = Type.BASE;
        // if pointer has not been already created
        if (m_SoundRecorder is null)
        {
            m_id = ++seed;
            m_instances[m_id] = this;
            m_SoundRecorder = sfSoundRecorder_Create(&internalCallback, cast(void*)seed);
        }

    }
    bool processSamples(short* s, size_t size)
    {
        return true;
    }

    sfSoundRecorder* m_SoundRecorder;
    bool m_disposed;
    
private:
    union
    {
        FuncType m_fcallback;
        DelegType m_dcallback;
    }
    
    void* m_userData;
    int m_id;
    
    static int seed = 0;
    static SoundRecorder[int] m_instances;
    
    enum Type
    {
        BASE,
        DELEGATE,
        FUNCTION
    }

    Type m_type;

    /*
    *   Extern C callback function
    *           
    *   This function must be static for C interop. To retrieve the current
    *   instance, we retrieve id of the sender in the user data, and search it
    *   in the associative array                        
    */
    extern(C) static int internalCallback(short* s, size_t size, void* user)
    {
        // retrieve instance
        if (cast(int)user in m_instances)
        {
            SoundRecorder temp = m_instances[cast(int)user];
            
            //If used directly
            if (temp.m_type == Type.FUNCTION)
                return temp.m_fcallback(s, size, temp.m_userData);
            else if (temp.m_type == Type.DELEGATE)
                return temp.m_dcallback(s, size, temp.m_userData);
            //else this is a base class
            else
                return temp.processSamples(s, size);
        }
        else
            return true; 
    }
    
    mixin TEnforcePointer!(m_SoundRecorder);
}
