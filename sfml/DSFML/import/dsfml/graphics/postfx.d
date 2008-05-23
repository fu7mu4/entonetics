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

module dsfml.graphics.postfx;

import dsfml.graphics.external;
import dsfml.graphics.image;

import dsfml.system.stringutil;


/**
*   PostFX is used to apply a post effect to a window
* 
*   See_Also:
*   $(LINK2 http://www.sfml-dev.org/tutorials/graphics-postfx.php, SFML post FX tutorial) from more informations about Post effects and GLSL fragment shaders syntax.
*/
class PostFX
{
    /**
    *   Default constructor
    */
    this()
	{
		m_PostFX = null;
	}

    /**
    *   Destructor
    */
    ~this()
	{
		sfPostFX_Destroy(m_PostFX);
	}

    /**
    *   Load the effect from a file
    *
    *   Params: 
    *       filename = Path of the effect file to load
    *
    *   Returns: 
    *       True on success
    */
    bool loadFromFile(char[] filename)
	{
		m_PostFX = sfPostFX_CreateFromFile(toStringz(filename));
        return (m_PostFX !is null); 
	}

    /**
    *   Load the effect from a text in memory
    *
    *   Params: 
    *       effect = String containing the effect code
    *
    *   Returns: 
    *       True on success
    */
    bool loadFromMemory(char[] effect)
	{
		m_PostFX = sfPostFX_CreateFromMemory(toStringz(effect));
		return (m_PostFX !is null); 
	}

    /**
    *   Change parameters of the effect           
    *
    *   Params:    
    *       name = Parameter name in the effect
    */
    void setParameter(char[] name, float x)
	{
		if (m_PostFX !is null)
			sfPostFX_SetParameter1(m_PostFX, toStringz(name), x);
	}

    /**
    *   ditto
    */           
    void setParameter(char[] name, float x, float y)
	{
		if (m_PostFX !is null)
			sfPostFX_SetParameter2(m_PostFX, toStringz(name), x, y);
	}

    /**
    *   ditto
    */           
    void setParameter(char[] name, float x, float y, float z)
	{
		if (m_PostFX !is null)
			sfPostFX_SetParameter3(m_PostFX, toStringz(name), x, y, z);
	}

    /**
    *   ditto
    */           
    void setParameter(char[] name, float x, float y, float z, float w)
	{
		if (m_PostFX !is null)
			sfPostFX_SetParameter4(m_PostFX, toStringz(name), x, y, z, w);
	}

    /**
    *   Set a texture parameter
    *
    *   Params: 
    *       name = Texture name in the effect
    *       texture = Image to set (pass NULL to use content of current framebuffer)
    */
    void setTexture(char[] name, Image texture)
	{
		if (m_PostFX !is null)
			sfPostFX_SetTexture(m_PostFX, toStringz(name), texture is null ? null : texture.toCImage());
	}

    /**
    *   Tell whether or not the system supports post-effects
    *
    *   Returns:
    *       True if the system can use post-effects
    */
    static bool canUsePostFX()
	{
		return sfPostFX_CanUsePostFX();
	}

package:
    sfPostFX* toCPostFX()
	{
		return m_PostFX;
	}

private:
	sfPostFX* m_PostFX;
}
