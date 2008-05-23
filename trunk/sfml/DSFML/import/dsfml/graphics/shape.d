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

module dsfml.graphics.shape;

import dsfml.system.pointerchecker;
import dsfml.system.vector2;

import dsfml.graphics.blendmode;
import dsfml.graphics.color;
import dsfml.graphics.external;
import dsfml.graphics.drawableimpl;

/**
*   Shape defines a drawable convex shape ; it also defines
*   helper functions to draw simple shapes like
*   lines, rectangles, circles, etc.
*/
class Shape : Drawableimpl!(sfShape)
{
    this()
    {
        m_drawable = sfShape_Create();
    }

    ~this()
    {
        sfShape_Destroy(m_drawable); 
    }

    /**
    *   Add a point to the shape
    *
    *   Params:
    *       x = X position of the point
    *       y = Y position of the point
    *       col = Color of the point (white by default)
    *       outlineCol = Outline color of the point (black by default)
    */        
    void addPoint(float x, float y, Color col = Color.WHITE, Color outlineCol = Color.BLACK)
    {
        sfShape_AddPoint(m_drawable, x, y, col, outlineCol);
    }
 
    /**
    *   Add a point to the shape
    *
    *   Params:
    *       position = position of the point
    *       col = Color of the point (white by default)
    *       outlineCol = Outline color of the point (black by default)
    */        
    void addPoint(Vector2f position, Color col = Color.WHITE, Color outlineCol = Color.BLACK)
    {
        sfShape_AddPoint(m_drawable, position.x, position.x, col, outlineCol);
    }
 
    /**
    *   Enable or disable filling the shape.
    *   Fill is enabled by default.
    *   
    *   Params:
    *       enable = True to enable, false to disable                
    */        
    void enableFill(bool enable)
    {
        sfShape_EnableFill(m_drawable, enable);
    }

    /**
    *   Enable or disable drawing a shape outline.
    *   Outline is enabled by default
    *
    *   Params:
    *       enable = True to enable, false to disable
    */
    void enableOutline(bool enable)
    {
        sfShape_EnableOutline(m_drawable, enable);
    }

    /**
    *   Change the width of a shape outline
    *
    *   Params: 
    *       width = New width
    */
    void setOutlineWidth(float width)
    {
        sfShape_SetOutlineWidth(m_drawable, width);
    }

    /**
    *   Get the number of points composing a shape
    *
    *   Returns:
    *       Total number of points
    */
    uint getNbPoints()
    {
        return sfShape_GetNbPoints(m_drawable);
    }

    /**
    *   Get a point of the shape
    *
    *   Params:    
    *       index = Index-th point
    */
    Vector2f getPoint(uint index)
    {
        float x, y;
        sfShape_GetPoint(m_drawable, index, &x, &y);
        return Vector2f(x, y);
    }

    /**
    *   Get the width of the shape outline
    *
    *   Returns:
    *       Current outline width
    *
    */
    float getOutlineWidth() 
    {
        return sfShape_GetOutlineWidth(m_drawable);
    }


 
    /**
    *   Create a shape made of a single line
    *
    *   Params:
    *       p1X, p1Y = Position of the first point
    *       p2X, p2Y = Position second point
    *       thickness = Line thickness
    *       col = Color used to draw the line
    *       outline = Outline width (0 by default)
    *       outlineCol = Color used to draw the outline (black by default)
    *   
    *   Returns:
    *       New line shape        
    */
    static Shape line(float p1X, float p1Y, float p2X, float p2Y, float thickness, Color col, float outline = 0.f, Color outlineCol = Color.BLACK)
    {
        
        return new Shape(sfShape_CreateLine(p1X, p1Y, p2X, p2Y, thickness, col, outline, outlineCol));
    }

    /**
    *   Create a shape made of a single rectangle
    *
    *   Params:    
    *       p1X, p1Y = Position of the first point
    *       p2X, p2Y = Position second point
    *       col = Color used to fill the rectangle
    *       outline = Outline width (0 by default)
    *       outlineCol = Color used to draw the outline (black by default)
    *       
    *   Returns:
    *       new rectangle shape            
    */
    static Shape rectangle(float p1X, float p1Y, float p2X, float p2Y, Color col, float outline = 0.f, Color outlineCol = Color.BLACK)
    {
        return new Shape(sfShape_CreateRectangle(p1X, p1Y, p2X, p2Y, col, outline, outlineCol));
    }

    /**
    *   Create a shape made of a single circle
    *
    *   Params:    
    *       x, y = Position of the center
    *       radius = Radius
    *       col = Color used to fill the circle
    *       outline = Outline width (0 by default)
    *       outlineCol = Color used to draw the outline (black by default)
    *
    *   Returns:
    *       new circle shape        
    */
    static Shape circle(float x, float y, float radius, Color col, float outline = 0.f, Color outlineCol = Color.BLACK)
    {
        return new Shape(sfShape_CreateCircle(x, y, radius, col, outline, outlineCol));
    }

package:
    sfShape* toCShape()
    {
        return m_drawable;
    }
private:
    this (sfShape* ptr)
    {
        m_drawable = ptr;
    }
    
    mixin TEnforcePointer!(m_drawable);
}
