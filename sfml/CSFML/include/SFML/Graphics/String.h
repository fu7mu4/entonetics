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

#ifndef SFML_STRING_H
#define SFML_STRING_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Config.h>
#include <SFML/Graphics/BlendMode.h>
#include <SFML/Graphics/Color.h>
#include <SFML/Graphics/Font.h>
#include <SFML/Graphics/Rect.h>


////////////////////////////////////////////////////////////
/// sfString defines a graphical 2D text, that can be drawn on screen
////////////////////////////////////////////////////////////
typedef struct sfString sfString;


////////////////////////////////////////////////////////////
/// sfString styles
////////////////////////////////////////////////////////////
typedef enum
{
    sfStringRegular    = 0,      ///< Regular characters, no style
    sfStringBold       = 1 << 0, ///< Characters are bold
    sfStringItalic     = 1 << 1, ///< Characters are in italic
    sfStringUnderlined = 1 << 2  ///< Characters are underlined
} sfStringStyle;


////////////////////////////////////////////////////////////
/// Create a new string
///
/// \return A new sfString object, or NULL if it failed
///
////////////////////////////////////////////////////////////
CSFML_API sfString* sfString_Create();

////////////////////////////////////////////////////////////
/// Destroy an existing string
///
/// \param String : String to delete
///
////////////////////////////////////////////////////////////
CSFML_API void sfString_Destroy(sfString* String);

////////////////////////////////////////////////////////////
/// Set the X position of a string
///
/// \param String : String to modify
/// \param X :      New X coordinate
///
////////////////////////////////////////////////////////////
CSFML_API void sfString_SetX(sfString* String, float X);

////////////////////////////////////////////////////////////
/// Set the Y position of a string
///
/// \param String : String to modify
/// \param Y :      New Y coordinate
///
////////////////////////////////////////////////////////////
CSFML_API void sfString_SetY(sfString* String, float Y);

////////////////////////////////////////////////////////////
/// Set the position of a string
///
/// \param String : String to modify
/// \param Left :   New left coordinate
/// \param Top :    New top coordinate
///
////////////////////////////////////////////////////////////
CSFML_API void sfString_SetPosition(sfString* String, float Left, float Top);

////////////////////////////////////////////////////////////
/// Set the horizontal scale of a string
///
/// \param String : String to modify
/// \param Scale :  New scale (must be strictly positive)
///
////////////////////////////////////////////////////////////
CSFML_API void sfString_SetScaleX(sfString* String, float Scale);

////////////////////////////////////////////////////////////
/// Set the vertical scale of a string
///
/// \param String : String to modify
/// \param Scale :  New scale (must be strictly positive)
///
////////////////////////////////////////////////////////////
CSFML_API void sfString_SetScaleY(sfString* String, float Scale);

////////////////////////////////////////////////////////////
/// Set the scale of a string
///
/// \param String : String to modify
/// \param ScaleX : New horizontal scale (must be strictly positive)
/// \param ScaleY : New vertical scale (must be strictly positive)
///
////////////////////////////////////////////////////////////
CSFML_API void sfString_SetScale(sfString* String, float ScaleX, float ScaleY);

////////////////////////////////////////////////////////////
/// Set the orientation of a string
///
/// \param String :   String to modify
/// \param Rotation : Angle of rotation, in degrees
///
////////////////////////////////////////////////////////////
CSFML_API void sfString_SetRotation(sfString* String, float Rotation);

////////////////////////////////////////////////////////////
/// Set the center of a string, in coordinates
/// relative to its left-top corner
///
/// \param String : String to modify
/// \param X :      X coordinate of the center
/// \param Y :      Y coordinate of the center
///
////////////////////////////////////////////////////////////
CSFML_API void sfString_SetCenter(sfString* String, float X, float Y);

////////////////////////////////////////////////////////////
/// Set the color of a string
///
/// \param String : String to modify
/// \param Color :  New color
///
////////////////////////////////////////////////////////////
CSFML_API void sfString_SetColor(sfString* String, sfColor Color);

////////////////////////////////////////////////////////////
/// Set the blending mode for a string
///
/// \param String : String to modify
/// \param Mode :   New blending mode
///
////////////////////////////////////////////////////////////
CSFML_API void sfString_SetBlendMode(sfString* String, sfBlendMode Mode);

////////////////////////////////////////////////////////////
/// Get the X position of a string
///
/// \param String : String to read
///
/// \return Current X position
///
////////////////////////////////////////////////////////////
CSFML_API float sfString_GetX(sfString* String);

////////////////////////////////////////////////////////////
/// Get the top Y of a string
///
/// \param String : String to read
///
/// \return Current Y position
///
////////////////////////////////////////////////////////////
CSFML_API float sfString_GetY(sfString* String);

////////////////////////////////////////////////////////////
/// Get the horizontal scale of a string
///
/// \param String : String to read
///
/// \return Current X scale factor (always positive)
///
////////////////////////////////////////////////////////////
CSFML_API float sfString_GetScaleX(sfString* String);

////////////////////////////////////////////////////////////
/// Get the vertical scale of a string
///
/// \param String : String to read
///
/// \return Current Y scale factor (always positive)
///
////////////////////////////////////////////////////////////
CSFML_API float sfString_GetScaleY(sfString* String);

////////////////////////////////////////////////////////////
/// Get the orientation of a string
///
/// \param String : String to read
///
/// \return Current rotation, in degrees
///
////////////////////////////////////////////////////////////
CSFML_API float sfString_GetRotation(sfString* String);

////////////////////////////////////////////////////////////
/// Get the X position of the center a string
///
/// \param String : String to read
///
/// \return Current X center position
///
////////////////////////////////////////////////////////////
CSFML_API float sfString_GetCenterX(sfString* String);

////////////////////////////////////////////////////////////
/// Get the top Y of the center of a string
///
/// \param String : String to read
///
/// \return Current Y center position
///
////////////////////////////////////////////////////////////
CSFML_API float sfString_GetCenterY(sfString* String);

////////////////////////////////////////////////////////////
/// Get the color of a string
///
/// \param String : String to read
///
/// \return Current color
///
////////////////////////////////////////////////////////////
CSFML_API sfColor sfString_GetColor(sfString* String);

////////////////////////////////////////////////////////////
/// Get the current blending mode of a string
///
/// \param String : String to read
///
/// \return Current blending mode
///
////////////////////////////////////////////////////////////
CSFML_API sfBlendMode sfString_GetBlendMode(sfString* String);

////////////////////////////////////////////////////////////
/// Move a string
///
/// \param String :  String to modify
/// \param OffsetX : Offset on the X axis
/// \param OffsetY : Offset on the Y axis
///
////////////////////////////////////////////////////////////
CSFML_API void sfString_Move(sfString* String, float OffsetX, float OffsetY);

////////////////////////////////////////////////////////////
/// Scale a string
///
/// \param String :  String to modify
/// \param FactorX : Horizontal scaling factor (must be strictly positive)
/// \param FactorY : Vertical scaling factor (must be strictly positive)
///
////////////////////////////////////////////////////////////
CSFML_API void sfString_Scale(sfString* String, float FactorX, float FactorY);

////////////////////////////////////////////////////////////
/// Rotate a string
///
/// \param String : String to modify
/// \param Angle :  Angle of rotation, in degrees
///
////////////////////////////////////////////////////////////
CSFML_API void sfString_Rotate(sfString* String, float Angle);

////////////////////////////////////////////////////////////
/// Set the text of a string (from a multibyte string)
///
/// \param String : String to modify
/// \param Text :   New text
///
////////////////////////////////////////////////////////////
CSFML_API void sfString_SetText(sfString* String, const char* Text);

////////////////////////////////////////////////////////////
/// Set the text of a string (from a unicode string)
///
/// \param String : String to modify
/// \param Text :   New text
///
////////////////////////////////////////////////////////////
CSFML_API void sfString_SetUnicodeText(sfString* String, const wchar_t* Text);

////////////////////////////////////////////////////////////
/// Set the font of a string
///
/// \param String : String to modify
/// \param Font :   Font to use
///
////////////////////////////////////////////////////////////
CSFML_API void sfString_SetFont(sfString* String, sfFont* Font);

////////////////////////////////////////////////////////////
/// Set the size of a string
///
/// \param String : String to modify
/// \param Size :   New size, in pixels
///
////////////////////////////////////////////////////////////
CSFML_API void sfString_SetSize(sfString* String, float Size);

////////////////////////////////////////////////////////////
/// Set the style of a string
///
/// \param String : String to modify
/// \param Size :   New style (see sfStringStyle enum)
///
////////////////////////////////////////////////////////////
CSFML_API void sfString_SetStyle(sfString* String, unsigned long Style);

////////////////////////////////////////////////////////////
/// Get the text of a string (returns a unicode string)
///
/// \param String : String to read
///
/// \return Text
///
////////////////////////////////////////////////////////////
CSFML_API const wchar_t* sfString_GetUnicodeText(sfString* String);

////////////////////////////////////////////////////////////
/// Get the text of a string (returns a multibyte string)
///
/// \param String : String to read
///
/// \return Text
///
////////////////////////////////////////////////////////////
CSFML_API const char* sfString_GetText(sfString* String);

////////////////////////////////////////////////////////////
/// Get the font used by a string
///
/// \param String : String to read
///
/// \return Pointer to the font
///
////////////////////////////////////////////////////////////
CSFML_API sfFont* sfString_GetFont(sfString* String);

////////////////////////////////////////////////////////////
/// Get the size of the characters of a string
///
/// \param String : String to read
///
/// \return Size of the characters
///
////////////////////////////////////////////////////////////
CSFML_API float sfString_GetSize(sfString* String);

////////////////////////////////////////////////////////////
/// Get the style of a string
///
/// \param String : String to read
///
/// \return Current string style (see sfStringStyle enum)
///
////////////////////////////////////////////////////////////
CSFML_API unsigned long sfString_GetStyle(sfString* String);

////////////////////////////////////////////////////////////
/// Get the bounding rectangle of a string on screen
///
/// \param String : String to read
///
/// \return Rectangle contaning the string in screen coordinates
///
////////////////////////////////////////////////////////////
CSFML_API sfFloatRect* sfString_GetRect(sfString* String);


#endif // SFML_STRING_H
