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

module dsfml.audio.listener;

import dsfml.audio.external;

import dsfml.system.vector3;

/**
*   Listener is a global interface for defining the audio
*   listener properties ; the audio listener is the point in
*   the scene from where all the sounds are heard.
*   
*   See_Also:
*   $(LINK2 http://www.sfml-dev.org/tutorials/audio-spatialization.php, SFML Tutorial) for sound spatialization example.
*/
class Listener
{

    /**
    *   Change the global volume of all the sounds.
    *   The default volume is 100
    *
    *   Params:
    *       volume = New global volume, in the range [0, 100]
    */
    static void setGlobalVolume(float Volume)
    in
    {
        assert (Volume >= 0.f && Volume <= 100.f);
    }
    body
	{
		sfListener_SetGlobalVolume(Volume);
	}

    /**
    *   Get the current value of the global volume of all the sounds
    *
    *   Returns: 
    *       Current global volume, in the range [0, 100]
    */
    static float getGlobalVolume()
	{
		return sfListener_GetGlobalVolume();
	}

    /**
    *   Change the position of the listener.
    *   The default position is (0, 0, 0)
    *
    *   Params: 
    *       posX = X position of the listener in the world
    *       posY = Y position of the listener in the world
    *       posZ = Z position of the listener in the world
    */
    static void setPosition(float posX, float posY, float posZ)
	{
		sfListener_SetPosition(posX, posY, posZ);
	}

    /**
    *   Change the position of the listener.
    *   The default position is (0, 0, 0)
    *
    *   Params: 
    *       position = new position
    */
    static void setPosition(Vector3f position)
	{
		sfListener_SetPosition(position.x, position.y, position.z);
	}
 

    /**
    * Get the current position of the listener
    *
    *   Returns:
    *       Current position        
    */
    static Vector3f getPosition(Vector3f position)
	{
        Vector3f ret;
		sfListener_GetPosition(&ret.x, &ret.y, &ret.z);
		return ret;
	}

    /**
    *   Change the orientation of the listener (the point
    *   he must look at).
    *   The default target is (0, 0, -1)
    *   
    *   Params:    
    *       targetX = X position of the point the listener must look at
    *       targetY = X position of the point the listener must look at
    *       targetZ = X position of the point the listener must look at
    */
    static void setTarget(float targetX, float targetY, float targetZ)
	{
		sfListener_SetTarget(targetX, targetY, targetZ);
	}

    /**
    *   Change the orientation of the listener (the point
    *   he must look at).
    *   The default target is (0, 0, -1)
    *   
    *   Params:
    *       target = Position of the point the listener must look at   
    */
    static void setTarget(Vector3f position)
	{
		sfListener_SetTarget(position.x, position.y, position.z);
	}

    /**
    *   Get the current orientation of the listener (the point
    *   he's looking at)
    *
    *   Returns:
    *       Position of the point the listener is looking at    
    */
    static Vector3f getTarget()
	{
        Vector3f ret;
		sfListener_GetTarget(&ret.x, &ret.y, &ret.z);
		return ret;
	}
};
