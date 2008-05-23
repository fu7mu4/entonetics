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

module dsfml.window.videomode;

import dsfml.window.external;

/**
*   VideoMode defines a video mode (width, height, bpp, frequency)
*   and provides static functions for getting modes supported
*   by the display device
*/
struct VideoMode
{
    static VideoMode opCall(uint width, uint height, uint bitsPerPixel = 32)
    {
        VideoMode mode;
        mode.Width = width;
        mode.Height = height;
        mode.BitsPerPixel = bitsPerPixel;
        return mode;
    }
    /**
    *   Get the current desktop video mode
    *
    *   Returns:
    *       Current desktop video mode
    */
    static VideoMode getDesktopMode()
    {
        return sfVideoMode_GetDesktopMode();
    }

    /**
    *   Get a valid video mode
    *   Index must be in range [0, GetModesCount()[
    *   Modes are sorted from best to worst
    *
    *   Params:
    *       index = Index of video mode to get
    *
    *   Returns:
    *       Corresponding video mode (invalid mode if index is out of range)
    */
    static VideoMode getMode(size_t index)
    {
        return sfVideoMode_GetMode(index);
    }

    /**
    *   Get valid video modes count
    *
    *   Returns:
    *       Number of valid video modes available
    */
    static size_t getModesCount()
    {
        return sfVideoMode_GetModesCount();
    }

    /**
    *   Tell whether or not the video mode is supported
    *
    *   Returns:
    *       True if video mode is supported, false otherwise
    */
    bool isValid()
    {
        return sfVideoMode_IsValid(*this);
    }

    /**
    *   Comparison operator overload -- tell if two video modes are equal
    *
    *   Params: 
    *       Other : Video mode to compare
    *
    *   Returns:
    *       True if modes are equal
    */
    bool opEquals(VideoMode other)
    {
        return ((other.Width == Width) && (other.Height == Height) && (other.BitsPerPixel == BitsPerPixel));
    }
    
    uint Width;        /// Video mode width, in pixels
    uint Height;       /// Video mode height, in pixels
    uint BitsPerPixel; /// Video mode pixel depth, in bits per pixels
}
