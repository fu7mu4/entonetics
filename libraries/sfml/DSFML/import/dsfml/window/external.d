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

module dsfml.window.external;

import dsfml.window.event;
import dsfml.window.videomode;
import dsfml.window.windowhandle;
import dsfml.window.windowsettings;


version (Dynamic)
{
    extern(C)
    {
        ////////////////////////////////////////////////////////////
        //input.d
        ////////////////////////////////////////////////////////////
        struct sfInput {};
    
    
    	typedef int function(sfInput*, KeyCode) pf_sfInput_IsKeyDown;
    	typedef int function(sfInput*, MouseButtons) pf_sfInput_IsMouseButtonDown;
    	typedef int function(sfInput*, uint, uint) pf_sfInput_IsJoystickButtonDown;
    	typedef uint function (sfInput*) pf_sfInput_GetMouseX;
    	typedef uint function(sfInput*) pf_sfInput_GetMouseY;
    	typedef float function(sfInput*, uint, JoyAxis) pf_sfInput_GetJoystickAxis;
    
    	pf_sfInput_IsKeyDown sfInput_IsKeyDown;
    	pf_sfInput_IsMouseButtonDown sfInput_IsMouseButtonDown;
    	pf_sfInput_IsJoystickButtonDown sfInput_IsJoystickButtonDown;
    	pf_sfInput_GetMouseX sfInput_GetMouseX;
    	pf_sfInput_GetMouseY sfInput_GetMouseY;
    	pf_sfInput_GetJoystickAxis sfInput_GetJoystickAxis;


        ////////////////////////////////////////////////////////////
        //videomode.d
        ////////////////////////////////////////////////////////////        
    	typedef VideoMode function() pf_sfVideoMode_GetDesktopMode;
    	typedef VideoMode function(size_t) pf_sfVideoMode_GetMode;
    	typedef size_t function() pf_sfVideoMode_GetModesCount;
    	typedef bool function(VideoMode) pf_sfVideoMode_IsValid;
    
    	pf_sfVideoMode_GetDesktopMode sfVideoMode_GetDesktopMode;
    	pf_sfVideoMode_GetMode sfVideoMode_GetMode;
    	pf_sfVideoMode_GetModesCount sfVideoMode_GetModesCount;
    	pf_sfVideoMode_IsValid sfVideoMode_IsValid;



        ////////////////////////////////////////////////////////////
        //window.d
        ////////////////////////////////////////////////////////////

        struct sfWindow {};
        
        
    	typedef sfWindow* function(VideoMode, char*, ulong, WindowSettings) pf_sfWindow_Create;
    	typedef sfWindow* function(WindowHandle, WindowSettings) pf_sfWindow_CreateFromHandle;
    	typedef void function(sfWindow*) pf_sfWindow_Destroy;
    	typedef void function(sfWindow*) pf_sfWindow_Close;
    	typedef bool function(sfWindow*) pf_sfWindow_IsOpened;
    	typedef uint function(sfWindow*) pf_sfWindow_GetWidth;
    	typedef uint function(sfWindow*) pf_sfWindow_GetHeight;
    	typedef WindowSettings function(sfWindow* Window) pf_sfWindow_GetSettings;
    	typedef bool function(sfWindow*, Event*) pf_sfWindow_GetEvent;
    	typedef void function(sfWindow*, int) pf_sfWindow_UseVerticalSync;
    	typedef void function(sfWindow*, int) pf_sfWindow_ShowMouseCursor;
    	typedef void function(sfWindow*, uint, uint) pf_sfWindow_SetCursorPosition;
    	typedef void function(sfWindow*, int, int) pf_sfWindow_SetPosition;
    	typedef void function(sfWindow*, int) pf_sfWindow_Show;
    	typedef void function(sfWindow*, bool) pf_sfWindow_EnableKeyRepeat;
    	typedef bool function(sfWindow*, bool) pf_sfWindow_SetActive;
    	typedef void function(sfWindow*) pf_sfWindow_Display;
    	typedef sfInput* function(sfWindow*) pf_sfWindow_GetInput;
    	typedef void function(sfWindow*, uint) pf_sfWindow_SetFramerateLimit;
    	typedef float function(sfWindow*) pf_sfWindow_GetFrameTime;
    	typedef void function(sfWindow*, float) pf_sfWindow_SetJoystickThreshold;
    
    	pf_sfWindow_Create sfWindow_Create;
    	pf_sfWindow_CreateFromHandle sfWindow_CreateFromHandle;
    	pf_sfWindow_Destroy sfWindow_Destroy;
    	pf_sfWindow_Close sfWindow_Close;
    	pf_sfWindow_IsOpened sfWindow_IsOpened;
    	pf_sfWindow_GetWidth sfWindow_GetWidth;
    	pf_sfWindow_GetHeight sfWindow_GetHeight;
    	pf_sfWindow_GetSettings sfWindow_GetSettings;
    	pf_sfWindow_GetEvent sfWindow_GetEvent;
    	pf_sfWindow_UseVerticalSync sfWindow_UseVerticalSync;
    	pf_sfWindow_ShowMouseCursor sfWindow_ShowMouseCursor;
    	pf_sfWindow_SetCursorPosition sfWindow_SetCursorPosition;
    	pf_sfWindow_SetPosition sfWindow_SetPosition;
    	pf_sfWindow_Show sfWindow_Show;
    	pf_sfWindow_EnableKeyRepeat sfWindow_EnableKeyRepeat;
    	pf_sfWindow_SetActive sfWindow_SetActive;
    	pf_sfWindow_Display sfWindow_Display;
    	pf_sfWindow_GetInput sfWindow_GetInput;
    	pf_sfWindow_SetFramerateLimit sfWindow_SetFramerateLimit;
    	pf_sfWindow_GetFrameTime sfWindow_GetFrameTime;
    	pf_sfWindow_SetJoystickThreshold sfWindow_SetJoystickThreshold;
    }
}
else
{
    extern(C)
    {        
        ////////////////////////////////////////////////////////////
        //input.d
        /////////////////////////////////////////////////////////////
        struct sfInput {};
    
    
        int sfInput_IsKeyDown(sfInput*, KeyCode);
        int sfInput_IsMouseButtonDown(sfInput*, MouseButtons);
        int sfInput_IsJoystickButtonDown(sfInput*, uint, uint);
        uint sfInput_GetMouseX (sfInput*);
        uint sfInput_GetMouseY(sfInput*);
        float sfInput_GetJoystickAxis(sfInput*, uint, JoyAxis);    
    
    
        ////////////////////////////////////////////////////////////
        //videomode.d
        ////////////////////////////////////////////////////////////
        VideoMode sfVideoMode_GetDesktopMode();
        VideoMode sfVideoMode_GetMode(size_t);
        size_t sfVideoMode_GetModesCount();
        bool sfVideoMode_IsValid(VideoMode);
    
        ////////////////////////////////////////////////////////////
        //window.d
        ////////////////////////////////////////////////////////////
        struct sfWindow {};
    
        sfWindow* sfWindow_Create(VideoMode, char*, ulong, WindowSettings);
        sfWindow* sfWindow_CreateFromHandle(WindowHandle, WindowSettings);
        void sfWindow_Destroy(sfWindow*);
        void sfWindow_Close(sfWindow*);
        bool sfWindow_IsOpened(sfWindow*);
        uint sfWindow_GetWidth(sfWindow*);
        uint sfWindow_GetHeight(sfWindow*);
        WindowSettings sfWindow_GetSettings(sfWindow*);
        bool sfWindow_GetEvent(sfWindow*, Event*);
        void sfWindow_UseVerticalSync(sfWindow*, int);
        void sfWindow_ShowMouseCursor(sfWindow*, int);
        void sfWindow_SetCursorPosition(sfWindow*, uint, uint);
        void sfWindow_SetPosition(sfWindow*, int, int);
        void sfWindow_Show(sfWindow*, int);
        void sfWindow_EnableKeyRepeat(sfWindow*, bool);
        bool sfWindow_SetActive(sfWindow*, bool);
        void sfWindow_Display(sfWindow*);
        sfInput* sfWindow_GetInput(sfWindow*);
        void sfWindow_SetFramerateLimit(sfWindow*, uint);
        float sfWindow_GetFrameTime(sfWindow*);
        void sfWindow_SetJoystickThreshold(sfWindow*, float);
    
    }
}
