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

module dsfml.window.loader;

import dsfml.window.external;

import dsfml.system.dllloader;

version (Windows)
{
    char[] LIBNAME = "csfml-window.dll";
}
version (linux)
{
    char[] LIBNAME = "libcsfml-window.so";
}


DLLloader s_lib;

void init()
{    
    s_lib = DLLloader.load(LIBNAME);
    
    //input.d
    sfInput_IsKeyDown = cast(pf_sfInput_IsKeyDown)s_lib.getSymbol("sfInput_IsKeyDown");
    sfInput_IsMouseButtonDown = cast(pf_sfInput_IsMouseButtonDown)s_lib.getSymbol("sfInput_IsMouseButtonDown");
    sfInput_IsJoystickButtonDown = cast(pf_sfInput_IsJoystickButtonDown)s_lib.getSymbol("sfInput_IsJoystickButtonDown");
    sfInput_GetMouseX = cast(pf_sfInput_GetMouseX)s_lib.getSymbol("sfInput_GetMouseX");
    sfInput_GetMouseY = cast(pf_sfInput_GetMouseY)s_lib.getSymbol("sfInput_GetMouseY");
    sfInput_GetJoystickAxis = cast(pf_sfInput_GetJoystickAxis)s_lib.getSymbol("sfInput_GetJoystickAxis");
        
    //videomode.d
    sfVideoMode_GetDesktopMode = cast(pf_sfVideoMode_GetDesktopMode)s_lib.getSymbol("sfVideoMode_GetDesktopMode");
    sfVideoMode_GetMode = cast(pf_sfVideoMode_GetMode)s_lib.getSymbol("sfVideoMode_GetMode");
    sfVideoMode_GetModesCount = cast(pf_sfVideoMode_GetModesCount)s_lib.getSymbol("sfVideoMode_GetModesCount");
    sfVideoMode_IsValid = cast(pf_sfVideoMode_IsValid)s_lib.getSymbol("sfVideoMode_IsValid");
    
    //window.d
    sfWindow_Create = cast(pf_sfWindow_Create)s_lib.getSymbol("sfWindow_Create");
    sfWindow_CreateFromHandle = cast(pf_sfWindow_CreateFromHandle)s_lib.getSymbol("sfWindow_CreateFromHandle");
    sfWindow_Destroy = cast(pf_sfWindow_Destroy)s_lib.getSymbol("sfWindow_Destroy");
    sfWindow_Close = cast(pf_sfWindow_Close)s_lib.getSymbol("sfWindow_Close");
    sfWindow_IsOpened = cast(pf_sfWindow_IsOpened)s_lib.getSymbol("sfWindow_IsOpened");
    sfWindow_GetWidth = cast(pf_sfWindow_GetWidth)s_lib.getSymbol("sfWindow_GetWidth");
    sfWindow_GetHeight = cast(pf_sfWindow_GetHeight)s_lib.getSymbol("sfWindow_GetHeight");
    sfWindow_GetSettings = cast(pf_sfWindow_GetSettings)s_lib.getSymbol("sfWindow_GetSettings");
    sfWindow_GetEvent = cast(pf_sfWindow_GetEvent)s_lib.getSymbol("sfWindow_GetEvent");
    sfWindow_UseVerticalSync = cast(pf_sfWindow_UseVerticalSync)s_lib.getSymbol("sfWindow_UseVerticalSync");
    sfWindow_ShowMouseCursor = cast(pf_sfWindow_ShowMouseCursor)s_lib.getSymbol("sfWindow_ShowMouseCursor");
    sfWindow_SetCursorPosition = cast(pf_sfWindow_SetCursorPosition)s_lib.getSymbol("sfWindow_SetCursorPosition");
    sfWindow_SetPosition = cast(pf_sfWindow_SetPosition)s_lib.getSymbol("sfWindow_SetPosition");
    sfWindow_Show = cast(pf_sfWindow_Show)s_lib.getSymbol("sfWindow_Show");
    sfWindow_EnableKeyRepeat = cast(pf_sfWindow_EnableKeyRepeat)s_lib.getSymbol("sfWindow_EnableKeyRepeat");
    sfWindow_SetActive = cast(pf_sfWindow_SetActive)s_lib.getSymbol("sfWindow_SetActive");
    sfWindow_Display = cast(pf_sfWindow_Display)s_lib.getSymbol("sfWindow_Display");
    sfWindow_GetInput = cast(pf_sfWindow_GetInput)s_lib.getSymbol("sfWindow_GetInput");
    sfWindow_SetFramerateLimit = cast(pf_sfWindow_SetFramerateLimit)s_lib.getSymbol("sfWindow_SetFramerateLimit");
    sfWindow_GetFrameTime = cast(pf_sfWindow_GetFrameTime)s_lib.getSymbol("sfWindow_GetFrameTime");
    sfWindow_SetJoystickThreshold = cast(pf_sfWindow_SetJoystickThreshold)s_lib.getSymbol("sfWindow_SetJoystickThreshold");
}

