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

module dsfml.graphics.sprite;

import dsfml.graphics.blendmode;
import dsfml.graphics.color;
import dsfml.graphics.external;
import dsfml.graphics.drawableimpl;
import dsfml.graphics.image;
import dsfml.graphics.rect;

import dsfml.system.pointerchecker;
import dsfml.system.vector2;

/**
*   Sprite defines a sprite : texture, transformations,
*   color, and draw on screen
*   See_Also:
*       IDrawable
*/
class Sprite : Drawableimpl!(sfSprite)
{
    /**
    *   Default constructor
    */
    this()
	{
		m_drawable = sfSprite_Create();
	}

    /**
    *   Construct the sprite from a source image
    *
    *   Params: 
    *       img = Image of the sprite
    *       left = Left coordinate of the sprite (0 by default)
    *       top = Top coordinate of the sprite (0 by default)
    *       scaleX = Horizontal scale (1 by default)
    *       scaleY= Vertical scale (1 by default)
    *       rotation = Orientation, in degrees (0 by default)
    *       col = Color of the sprite (white by default)
    */
    this(Image img, float left = 0.f, float top = 0.f, float scaleX = 1.f, float scaleY = 1.f, float rotation = 0.f, Color col = Color.WHITE)
	{
        m_Image = img;
		m_drawable = sfSprite_Create();
		sfSprite_SetImage(m_drawable, img.toCImage());
		sfSprite_SetX(m_drawable, left);
		sfSprite_SetY(m_drawable, top);
		sfSprite_SetScaleX(m_drawable, scaleX);
		sfSprite_SetScaleY(m_drawable, scaleY);
		sfSprite_SetRotation(m_drawable, rotation);
		sfSprite_SetColor(m_drawable, col);
	}

	~this()
	{
		sfSprite_Destroy(m_drawable);
	}

    /**
    *   Change the image of the sprite
    *
    *   Params:
    *       img = New image
    */
    void setImage(Image img)
	{
		sfSprite_SetImage(m_drawable, img.toCImage());
		m_Image = img;
	}

    /**
    *   Set the sub-rectangle of a sprite inside the source image.
    *  
    *   Params:
    *       rect = New sub-rectangle                   
    */    
    void setSubRect(IntRect rect)
    {
        sfIntRect r = rect.toCIntRect();
        sfSprite_SetSubRect(m_drawable, &r);
        m_SubRect = rect;
    }

    /**
    *   Resize the sprite (by changing its scale factors).
    *   The default size is defined by the subrect
    *
    *   Params:    
    *       width = New width (must be strictly positive)
    *       height = New height (must be strictly positive)
    */
    void resize(float width, float height)
	{
		sfSprite_Resize(m_drawable, width, height);
	}

    /**
    *   Resize the sprite (by changing its scale factors).
    *   The default size is defined by the subrect
    *
    *   Params:    
    *       size = New size (both coordinates must be strictly positive)
    */
    void resize(Vector2f size)
	{
		sfSprite_Resize(m_drawable, size.x, size.y);
	}
 

    /**
    *   Flip the sprite horizontally
    *
    *   Params: 
    *       flipped = True to flip the sprite
    */
    void flipX(bool flipped)
	{
		sfSprite_FlipX(m_drawable, flipped);
	}

    /**
    *   Flip the sprite vertically
    *
    *   Params: 
    *       flipped = True to flip the sprite
    */
    void flipY(bool flipped)
	{
		sfSprite_FlipY(m_drawable, flipped);
	}

    /**
    *   Get the source image of the sprite
    *
    *   Returns: 
    *       Pointer to the image (can be NULL)
    */
    Image getImage()
	{
		return m_Image;
	}

    /**
    *   Get the sub-rectangle of the sprite inside the source image
    *   
    *   Returns:
    *       Sub-rectangle            
    */        
    IntRect getSubRect()
    {
        return m_SubRect;
    }

    /**
    *   Get the sprite size
    *
    *   Returns: 
    *       Size of the sprite
    */        
    Vector2f getSize()
    {
        return Vector2f(sfSprite_GetWidth(m_drawable), sfSprite_GetHeight(m_drawable));
    }

    /**
    *   Get the color of a given pixel in the sprite
    *   
    *   Params:
    *       x = X coordinate 
    *       y = Y coordinate
    *   
    *   Returns:
    *       Color of pixel             
    */
    Color getPixel(uint x, uint y)
    {
        return sfSprite_GetPixel(m_drawable, x, y);
    }

package:
	sfSprite* toCSprite()
	{
		return m_drawable;
	}

private:
    Image m_Image;      //< Image used to draw the sprite
    IntRect m_SubRect;    //< Sub-rectangle of source image to assign to the sprite
    
    mixin TEnforcePointer!(m_drawable);
}

