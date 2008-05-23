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

module dsfml.system.stringutil;

version(Tango)
{
    public import tango.stdc.stringz;
}
else
{
    public import std.string;
    
    /*
    *   Tango equivalent functions
    */    
    char[] fromStringz (char* s)
    {
        size_t i;

        if (s)
            while (*s++)
                ++i;

        return s ? s[0 .. i] : null;
    }
    
    
    wchar* toString16z (wchar[] s)
    {
            if (s.ptr)
                if (! (s.length && s[$-1] is 0))
                       s = s ~ "\0"w;
        return s.ptr;
    }
    
    
    wchar[] fromString16z (wchar* s)
    {
        size_t i;

        if (s)
            while (*s++)
                ++i;

        return s ? s[0 .. i] : null;
    }
}
