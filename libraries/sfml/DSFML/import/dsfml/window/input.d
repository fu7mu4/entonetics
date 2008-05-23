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

module dsfml.window.input;

import dsfml.window.external;

import dsfml.window.event;

/**
*   Input handles real-time input from keyboard and mouse.
*   Use it instead of events to handle continuous moves and more
*   game-friendly inputs
*/
class Input
{

    /**
    *   Get the state of a key
    *
    *   Params:
    *       key = Key to check
    *
    *   Returns:
    *       True if key is down, false if key is up
    */
    bool isKeyDown(KeyCode key)
	{
		return cast(bool)sfInput_IsKeyDown(m_Input, key);
	}

    /**
    *   Get the state of a mouse button
    *
    *   Params: 
    *       button = Button to check
    *
    *   Returns: 
    *       True if button is down, false if button is up
    */
    bool isMouseButtonDown(MouseButtons button)
	{
		return cast(bool)sfInput_IsMouseButtonDown(m_Input, button);
	}

    /**
    *   Get the state of a joystick button
    *
    *   Params: 
    *       joyId = Identifier of the joystick to check (0 or 1)
    *       button = Button to check
    *
    *   Returns: 
    *       True if button is down, false if button is up
    */
    bool isJoystickButtonDown(uint joyId, uint button)
	{
		return cast(bool)sfInput_IsJoystickButtonDown(m_Input, joyId, button);
	}

    /*
    *   Get the mouse X position
    *
    *   Returns:
    *       Current mouse left position, relative to owner window
    */
    uint getMouseX()
	{
		return sfInput_GetMouseX(m_Input);
	}

    /**
    *   Get the mouse Y position
    *
    *   Returns:
    *       Current mouse top position, relative to owner window
    *
    */
    uint getMouseY()
	{
		return sfInput_GetMouseY(m_Input);
	}

    /**
    * Get a joystick axis position
    *
    *   Params:    
    *       joyId = Identifier of the joystick to check (0 or 1)
    *       axis =  Axis to get
    *
    *   Returns:
    *       Current axis position, in the range [-100, 100] (except for POV, which is [0, 360])
    */
    float getJoystickAxis(uint joyId, JoyAxis axis)
	{
		return sfInput_GetJoystickAxis(m_Input, joyId, axis);
	}

    this(sfInput* input)
	{
		m_Input = input;
	}


private:
    ////////////////////////////////////////////////////////////
    // Member
    ////////////////////////////////////////////////////////////
	sfInput* m_Input;
}
