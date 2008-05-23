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

module dsfml.graphics.image;

import dsfml.graphics.color;
import dsfml.graphics.external;

import dsfml.system.pointerchecker;
import dsfml.system.stringutil;


/**
*   Image is the low-level class for loading and
*   manipulating images
*/
class Image
{
    /**
    *   Default constructor
    */
    this()
	{
		m_Image = sfImage_Create();
	}

    /**
    *   Construct an empty image
    *
    *   Params:    
    *       width = Image width
    *       height = Image height
    *       col = Image color (black by default)
    */
    this(uint width, uint height, Color col = Color.BLACK)
	{
		m_Image = sfImage_CreateFromColor(width, height, col);
	}

    /**
    *   Construct the image from pixels in memory
    *   
    *   Params:
    *       width = Image width
    *       height = Image height
    *       data = Pointer to the pixels in memory (assumed format is RGBA)
    */
    this(uint width, uint height, ubyte* data)
	{
		m_Image = sfImage_CreateFromPixels(width, height, data);
	}

    /**
    * Destructor
    */
    ~this()
	{
		sfImage_Destroy(m_Image);
	}

    /**
    *   Load the surface from a file
    *
    *   Params: 
    *       filename = Path of the image file to load
    *
    *   Returns: 
    *       True if loading was successful
    */
    bool loadFromFile(char[] filename)
	{
		m_Image = sfImage_CreateFromFile(toStringz(filename));
		return (m_Image !is null); 
	}

    /**
    *   Load the surface from a file in memory
    *
    *   Params:
    *       data = Pointer to the file data in memory
    *       sizeInBytes = Size of the data to load, in bytes
    *
    *   Returns: 
    *       True if loading was successful
    */
    bool loadFromMemory(byte* data, size_t sizeInBytes)
	{
		m_Image = sfImage_CreateFromMemory(data, sizeInBytes);
		return (m_Image !is null); 
	}

    /**
    *   Load the image directly from an array of pixels
    *
    *   Params: 
    *       width = Image width
    *       height = Image height
    *       data = Pointer to the pixels in memory (assumed format is RGBA)
    *
    *   Returns:
    *      True if loading was successful
    */
    bool loadFromPixels(uint width, uint height, ubyte* data)
	{
		m_Image = sfImage_CreateFromPixels(width, height, data);
		return (m_Image !is null); 
	}

    /**
    *   Save the content of the image to a file
    *
    *   Params: 
    *       filename = Path of the file to save (overwritten if already exist)
    *
    *   Returns: 
    *       True if saving was successful
    */
    bool saveToFile(char[] filename)
	{
		return sfImage_SaveToFile(m_Image, toStringz(filename));
	}

    /**
    *   Create an empty image
    *   
    *   Params:    
    *       width = Image width
    *       height = Image height
    *       col = Image color (black by default)
    *
    *   Returns: 
    *       True if creation was successful
    */
    bool create(uint width, uint height, Color col = Color.BLACK)
	{
		m_Image = sfImage_CreateFromColor(width, height, col);
		return (m_Image !is null); 
	}

    /**
    *   Create transparency mask from a specified colorkey
    *
    *   Params: 
    *       colorKey = Color to become transparent
    *       alpha = Alpha value to use for transparent pixels (0 by default)
    */
    void createMaskFromColor(Color colorKey, ubyte alpha = 0)
	{
		sfImage_CreateMaskFromColor(m_Image, colorKey, alpha);
	}

    /**
    *   Resize the image - warning : this function does not scale the image,
    *   it just ajdusts size (add padding or remove pixels)
    *   
    *   Params:    
    *       width = New width
    *       height = New height
    *       col = Color to assign to new pixels (black by default)
    *
    *   Returns: 
    *       True if resize has been successful
    */
    bool resize(uint width, uint height, Color col = Color.BLACK)
	{
		return sfImage_Resize(m_Image, width, height, col);
	}

    /**
    *   Change the color of a pixel
    *   Don't forget to call Update when you end modifying pixels
    *   
    *   Params:    
    *       x = X coordinate of pixel in the image
    *       y = Y coordinate of pixel in the image
    *       col = New color for pixel (X, Y)
    */
    void setPixel(uint x, uint y, Color col)
	{
		sfImage_SetPixel(m_Image, x, y, col);
	}

    /**
    *   Get a pixel from the image
    *
    *   Params:    
    *       x = X coordinate of pixel in the image
    *       y = Y coordinate of pixel in the image
    *
    *   Returns: 
    *       Color of pixel (x, y)
    */
    Color getPixel(uint x, uint y)
	{
		return sfImage_GetPixel(m_Image, x, y);
	}

    /**
    *   Get a pointer to the array of pixels (8 bits integers RGBA)
    *   Array size is GetWidth() x GetHeight() x 4
    *   This pointer becomes invalid if you reload or resize the image
    *
    *   Returns:
    *       pointer to the array of pixels
    */
    ubyte* getPixelsPtr()
	{
		return sfImage_GetPixelsPtr(m_Image);
	}

    /**
    *   Bind the image for rendering
    */
    void bind()
	{
		sfImage_Bind(m_Image);
	}

    /**
    *   Enable or disable image smooth filter.
    *   This parameter is enabled by default
    *
    *   Params: 
    *       smooth = True to enable smoothing filter, false to disable it
    */
    void setSmooth(bool smooth)
	{
		sfImage_SetSmooth(m_Image, smooth);
	}

    /**
    *   Return the width of the image
    *
    *   Returns: 
    *       Width in pixels
    */
    uint getWidth()
	{
		return sfImage_GetWidth(m_Image);
	}

    /**
    *   Return the height of the image
    *
    *   Returns: 
    *       Height in pixels
    */
    uint getHeight()
	{
		return sfImage_GetHeight(m_Image);
	}
    
    /**
    *   Tells whether the smooth filtering is enabled or not
    *
    *   Returns:
    *       True if image smoothing is enabled
    */
    bool isSmooth()
    {
        return sfImage_IsSmooth(m_Image);
    }
    
    

    this(sfImage* psfImage)
	{
		m_Image = psfImage;
	}


	sfImage* toCImage()
	{
		return m_Image;
	}

private:
	sfImage *m_Image;
	mixin TEnforcePointer!(m_Image);
}
