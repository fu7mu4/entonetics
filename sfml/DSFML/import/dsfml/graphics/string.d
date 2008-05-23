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

module dsfml.graphics.string;

import dsfml.graphics.blendmode;
import dsfml.graphics.color;
import dsfml.graphics.external;
import dsfml.graphics.font;
import dsfml.graphics.textstyle;
import dsfml.graphics.drawableimpl;
import dsfml.graphics.rect;

import dsfml.system.pointerchecker;
import dsfml.system.stringutil;
import dsfml.system.vector2;


/**
*   String defines a graphical 2D text, that can be drawn on screen
*   
*   All string litterals used must be prefixed with d for multibyte 
*   and w for unicode 16 string.
*    
*   Examples :
*   ---------------------------------------------------------------
*   String s = new String("Hello"c, "arial.ttf", 36.f);
*   //this(char[], char[], float)
*   s = new String("Hello"w, "arial.ttf", 36.f);
*   //this(wchar[], char[], float)
*   ---------------------------------------------------------------
*   
*   See_Also:
*       IDrawable
*/
class String : Drawableimpl!(sfString)
{
    /**
    *   Construct the string from a text
    *   
    *   Prefixs string litterals with c        
    *
    *   Params:    
    *       text = Text assigned to the string ("" by default)
    *       font = Font used to draw the string (use default font)
    *       size = Characters size, in pixels (32 by default)
    */
    this(char[] text, Font font = Font.getDefaultFont(), float size = 30.f)
	{
		m_drawable = sfString_Create();
		sfString_SetFont(m_drawable, font.toCFont());
		sfString_SetText(m_drawable, toStringz(text));
		sfString_SetSize(m_drawable, size);
	}

    /**
    *   Construct the string from a unicode text
    *   
    *   Prefixs string litterals with w  
    *           
    *   Params:    
    *       text = Text assigned to the string ("" by default)
    *       font = Font used to draw the string (use default font)
    *       size = Characters size, in pixels (32 by default)
    */
    this(wchar[] text, Font font = Font.getDefaultFont(), float size = 30.f)
	{
		m_drawable = sfString_Create();
		sfString_SetFont(m_drawable, font.toCFont());
		sfString_SetUnicodeText(m_drawable, toString16z(text));
		sfString_SetSize(m_drawable, size);
	}

    /**
    *   Set the text (from a multibyte string)
    *
    *   Params: 
    *       text = New text
    *
    */
    void setText(char[] text)
	{
		sfString_SetText(m_drawable,toStringz(text));
	}

    /**
    *   Set the text (from a unicode string)
    *
    *   Params:     
    *       text = New text
    */
    void setText(wchar[] text)
	{
		sfString_SetUnicodeText(m_drawable, toString16z(text));
	}

    /**
    *   Set the font of the string
    *
    *   Params:    
    *       font = Font filename
    */
    void setFont(Font font)
	{
		sfString_SetFont(m_drawable, font.toCFont());
	}

    /**
    *   Set the size of the string
    *
    *   Params:    
    *       size = New size, in pixels
    */
    void setSize(float size)
	{
		sfString_SetSize(m_drawable, size);
	}

    /**
    *   Set the style of the text
    *   The default style is Regular
    *
    *   Params:
    *       TextStyle = New text style, (combination of Style enum values)
    *
    */
    void setStyle(TextStyle style)
    {
        sfString_SetStyle(m_drawable, style);
    }        

    /**
    *   Get the text (returns a unicode string)
    *
    *   Returns: 
    *       Text
    */
    wchar[] getUnicodeText()
	{
		return fromString16z(sfString_GetUnicodeText(m_drawable));
	}

    /**
    *   Get the text (returns a multibyte string)
    *
    *   Returns: 
    *       Text
    */
    char[] getText()
	{
		return fromStringz(sfString_GetText(m_drawable));
	}

    /**
    *   Get the font used by the string
    *
    *   Returns: 
    *       Font name
    */
    Font getFont()
	{
		return new Font(sfString_GetFont(m_drawable));
	}

    /**
    *   Get the size of the characters
    *
    *   Returns: 
    *       Size of the characters
    */
    float getSize()
	{
		return sfString_GetSize(m_drawable);
	}

    /**
    *   Get the current font style
    *   
    *   Returns:
    *       Font style            
    */
    TextStyle getStyle()
    {
        return sfString_GetStyle(m_drawable);
    }
            
    /**
    *   Get the string rectangle on screen
    *
    *   Returns: 
    *       Rectangle contaning the string in screen coordinates
    */
    FloatRect getRect()
	{
		sfFloatRect sfRect = sfString_GetRect(m_drawable);
		
		return new Rect!(float)(sfRect.Left, sfRect.Top, sfRect.Right, sfRect.Bottom);
	}

package:
    sfString* toCString()
   	{
		return m_drawable;
	}

private:
 	mixin TEnforcePointer!(m_drawable);
}
