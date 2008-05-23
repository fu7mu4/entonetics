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

module dsfml.graphics.drawableimpl;

import dsfml.system.vector2;

import dsfml.graphics.idrawable;
import dsfml.graphics.color;
import dsfml.graphics.external;
import dsfml.graphics.blendmode;

/*
*   Package base class of all drawable.
*   Provide implementation of IDrawable and functions aliases. 
*/
package class Drawableimpl(T) : IDrawable
{
    static if (is (T : sfShape))
    {
        alias sfShape sfDrawable;
        
        alias sfShape_SetX sfDrawable_SetX;
        alias sfShape_SetY sfDrawable_SetY;
        alias sfShape_SetPosition sfDrawable_SetPosition;
        alias sfShape_SetScaleX sfDrawable_SetScaleX;
        alias sfShape_SetScaleY sfDrawable_SetScaleY;
        alias sfShape_SetScale sfDrawable_SetScale;
        alias sfShape_SetRotation sfDrawable_SetRotation;
        alias sfShape_SetCenter sfDrawable_SetCenter;
        alias sfShape_SetColor sfDrawable_SetColor;
        alias sfShape_SetBlendMode sfDrawable_SetBlendMode;
        alias sfShape_GetX sfDrawable_GetX;
        alias sfShape_GetY sfDrawable_GetY;
        alias sfShape_GetScaleX sfDrawable_GetScaleX;
        alias sfShape_GetScaleY sfDrawable_GetScaleY;
        alias sfShape_GetRotation sfDrawable_GetRotation;
        alias sfShape_GetCenterX sfDrawable_GetCenterX;
        alias sfShape_GetCenterY sfDrawable_GetCenterY;
        alias sfShape_GetColor sfDrawable_GetColor;
        alias sfShape_GetBlendMode sfDrawable_GetBlendMode;
        alias sfShape_Move sfDrawable_Move;
        alias sfShape_Scale sfDrawable_Scale;
        alias sfShape_Rotate sfDrawable_Rotate;
    }
    else static if (is (T : sfString))
    {
        alias sfString sfDrawable;
        
        alias sfString_SetX sfDrawable_SetX;
        alias sfString_SetY sfDrawable_SetY;
        alias sfString_SetPosition sfDrawable_SetPosition;
        alias sfString_SetScaleX sfDrawable_SetScaleX;
        alias sfString_SetScaleY sfDrawable_SetScaleY;
        alias sfString_SetScale sfDrawable_SetScale;
        alias sfString_SetRotation sfDrawable_SetRotation;
        alias sfString_SetCenter sfDrawable_SetCenter;
        alias sfString_SetColor sfDrawable_SetColor;
        alias sfString_SetBlendMode sfDrawable_SetBlendMode;
        alias sfString_GetX sfDrawable_GetX;
        alias sfString_GetY sfDrawable_GetY;
        alias sfString_GetScaleX sfDrawable_GetScaleX;
        alias sfString_GetScaleY sfDrawable_GetScaleY;
        alias sfString_GetRotation sfDrawable_GetRotation;
        alias sfString_GetCenterX sfDrawable_GetCenterX;
        alias sfString_GetCenterY sfDrawable_GetCenterY;
        alias sfString_GetColor sfDrawable_GetColor;
        alias sfString_GetBlendMode sfDrawable_GetBlendMode;
        alias sfString_Move sfDrawable_Move;
        alias sfString_Scale sfDrawable_Scale;
        alias sfString_Rotate sfDrawable_Rotate;
    }
    else static if (is (T : sfSprite))
    {
        alias sfSprite sfDrawable;
        
        alias sfSprite_SetX sfDrawable_SetX;
        alias sfSprite_SetY sfDrawable_SetY;
        alias sfSprite_SetPosition sfDrawable_SetPosition;
        alias sfSprite_SetScaleX sfDrawable_SetScaleX;
        alias sfSprite_SetScaleY sfDrawable_SetScaleY;
        alias sfSprite_SetScale sfDrawable_SetScale;
        alias sfSprite_SetRotation sfDrawable_SetRotation;
        alias sfSprite_SetCenter sfDrawable_SetCenter;
        alias sfSprite_SetColor sfDrawable_SetColor;
        alias sfSprite_SetBlendMode sfDrawable_SetBlendMode;
        alias sfSprite_GetX sfDrawable_GetX;
        alias sfSprite_GetY sfDrawable_GetY;
        alias sfSprite_GetScaleX sfDrawable_GetScaleX;
        alias sfSprite_GetScaleY sfDrawable_GetScaleY;
        alias sfSprite_GetRotation sfDrawable_GetRotation;
        alias sfSprite_GetCenterX sfDrawable_GetCenterX;
        alias sfSprite_GetCenterY sfDrawable_GetCenterY;
        alias sfSprite_GetColor sfDrawable_GetColor;
        alias sfSprite_GetBlendMode sfDrawable_GetBlendMode;
        alias sfSprite_Move sfDrawable_Move;
        alias sfSprite_Scale sfDrawable_Scale;
        alias sfSprite_Rotate sfDrawable_Rotate;
    }

    void setX(float x)
    {
        sfDrawable_SetX(m_drawable, x);
    }

    void setY(float y)
    {
        sfDrawable_SetY(m_drawable, y);
    }

    void setPosition(float x, float y)
    {
        sfDrawable_SetPosition(m_drawable, x, y);
    }

    void setPosition(Vector2f vec)
    {
        sfDrawable_SetPosition(m_drawable, vec.x, vec.y);
    }

    void setScaleX(float scale)
    in
    {
        assert (scale > 0, "Scale factor must be strictly positive.");
    }
    body
    {
        sfDrawable_SetScaleX(m_drawable, scale);
    }
    
    void setScaleY(float scale)
    in
    {
        assert (scale > 0, "Scale factor must be strictly positive.");
    }
    body
    {
        sfDrawable_SetScaleY(m_drawable, scale);
    }

    void setScale(float scaleX, float scaleY)
    in
    {
        assert (scaleX > 0 && scaleY > 0, "Scale factor must be strictly positive.");
    }
    body
    {
        sfDrawable_SetScale(m_drawable, scaleX, scaleY);
    }

    void setScale(Vector2f scale)
    in
    {
        assert (scale.x > 0 && scale.y > 0, "Scale factor must be strictly positive.");
    }
    body
    {
        sfDrawable_SetScale(m_drawable, scale.x, scale.y);
    }

    void setCenter(float centerX, float centerY)
    {
        sfDrawable_SetCenter(m_drawable, centerX, centerY);
    }

    void setCenter(Vector2f center)
    {
        sfDrawable_SetCenter(m_drawable, center.x, center.y);
    }

    void setRotation(float angle)
    {
        sfDrawable_SetRotation(m_drawable, angle);
    }

    void setColor(Color c)
    {
        sfDrawable_SetColor(m_drawable, c);
    }
            
    void setBlendMode(BlendMode mode)
	{
		sfDrawable_SetBlendMode(m_drawable, mode);
	}

    Vector2f getPosition()
    {
        return Vector2f(sfDrawable_GetX(m_drawable), sfDrawable_GetY(m_drawable));
    }

    Vector2f getScale()
    {
        return Vector2f(sfDrawable_GetScaleX(m_drawable), sfDrawable_GetScaleY(m_drawable));
    }

    Vector2f getCenter()
    {
        return Vector2f(sfDrawable_GetCenterX(m_drawable),  sfDrawable_GetCenterY(m_drawable));
    }
    
    float getRotation()
    {
        return sfDrawable_GetRotation(m_drawable);
    }

    Color getColor()
    {
        return sfDrawable_GetColor(m_drawable);
    }

    BlendMode getBlendMode()
	{
		return cast(BlendMode)(sfDrawable_GetBlendMode(m_drawable));
	}

    void rotate(float angle)
    {
        sfDrawable_Rotate(m_drawable, angle);
    }

    void move(float offsetX, float offsetY)
    {
        sfDrawable_Move(m_drawable, offsetX, offsetY);
    }

    void move(Vector2f offset)
    {
        sfDrawable_Move(m_drawable, offset.x, offset.y);
    }

    void scale(float scaleX, float scaleY)
    in
    {
        assert(scaleX > 0 && scaleY > 0, "Scale factor must be strictly positive.");
    }
    body
    {
        sfDrawable_SetScale(m_drawable, scaleX, scaleY);
    }

    void scale(Vector2f scale)
    in
    {
        assert(scale.x > 0 && scale.y > 0, "Scale factor must be strictly positive.");
    }
    body
    {
        sfDrawable_SetScale(m_drawable, scale.x, scale.y);
    }


protected:
    sfDrawable* m_drawable;
}
