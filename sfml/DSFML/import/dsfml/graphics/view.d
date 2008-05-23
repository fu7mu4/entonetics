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

module dsfml.graphics.view;

import dsfml.graphics.external;
import dsfml.graphics.rect;

import dsfml.system.vector2;

/**
*   This class defines a view (position, size and zoom) ;
*   you can consider it as a camera
*/
class View
{
    /**
    *   Constructor
    *   
    *   Default view (1000 x 1000)        
    */
    this()
    {
        m_view = sfView_Create();
    }
     
   /**
   *   Constructor
   *   
   *    Params:
   *        center = center of the view
   *        hlafsize = Half-size of the view (from center to corner)            
   */       	   
	this(Vector2f center, Vector2f halfsize)
	{
		m_view = sfView_CreateFromRect(sfFloatRect(center.x - halfsize.x, center.y - halfsize.y, center.x + halfsize.x, center.y + halfsize.y) );
	}
    
    /**
    *   Constructor
    *   
    *   Params:
    *       rect = Rectangle defining the position and size of the view                 
    */        
    this(FloatRect rect)
    {
        sfView_CreateFromRect(rect.toCFloatRect());
    }

    ~this()
    {
        sfView_Destroy(m_view);
    }
    
    /**
    *   Change the center of the view
    *   
    *   Params:
    *       x = X coordinates of the new center
    *       y = Y coordinates of the new center                     
    */        
    void setCenter(float x, float y)
    {
        sfView_SetCenter(m_view, x, y);
        m_isModified = true;
    }

    /**
    *   Change the center of the view
    *   
    *   Params:
    *       center = New center                     
    */        
    void setCenter(Vector2f center)
    {
        sfView_SetCenter(m_view, center.x, center.y);
        m_isModified = true;
    }

    /**
    *   Change the half-size of the view (take 2 values)
    *
    *   Params:
    *       halfWidth = New half-width
    *       halfHeight = New half-height
    */
    void setHalfSize(float halfWidth, float HalfHeight)
    {
        sfView_SetHalfSize(m_view, halfWidth, HalfHeight);
        m_isModified = true;
    }

    /**
    *   Change the half-size of the view (take 2 values)
    *
    *   Params:
    *       helfSize = New halfsize
    */
    void setHalfSize(Vector2f halfSize)
    {
        sfView_SetHalfSize(m_view, halfSize.x, halfSize.y);
        m_isModified = true;
    }

    /**
    * Rebuild the view from a rectangle
    *
    * Params:
    *     viewRect : Rectangle defining the position and size of the view
    */
    void setFromRect(FloatRect viewRect)
    {
        sfView_SetFromRect(m_view, viewRect.toCFloatRect());
        m_rect = viewRect;
    }

    /**
    *   Get the center of the view
    *
    *   Returns: 
    *       Center of the view
    */
    Vector2f GetCenter()
    {
        return Vector2f(sfView_GetCenterX(m_view), sfView_GetCenterY(m_view));
    }

    /**
    *   Get the halfsize of the view
    *
    *   Returns: 
    *       Halfsize of the view
    */
    Vector2f GetHalfSize()
    {
        return Vector2f(sfView_GetHalfSizeX(m_view), sfView_GetHalfSizeY(m_view));
    }

    /**
    *   Get the bounding retangle of the view
    */       	   
    FloatRect getRect()
    {
        if (m_isModified)
        {
            m_isModified = false;
            sfFloatRect cRect = sfView_GetRect(m_view);
            m_rect = new FloatRect(cRect.Left, cRect.Top, cRect.Right, cRect.Bottom);
        }
        return m_rect;
    }
    
    /**
    *   Move the view 
    *
    *   Params:
    *       offsetX = Offset to move the view, on X axis
    *       offsetY = Offset to move the view, on Y axis
    */
    void move(float offsetX, float offsetY)
    {
        sfView_Move(m_view, offsetX, offsetY);
    }

    /**
    *   Move the view 
    *
    *   Params:
    *       offset = offsetto move the view
    */
    void move(Vector2f offset)
    {
        sfView_Move(m_view, offset.x, offset.y);
    }

    void zoom(float factor)
    {
        sfView_Zoom(m_view, factor);
    }
    
    sfView* toCView()
    {
        return m_view;
    }

    this(sfView* view)
    {
        m_view = view;
    } 

private:
    sfView* m_view;
    FloatRect m_rect;
    bool m_isModified = true;
}


