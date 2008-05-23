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

module dsfml.system.clock;

import dsfml.system.external;
import dsfml.system.pointerchecker;

/**
 *  Utility class for manipulating time
 */ 
class Clock
{
    /**
     *  Default constructor
     */        
    this()
    {
        m_Clock = sfClock_Create();
    }

    /**
     *  Destructor        
     */        
    ~this()
    {
        sfClock_Destroy(m_Clock);
    }

    /**
     *  Return the time elapsed since the last reset
     *  Returns: 
     *      Elapsed Time in seconds                          
     */        
    float getElapsedTime()
    {
        return sfClock_GetTime(m_Clock);
    }

    /**
     *  Restart the timer        
     */        
    void reset()
    {
        sfClock_Reset(m_Clock);
    }

private:
    sfClock* m_Clock;
    
    mixin TEnforcePointer!(m_Clock);     
}

