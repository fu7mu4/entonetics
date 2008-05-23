////////////////////////////////////////////////////////////
//
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007 Laurent Gomila (laurent.gom@gmail.com)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics/Font.h>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Internal.h>


struct sfFont
{
    sf::Font This;
};


////////////////////////////////////////////////////////////
/// Create a new empty font
////////////////////////////////////////////////////////////
sfFont* sfFont_Create()
{
    return new sfFont;
}


////////////////////////////////////////////////////////////
/// Create a new font from a file
////////////////////////////////////////////////////////////
sfFont* sfFont_CreateFromFile(const char* Filename, unsigned int CharSize, const wchar_t* Charset)
{
    sfFont* Font = new sfFont;

    if (!Font->This.LoadFromFile(Filename, CharSize, Charset))
    {
        delete Font;
        Font = NULL;
    }

    return Font;
}


////////////////////////////////////////////////////////////
/// Create a new font from a file in memory
////////////////////////////////////////////////////////////
sfFont* sfFont_CreateFromMemory(const char* Data, size_t SizeInBytes, unsigned int CharSize, const wchar_t* Charset)
{
    sfFont* Font = new sfFont;

    if (!Font->This.LoadFromMemory(Data, SizeInBytes, CharSize, Charset))
    {
        delete Font;
        Font = NULL;
    }

    return Font;
}


////////////////////////////////////////////////////////////
/// Destroy an existing font
////////////////////////////////////////////////////////////
void sfFont_Destroy(sfFont* Font)
{
    delete Font;
}


////////////////////////////////////////////////////////////
/// Get the built-in default font (Arial)
////////////////////////////////////////////////////////////
sfFont* sfFont_GetDefaultFont()
{
    static sfFont DefaultFont = {sf::Font::GetDefaultFont()};

    return &DefaultFont;
}
