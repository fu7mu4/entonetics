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

module dsfml.graphics.font;

import dsfml.graphics.external;

import dsfml.system.stringutil;
import dsfml.system.pointerchecker;

/**
*   Font is the low-level class for loading and
*   manipulating character fonts.
*/
class Font
{
    /**
    *   Get SFML default built-in font (Arial)
    */        
    static Font getDefaultFont()
    {
        if (s_default is null)
            s_default = new Font(sfFont_GetDefaultFont());           
        return s_default;
    }

    /**
    *   Constructor
    */        
    this()
    {
        m_font = sfFont_Create();
    }
    
    ~this()
    {
        sfFont_Destroy(m_font);
    }

    /**
    *   Load the Font from a file
    *   
    *   Params:
    *       filename = font file to load
    *       charSize = size of characters (30 by default)
    *       charset = characters set to generate (empty by default - takes the ASCII range [31, 255])
    *       
    *   Returns:
    *       true if loading was successful                              
    */        
    bool loadFromFile(char[] filename, uint charSize = 30, wchar[] charset = ""w)
    {
        m_font = sfFont_CreateFromFile(toStringz(filename), charSize, toString16z(charset));
        return (m_font !is null);
    }
    
    /**
    *   Load the Font from a file
    *   
    *   Params:
    *       data = pointer to data to load
    *       sizeInBytes = size of the data to load    
    *       charSize = size of characters (30 by default)
    *       charset = characters set to generate (empty by default - takes the ASCII range [31, 255])
    *       
    *   Returns:
    *       true if loading was successful                              
    */            
    bool loadFromMemory(byte* data, size_t sizeInBytes, uint charSize = 30, wchar[] charset = ""w)
    {
        m_font = sfFont_CreateFromMemory(data, sizeInBytes, charSize, toString16z(charset));
        return (m_font !is null);
    }

    sfFont* toCFont()
    {
        return m_font;
    }

    this(sfFont* cFont)
    {
        m_font = cFont;
    }

private:

    sfFont* m_font;
    static Font s_default;
    
     mixin TEnforcePointer!(m_font);
} 
