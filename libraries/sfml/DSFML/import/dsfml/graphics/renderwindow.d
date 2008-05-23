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

module dsfml.graphics.renderwindow;

import dsfml.graphics.color;
import dsfml.graphics.external;
import dsfml.graphics.idrawable;
import dsfml.graphics.image;
import dsfml.graphics.rect;
import dsfml.graphics.sprite;
import dsfml.graphics.string;
import dsfml.graphics.shape;
import dsfml.graphics.postfx;
import dsfml.graphics.view;

import dsfml.window.event;
import dsfml.window.external;
import dsfml.window.input;
import dsfml.window.videomode;
import dsfml.window.window;
import dsfml.window.windowhandle;
import dsfml.window.windowsettings;
import dsfml.window.windowstyle;

import dsfml.system.stringutil;
import dsfml.system.vector2;

/**
*   Simple wrapper for Window that allows easy 2D rendering. 
*/
class RenderWindow : Window
{
    /**
    *   Construct the window
    *
    *   Params:    
    *       mode = Video mode to use
    *       title = Title of the window
    *       windowStyle = Window style (Resize | Close by default)
    *       antialiasingLevel = Level of antialiasing (0 by default, disabled)
    */
    this(VideoMode mode, in char[] title, ulong windowStyle = Style.RESIZE | Style.CLOSE, WindowSettings settings = WindowSettings())
    {
        m_Window = cast(sfWindow*)sfRenderWindow_Create(mode, toStringz(title), windowStyle, settings);
        m_input = new Input(sfRenderWindow_GetInput(cast(sfRenderWindow*)m_Window));
        
        super();
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
        m_Window = cast(sfWindow*)sfRenderWindow_CreateFromHandle(handle, settings);
        m_input = new Input(sfRenderWindow_GetInput(cast(sfRenderWindow*)m_Window));
        
        super();
    }

    /**
    *   Destructor
    */
    ~this()
    {
        sfRenderWindow_Destroy(cast(sfRenderWindow*)m_Window);
        m_input = null;
        m_disposed = true;
    }

    /**
    *   Create (or recreate) the window
    *   
    *   Input created with getInput will become invalid.
    *                   
    *   Params:        
    *       mode = Video mode to use
    *       title = Title of the window
    *       windowStyle = Window style (Resize | Close by default)
    *       antialiasingLevel = Level of antialiasing (0 by default, disabled)
    *
    */
    void create(VideoMode mode, char[] title, ulong windowStyle = Style.RESIZE | Style.CLOSE, WindowSettings settings = WindowSettings())
    {
        if (m_Window !is null)
        {
            delete m_input;
            m_input = null;
            sfRenderWindow_Destroy(cast(sfRenderWindow*)m_Window);
        }

        m_Window = cast(sfWindow*)sfRenderWindow_Create(mode, toStringz(title), windowStyle, settings);
        m_input = new Input(sfRenderWindow_GetInput(cast(sfRenderWindow*)m_Window));
    }

    /**
    *   Create (or recreate) the window from an existing control
    *   
    *   Input created with getInput become invalid.
    *                   
    *   Params:        
    *       handle = Platform-specific handle of the control
    *       antialiasingLevel = Level of antialiasing (0 by default, disabled)
    *
    */
    void create(WindowHandle handle, WindowSettings settings = WindowSettings())
    {
        if (m_Window !is null)
        {
            delete m_input;
            m_input = null;
            sfRenderWindow_Destroy(cast(sfRenderWindow*)m_Window);
        }
    
        m_Window = cast(sfWindow*)sfRenderWindow_CreateFromHandle(handle, settings);
        m_input = new Input(sfRenderWindow_GetInput(cast(sfRenderWindow*)m_Window));
    }

    /**
    *   Draw a PostFX on the window
    *
    *   Params:
    *       postFX = Object to draw
    */
    void draw(PostFX postFX)
    {
        sfRenderWindow_DrawPostFX(cast(sfRenderWindow*)m_Window, postFX.toCPostFX());
    }

    /**
    *   Draw a Sprite or a String
    *   
    *   Params:
    *       obj = IDrawable object to draw                    
    */                
    void draw(IDrawable obj)
    {
        if (cast(Sprite)obj !is null)
            sfRenderWindow_DrawSprite(cast(sfRenderWindow*)m_Window, (cast(Sprite)obj).toCSprite());
        else if (cast(String)obj !is null)
            sfRenderWindow_DrawString(cast(sfRenderWindow*)m_Window, (cast(String)obj).toCString());
        else if (cast(Shape)obj !is null)
            sfRenderWindow_DrawShape(cast(sfRenderWindow*)m_Window, (cast(Shape)obj).toCShape());
    }   
    /**
    *   Save the content of the window to an image
    *
    *   Returns:
    *       Image instance containing the contents of the screen
    */
    Image capture()
    {
        return(new Image(sfRenderWindow_Capture(cast(sfRenderWindow*)m_Window)));
    }

    /**
    *   Change the background color of the window.
    *   The default color is black
    *
    *   Params:
    *       col = New background color
    */
    void setBackgroundColor(Color col)
    {
        sfRenderWindow_SetBackgroundColor(cast(sfRenderWindow*)m_Window, col);
    }

    /**
    *   Change the current active view.
    *   The current view is defined with the initial size of the window
    *
    *   Params: 
    *       newView = Pointer to the new view (pass NULL to set the default view)
    */
    void setView(View newView)
    {
        if (newView is null)
            sfRenderWindow_SetView(cast(sfRenderWindow*)m_Window, null);
        else
        {
            sfRenderWindow_SetView(cast(sfRenderWindow*)m_Window, newView.toCView());
        }
        m_view = newView;
    }

    /**
    *   Get the current view rectangle
    *
    *   Returns: 
    *       current view rectangle, in global coordinates
    */
    View getView()
    {
        if (m_view is null)
        {
            sfView* cView = sfRenderWindow_GetView(cast(sfRenderWindow*)m_Window);
            m_view = new View(cView);
        }
        return m_view;
    }

    View getDefaultView()
    {
        if (m_defaultView is null)
        {
            sfView* cView = sfRenderWindow_GetDefaultView(cast(sfRenderWindow*)m_Window);
            m_defaultView = new View(cView);
        }
        return m_defaultView;
    }

    /**
    *   Convert a point in window coordinates into view coordinates
    *
    *   Params: 
    *       windowX :      X coordinate of the point to convert, relative to the window
    *       windowY :      Y coordinate of the point to convert, relative to the window
    *       targetView :   Target view to convert the point to (pass NULL to use the current view)
    *       
    *   Returns:
    *       Converted point            
    */     
    Vector2f ConvertCoords(uint windowX, uint windowY, View targetView = null)
    {
        Vector2f vec;
        sfRenderWindow_ConvertCoords(cast(sfRenderWindow*)m_Window, windowX, windowY, &vec.x, &vec.y, targetView.toCView());
        return vec;
    }

    /**
    *   Tell SFML to preserve external OpenGL states, at the expense of
    *   more CPU charge. Use this function if you don't want SFML
    *   to mess up your own OpenGL states (if any).
    *   Don't enable state preservation if not needed, as it will allow
    *   SFML to do internal optimizations and improve performances.
    *   This parameter is false by default
    *
    *   Params: 
    *       Preserve = True to preserve OpenGL states, false to let SFML optimize
    *
    */
    void preserveOpenGLStates(bool preserve)
    {
        sfRenderWindow_PreserveOpenGLStates(cast(sfRenderWindow*)m_Window, preserve);
    }

private:
    View m_view = null;
    View m_defaultView = null;
}

