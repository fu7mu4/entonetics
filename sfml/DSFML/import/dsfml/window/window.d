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

module dsfml.window.window;

import dsfml.window.external;
import dsfml.window.event;
import dsfml.window.input;
import dsfml.window.videomode;
import dsfml.window.windowhandle;
import dsfml.window.windowsettings;
import dsfml.window.windowstyle;

import dsfml.system.pointerchecker;
import dsfml.system.stringutil;

/**
*   Window is a rendering window ; it can create a new window
*   or connect to an existing one
*/
class  Window
{    
    /**
    *   Construct a new window
    *
    *   Params:
    *       mode = Video mode to use
    *       title = Title of the window
    *       windowStyle = Window style (Resize | Close by default)
    *       antialiasingLevel = Level of antialiasing (0 by default, disabled)
    */
    this(VideoMode mode, char[] title, Style windowStyle = Style.RESIZE | Style.CLOSE, WindowSettings settings = WindowSettings())
    {
        m_Window = sfWindow_Create(mode, toStringz(title), windowStyle, settings);
    }

    /**
    *   Construct the window from an existing control
    *
    *   Params:
    *       handle = Platform-specific handle of the control
    *       antialiasingLevel = Level of antialiasing (0 by default, disabled)
    */
    this(WindowHandle handle, WindowSettings settings = WindowSettings())
    {
        m_Window = sfWindow_CreateFromHandle(handle, settings);
    }

    /*
    *   Destructor
    */ 
    ~this()
    {
        if (!m_disposed)
        {
            m_input = null;
            sfWindow_Destroy(m_Window);       
        }
        m_Window = null;
    }

    /**
    *   Create (or recreate) the window
    *   
    *   Input created with getInput becomes invalid.   
    *                
    *   Params:
    *       mode = Video mode to use
    *       title = Title of the window
    *       windowStyle = Window style (Resize | Close by default)
    *       antialiasingLevel = Level of antialiasing (0 by default, disabled)
    */
    void create(VideoMode mode, char[] title, Style windowStyle = Style.RESIZE | Style.CLOSE, WindowSettings settings = WindowSettings())
    {
        if (m_Window !is null)
        {
            if (m_input !is null)
            {
                delete m_input;
                m_input = null;
            }
            sfWindow_Destroy(m_Window);
        }
        m_Window = sfWindow_Create(mode, toStringz(title), windowStyle, settings);
    }

    /**
    *   Create (or recreate) the window from an existing control
    *   
    *   Input created with getInput becomes invalid.   
    *                
    *   Params:
    *       handle = Platform-specific handle of the control
    *       antialiasingLevel = Level of antialiasing (0 by default, disabled)
    */
    void create(WindowHandle handle, WindowSettings settings = WindowSettings())
    {
        if (m_Window !is null)
        {
            if (m_input !is null)
            {
                delete m_input;
                m_input = null;
            }
            sfWindow_Destroy(m_Window);
        }
        m_Window = sfWindow_CreateFromHandle(handle, settings);
    }

    /**
    *   Close (destroy) the window.
    *   You can call create to recreate a valid window    
    */        
    void close()
    {
        if (m_Window !is null)
        {
            sfWindow_Close(m_Window);
        }
    }

    /**
    *   Tell whether or not a window is opened
    *   
    *   Returns:
    *       True if window is currently open.    
    */        
    bool isOpened()
    {
        if (m_Window !is null)
        {
            return sfWindow_IsOpened(m_Window);
        }
        return false;
    }
    /**
    *   Get the width of the rendering region of the window
    *
    *   Returns:
    *       Width in pixels
    */
    uint getWidth()
    {
        return sfWindow_GetWidth(m_Window);
    }

    /**
    *   Get the height of the rendering region of the window
    *
    *   Returns:
    *       Height in pixels
    */
    uint getHeight()
    {
        return sfWindow_GetHeight(m_Window);
    }

    /**
    *   Get the creation settings of a window
    *   
    *   Returns:
    *       Settings used to create the window            
    */
    WindowSettings getSettings()
    {
        return sfWindow_GetSettings(m_Window);
    }        


    /**
    *   Get the event on top of events stack, if any, and pop it
    *
    *   Params:
    *       eventReceived = Event to fill, if any
    *
    *   Returns:
    *       True if an event was returned, false if events stack was empty
    */
    bool getEvent(ref Event eventReceived)
    {
        return sfWindow_GetEvent(m_Window, &eventReceived);
    }

    /**
    *   Enable / disable vertical synchronization
    *
    *   Params: 
    *       enabled : True to enable v-sync, false to deactivate
    */
    void useVerticalSync(bool enabled)
    {
        sfWindow_UseVerticalSync(m_Window, enabled);
    }

    /**
    *   Show or hide the mouse cursor
    *
    *   Params:
    *       show : True to show, false to hide
    */
    void showMouseCursor(bool show)
    {
        sfWindow_ShowMouseCursor(m_Window, show);
    }

    /**
    *   Change the position of the mouse cursor
    *
    *   Params:
    *       left = Left coordinate of the cursor, relative to the window
    *       top = Top coordinate of the cursor, relative to the window
    */
    void setCursorPosition(uint left, uint top)
    {
        sfWindow_SetCursorPosition(m_Window, left, top);
    }

    /**
    *   Change the position of the window on screen.
    *   Only works for top-level windows
    *
    *   Params:
    *       left = Left position
    *       top = Top position
    */
    void setPosition(int left, int top)
    {
        sfWindow_SetPosition(m_Window, left, top);
    }

    /**
    *   Show or hide the window
    *
    *   Params:
    *       state = True to show, false to hide
    *
    */
    void show(bool state)
    {
        sfWindow_Show(m_Window, state);
    }

    /**
    *   Enable or disable automatic key-repeat for keydown events.
    *   Automatic key-repeat is enabled by default.
    *   
    *   Params:
    *       enabled = true to enable, false to disable            
    */        
    void enableKeyRepeat(bool enabled)
    {
        sfWindow_EnableKeyRepeat(m_Window, enabled);
    }
    /**
    *   Set the window as the current target for rendering
    *   
    *   Params:
    *       active = True to activate, false to deactivate        
    *   Returns:
    *       True if operation was successful, false otherwise
    */
    bool setActive(bool active)
    {
        if (m_Window !is null)
        {
            return sfWindow_SetActive(m_Window, active);
        }
    }

    /**
    * Display the window on screen
    */
    void display()
    {
        sfWindow* dumm_ = m_Window;
        sfWindow_Display(dumm_);
    }

    /**
    * Get the input manager of the window
    *
    *   Returns: 
    *       An input manager
    *   See_Also :
    *       Input
    */
    Input getInput()
    {
        if (m_input is null)
            m_input = new Input(sfWindow_GetInput(m_Window));
        return m_input;
    }

    /**
    *   Limit the framerate to a maximum fixed frequency
    *
    *   Params:
    *       limit : Framerate limit, in frames per seconds (use 0 to disable limit)
    */
    void setFramerateLimit(uint limit)
    {
        sfWindow_SetFramerateLimit(m_Window, limit);
    }

    /**
    *   Get time elapsed since last frame
    *
    *   Returns:
    *       Time elapsed, in seconds
    */
    float getFrameTime()
    {
        return sfWindow_GetFrameTime(m_Window);
    }

    /**
    *   Change the joystick threshold, ie. the value below which
    *   no move event will be generated
    *
    *   Params:
    *       threshold : New threshold, in range [0, 100]
    */
    void setJoystickThreshold(float threshold)
    {
        sfWindow_SetJoystickThreshold(m_Window, threshold);
    }
    
protected:
    this()
    {
        
    }

    sfWindow* m_Window;
    Input m_input;
    bool m_disposed;
    
    mixin TEnforcePointer!(m_Window);
}
