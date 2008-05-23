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

module dsfml.graphics.loader;

import dsfml.graphics.external;

import dsfml.system.dllloader;

version (Windows)
{
    const char[] LIBNAME = "csfml-graphics.dll";
}
version (linux)
{
    const char[] LIBNAME = "libcsfml-graphics.so.1";
}

DLLloader s_lib;

void init()
{
    s_lib = DLLloader.load(LIBNAME);
    
    //image.d
    sfImage_Create = cast(pf_sfImage_Create)s_lib.getSymbol("sfImage_Create");
    sfImage_CreateFromColor = cast(pf_sfImage_CreateFromColor)s_lib.getSymbol("sfImage_CreateFromColor");
    sfImage_CreateFromPixels = cast(pf_sfImage_CreateFromPixels)s_lib.getSymbol("sfImage_CreateFromPixels");
    sfImage_CreateFromFile = cast(pf_sfImage_CreateFromFile)s_lib.getSymbol("sfImage_CreateFromFile");
    sfImage_CreateFromMemory = cast(pf_sfImage_CreateFromMemory)s_lib.getSymbol("sfImage_CreateFromMemory");
    sfImage_Destroy = cast(pf_sfImage_Destroy)s_lib.getSymbol("sfImage_Destroy");
    sfImage_SaveToFile = cast(pf_sfImage_SaveToFile)s_lib.getSymbol("sfImage_SaveToFile");
    sfImage_CreateMaskFromColor = cast(pf_sfImage_CreateMaskFromColor)s_lib.getSymbol("sfImage_CreateMaskFromColor");
    sfImage_Resize = cast(pf_sfImage_Resize)s_lib.getSymbol("sfImage_Resize");
    sfImage_SetPixel = cast(pf_sfImage_SetPixel)s_lib.getSymbol("sfImage_SetPixel");
    sfImage_GetPixel = cast(pf_sfImage_GetPixel)s_lib.getSymbol("sfImage_GetPixel");
    sfImage_GetPixelsPtr = cast(pf_sfImage_GetPixelsPtr)s_lib.getSymbol("sfImage_GetPixelsPtr");
    sfImage_Bind = cast(pf_sfImage_Bind)s_lib.getSymbol("sfImage_Bind");
    sfImage_SetSmooth = cast(pf_sfImage_SetSmooth)s_lib.getSymbol("sfImage_SetSmooth");
    sfImage_GetWidth = cast(pf_sfImage_GetWidth)s_lib.getSymbol("sfImage_GetWidth");
    sfImage_GetHeight = cast(pf_sfImage_GetHeight)s_lib.getSymbol("sfImage_GetHeight");
    sfImage_IsSmooth = cast(pf_sfImage_IsSmooth)s_lib.getSymbol("sfImage_IsSmooth");
    
    //psotFX.d
    sfPostFX_CreateFromFile = cast(pf_sfPostFX_CreateFromFile)s_lib.getSymbol("sfPostFX_CreateFromFile");
    sfPostFX_CreateFromMemory = cast(pf_sfPostFX_CreateFromMemory)s_lib.getSymbol("sfPostFX_CreateFromMemory");
    sfPostFX_Destroy = cast(pf_sfPostFX_Destroy)s_lib.getSymbol("sfPostFX_Destroy");
    sfPostFX_SetParameter1 = cast(pf_sfPostFX_SetParameter1)s_lib.getSymbol("sfPostFX_SetParameter1");
    sfPostFX_SetParameter2 = cast(pf_sfPostFX_SetParameter2)s_lib.getSymbol("sfPostFX_SetParameter2");
    sfPostFX_SetParameter3 = cast(pf_sfPostFX_SetParameter3)s_lib.getSymbol("sfPostFX_SetParameter3");
    sfPostFX_SetParameter4 = cast(pf_sfPostFX_SetParameter4)s_lib.getSymbol("sfPostFX_SetParameter4");
    sfPostFX_SetTexture = cast(pf_sfPostFX_SetTexture)s_lib.getSymbol("sfPostFX_SetTexture");
    sfPostFX_CanUsePostFX = cast(pf_sfPostFX_CanUsePostFX)s_lib.getSymbol("sfPostFX_CanUsePostFX");
    
    
    //renderwindow.d
    sfRenderWindow_Create = cast(pf_sfRenderWindow_Create)s_lib.getSymbol("sfRenderWindow_Create");
    sfRenderWindow_CreateFromHandle = cast(pf_sfRenderWindow_CreateFromHandle)s_lib.getSymbol("sfRenderWindow_CreateFromHandle");
    sfRenderWindow_Destroy = cast(pf_sfRenderWindow_Destroy)s_lib.getSymbol("sfRenderWindow_Destroy");
    sfRenderWindow_GetInput = cast(pf_sfRenderWindow_GetInput)s_lib.getSymbol("sfRenderWindow_GetInput");
    sfRenderWindow_DrawPostFX = cast(pf_sfRenderWindow_DrawPostFX)s_lib.getSymbol("sfRenderWindow_DrawPostFX");
    sfRenderWindow_DrawSprite = cast(pf_sfRenderWindow_DrawSprite)s_lib.getSymbol("sfRenderWindow_DrawSprite");
    sfRenderWindow_DrawString = cast(pf_sfRenderWindow_DrawString)s_lib.getSymbol("sfRenderWindow_DrawString");
    sfRenderWindow_DrawShape = cast(pf_sfRenderWindow_DrawShape)s_lib.getSymbol("sfRenderWindow_DrawShape");
    sfRenderWindow_Capture = cast(pf_sfRenderWindow_Capture)s_lib.getSymbol("sfRenderWindow_Capture");
    sfRenderWindow_SetBackgroundColor = cast(pf_sfRenderWindow_SetBackgroundColor)s_lib.getSymbol("sfRenderWindow_SetBackgroundColor");
    sfRenderWindow_SetView = cast(pf_sfRenderWindow_SetView)s_lib.getSymbol("sfRenderWindow_SetView");
    sfRenderWindow_GetView = cast(pf_sfRenderWindow_GetView)s_lib.getSymbol("sfRenderWindow_GetView");
    sfRenderWindow_ConvertCoords = cast(pf_sfRenderWindow_ConvertCoords)s_lib.getSymbol("sfRenderWindow_ConvertCoords");
    sfRenderWindow_PreserveOpenGLStates = cast(pf_sfRenderWindow_PreserveOpenGLStates)s_lib.getSymbol("sfRenderWindow_PreserveOpenGLStates");
    
    
    //sprite.d
    sfSprite_Create = cast(pf_sfSprite_Create)s_lib.getSymbol("sfSprite_Create");
    sfSprite_Destroy = cast(pf_sfSprite_Destroy)s_lib.getSymbol("sfSprite_Destroy");
    sfSprite_SetX = cast(pf_sfSprite_SetX)s_lib.getSymbol("sfSprite_SetX");
    sfSprite_SetY = cast(pf_sfSprite_SetY)s_lib.getSymbol("sfSprite_SetY");
    sfSprite_SetPosition = cast(pf_sfSprite_SetPosition)s_lib.getSymbol("sfSprite_SetPosition");
    sfSprite_SetScaleX = cast(pf_sfSprite_SetScaleX)s_lib.getSymbol("sfSprite_SetScaleX");
    sfSprite_SetScaleY = cast(pf_sfSprite_SetScaleY)s_lib.getSymbol("sfSprite_SetScaleY");
    sfSprite_SetScale = cast(pf_sfSprite_SetScale)s_lib.getSymbol("sfSprite_SetScale");
    sfSprite_SetRotation = cast(pf_sfSprite_SetRotation)s_lib.getSymbol("sfSprite_SetRotation");
    sfSprite_SetCenter = cast(pf_sfSprite_SetCenter)s_lib.getSymbol("sfSprite_SetCenter");
    sfSprite_SetColor = cast(pf_sfSprite_SetColor)s_lib.getSymbol("sfSprite_SetColor");
    sfSprite_SetBlendMode = cast(pf_sfSprite_SetBlendMode)s_lib.getSymbol("sfSprite_SetBlendMode");
    sfSprite_GetX = cast(pf_sfSprite_GetX)s_lib.getSymbol("sfSprite_GetX");
    sfSprite_GetY = cast(pf_sfSprite_GetY)s_lib.getSymbol("sfSprite_GetY");
    sfSprite_GetScaleX = cast(pf_sfSprite_GetScaleX)s_lib.getSymbol("sfSprite_GetScaleX");
    sfSprite_GetScaleY = cast(pf_sfSprite_GetScaleY)s_lib.getSymbol("sfSprite_GetScaleY");
    sfSprite_GetRotation = cast(pf_sfSprite_GetRotation)s_lib.getSymbol("sfSprite_GetRotation");
    sfSprite_GetCenterX = cast(pf_sfSprite_GetCenterX)s_lib.getSymbol("sfSprite_GetCenterX");
    sfSprite_GetCenterY = cast(pf_sfSprite_GetCenterY)s_lib.getSymbol("sfSprite_GetCenterY");
    sfSprite_GetColor = cast(pf_sfSprite_GetColor)s_lib.getSymbol("sfSprite_GetColor");
    sfSprite_GetBlendMode = cast(pf_sfSprite_GetBlendMode)s_lib.getSymbol("sfSprite_GetBlendMode");
    sfSprite_Move = cast(pf_sfSprite_Move)s_lib.getSymbol("sfSprite_Move");
    sfSprite_Scale = cast(pf_sfSprite_Scale)s_lib.getSymbol("sfSprite_Scale");
    sfSprite_Rotate = cast(pf_sfSprite_Rotate)s_lib.getSymbol("sfSprite_Rotate");
    sfSprite_SetImage = cast(pf_sfSprite_SetImage)s_lib.getSymbol("sfSprite_SetImage");
    sfSprite_SetSubRect = cast(pf_sfSprite_SetSubRect)s_lib.getSymbol("sfSprite_SetSubRect");
    sfSprite_Resize = cast(pf_sfSprite_Resize)s_lib.getSymbol("sfSprite_Resize");
    sfSprite_FlipX = cast(pf_sfSprite_FlipX)s_lib.getSymbol("sfSprite_FlipX");
    sfSprite_FlipY = cast(pf_sfSprite_FlipY)s_lib.getSymbol("sfSprite_FlipY");
    sfSprite_GetImage = cast(pf_sfSprite_GetImage)s_lib.getSymbol("sfSprite_GetImage");
    sfSprite_GetSubRect = cast(pf_sfSprite_GetSubRect)s_lib.getSymbol("sfSprite_GetSubRect");
    sfSprite_GetWidth = cast(pf_sfSprite_GetWidth)s_lib.getSymbol("sfSprite_GetWidth");
    sfSprite_GetHeight = cast(pf_sfSprite_GetHeight)s_lib.getSymbol("sfSprite_GetHeight");
    sfSprite_GetPixel = cast(pf_sfSprite_GetPixel)s_lib.getSymbol("sfSprite_GetPixel");
    
    
    //string.d
    sfString_Create = cast(pf_sfString_Create)s_lib.getSymbol("sfString_Create");
    sfString_Destroy = cast(pf_sfString_Destroy)s_lib.getSymbol("sfString_Destroy");
    sfString_SetX = cast(pf_sfString_SetX)s_lib.getSymbol("sfString_SetX");
    sfString_SetY = cast(pf_sfString_SetY)s_lib.getSymbol("sfString_SetY");
    sfString_SetPosition = cast(pf_sfString_SetPosition)s_lib.getSymbol("sfString_SetPosition");
    sfString_SetScaleX = cast(pf_sfString_SetScaleX)s_lib.getSymbol("sfString_SetScaleX");
    sfString_SetScaleY = cast(pf_sfString_SetScaleY)s_lib.getSymbol("sfString_SetScaleY");
    sfString_SetScale = cast(pf_sfString_SetScale)s_lib.getSymbol("sfString_SetScale");
    sfString_SetRotation = cast(pf_sfString_SetRotation)s_lib.getSymbol("sfString_SetRotation");
    sfString_SetCenter = cast(pf_sfString_SetCenter)s_lib.getSymbol("sfString_SetCenter");
    sfString_SetColor = cast(pf_sfString_SetColor)s_lib.getSymbol("sfString_SetColor");
    sfString_SetBlendMode = cast(pf_sfString_SetBlendMode)s_lib.getSymbol("sfString_SetBlendMode");
    sfString_GetX = cast(pf_sfString_GetX)s_lib.getSymbol("sfString_GetX");
    sfString_GetY = cast(pf_sfString_GetY)s_lib.getSymbol("sfString_GetY");
    sfString_GetScaleX = cast(pf_sfString_GetScaleX)s_lib.getSymbol("sfString_GetScaleX");
    sfString_GetScaleY = cast(pf_sfString_GetScaleY)s_lib.getSymbol("sfString_GetScaleY");
    sfString_GetRotation = cast(pf_sfString_GetRotation)s_lib.getSymbol("sfString_GetRotation");
    sfString_GetCenterX = cast(pf_sfString_GetCenterX)s_lib.getSymbol("sfString_GetCenterX");
    sfString_GetCenterY = cast(pf_sfString_GetCenterY)s_lib.getSymbol("sfString_GetCenterY");
    sfString_GetColor = cast(pf_sfString_GetColor)s_lib.getSymbol("sfString_GetColor");
    sfString_GetBlendMode = cast(pf_sfString_GetBlendMode)s_lib.getSymbol("sfString_GetBlendMode");
    sfString_Move = cast(pf_sfString_Move)s_lib.getSymbol("sfString_Move");
    sfString_Scale = cast(pf_sfString_Scale)s_lib.getSymbol("sfString_Scale");
    sfString_Rotate = cast(pf_sfString_Rotate)s_lib.getSymbol("sfString_Rotate");
    sfString_SetText = cast(pf_sfString_SetText)s_lib.getSymbol("sfString_SetText");
    sfString_SetUnicodeText = cast(pf_sfString_SetUnicodeText)s_lib.getSymbol("sfString_SetUnicodeText");
    sfString_SetFont = cast(pf_sfString_SetFont)s_lib.getSymbol("sfString_SetFont");
    sfString_SetSize = cast(pf_sfString_SetSize)s_lib.getSymbol("sfString_SetSize");
    sfString_SetStyle = cast(pf_sfString_SetStyle)s_lib.getSymbol("sfString_SetStyle");
    sfString_GetUnicodeText = cast(pf_sfString_GetUnicodeText)s_lib.getSymbol("sfString_GetUnicodeText");
    sfString_GetText = cast(pf_sfString_GetText)s_lib.getSymbol("sfString_GetText");
    sfString_GetFont = cast(pf_sfString_GetFont)s_lib.getSymbol("sfString_GetFont");
    sfString_GetSize = cast(pf_sfString_GetSize)s_lib.getSymbol("sfString_GetSize");
    sfString_GetStyle = cast(pf_sfString_GetStyle)s_lib.getSymbol("sfString_GetStyle");
    sfString_GetRect = cast(pf_sfString_GetRect)s_lib.getSymbol("sfString_GetRect");
    
    //shape.d
    sfShape_Create = cast(pf_sfShape_Create)s_lib.getSymbol("sfShape_Create");
    sfShape_CreateLine = cast(pf_sfShape_CreateLine)s_lib.getSymbol("sfShape_CreateLine");
    sfShape_CreateRectangle = cast(pf_sfShape_CreateRectangle)s_lib.getSymbol("sfShape_CreateRectangle");
    sfShape_CreateCircle = cast(pf_sfShape_CreateCircle)s_lib.getSymbol("sfShape_CreateCircle");
    sfShape_Destroy = cast(pf_sfShape_Destroy)s_lib.getSymbol("sfShape_Destroy");
    sfShape_SetX = cast(pf_sfShape_SetX)s_lib.getSymbol("sfShape_SetX");
    sfShape_SetY = cast(pf_sfShape_SetY)s_lib.getSymbol("sfShape_SetY");
    sfShape_SetPosition = cast(pf_sfShape_SetPosition)s_lib.getSymbol("sfShape_SetPosition");
    sfShape_SetScaleX = cast(pf_sfShape_SetScaleX)s_lib.getSymbol("sfShape_SetScaleX");
    sfShape_SetScaleY = cast(pf_sfShape_SetScaleY)s_lib.getSymbol("sfShape_SetScaleY");
    sfShape_SetScale = cast(pf_sfShape_SetScale)s_lib.getSymbol("sfShape_SetScale");
    sfShape_SetRotation = cast(pf_sfShape_SetRotation)s_lib.getSymbol("sfShape_SetRotation");
    sfShape_SetCenter = cast(pf_sfShape_SetCenter)s_lib.getSymbol("sfShape_SetCenter");
    sfShape_SetColor = cast(pf_sfShape_SetColor)s_lib.getSymbol("sfShape_SetColor");
    sfShape_SetBlendMode = cast(pf_sfShape_SetBlendMode)s_lib.getSymbol("sfShape_SetBlendMode");
    sfShape_GetX = cast(pf_sfShape_GetX)s_lib.getSymbol("sfShape_GetX");
    sfShape_GetY = cast(pf_sfShape_GetY)s_lib.getSymbol("sfShape_GetY");
    sfShape_GetScaleX = cast(pf_sfShape_GetScaleX)s_lib.getSymbol("sfShape_GetScaleX");
    sfShape_GetScaleY = cast(pf_sfShape_GetScaleY)s_lib.getSymbol("sfShape_GetScaleX");
    sfShape_GetRotation = cast(pf_sfShape_GetRotation)s_lib.getSymbol("sfShape_GetRotation");
    sfShape_GetCenterX = cast(pf_sfShape_GetCenterX)s_lib.getSymbol("sfShape_GetCenterX");
    sfShape_GetCenterY = cast(pf_sfShape_GetCenterY)s_lib.getSymbol("sfShape_GetCenterY");
    sfShape_GetColor = cast(pf_sfShape_GetColor)s_lib.getSymbol("sfShape_GetColor");
    sfShape_GetBlendMode = cast(pf_sfShape_GetBlendMode)s_lib.getSymbol("sfShape_GetBlendMode");
    sfShape_Move = cast(pf_sfShape_Move)s_lib.getSymbol("sfShape_Move");
    sfShape_Scale = cast(pf_sfShape_Scale)s_lib.getSymbol("sfShape_Scale");
    sfShape_Rotate = cast(pf_sfShape_Rotate)s_lib.getSymbol("sfShape_Rotate");
    sfShape_AddPoint = cast(pf_sfShape_AddPoint)s_lib.getSymbol("sfShape_AddPoint");
    sfShape_EnableFill = cast(pf_sfShape_EnableFill)s_lib.getSymbol("sfShape_EnableFill");
    sfShape_EnableOutline = cast(pf_sfShape_EnableOutline)s_lib.getSymbol("sfShape_EnableOutline");
    sfShape_SetOutlineWidth = cast(pf_sfShape_SetOutlineWidth)s_lib.getSymbol("sfShape_SetOutlineWidth");
    sfShape_GetNbPoints = cast(pf_sfShape_GetNbPoints)s_lib.getSymbol("sfShape_GetNbPoints");
    sfShape_GetPoint = cast(pf_sfShape_GetPoint)s_lib.getSymbol("sfShape_GetPoint");
    sfShape_GetOutlineWidth = cast(pf_sfShape_GetOutlineWidth)s_lib.getSymbol("sfShape_GetOutlineWidth");

    
    //font.d
    sfFont_Create = cast(pf_sfFont_Create) s_lib.getSymbol("sfFont_Create");
    sfFont_CreateFromFile = cast(pf_sfFont_CreateFromFile) s_lib.getSymbol("sfFont_CreateFromFile");
    sfFont_CreateFromMemory = cast(pf_sfFont_CreateFromMemory) s_lib.getSymbol("sfFont_CreateFromMemory");
    sfFont_Destroy = cast(pf_sfFont_Destroy) s_lib.getSymbol("sfFont_Destroy");
    sfFont_GetDefaultFont = cast(pf_sfFont_GetDefaultFont) s_lib.getSymbol("sfFont_GetDefaultFont");

    //view.d
    sfView_Create = cast(pf_sfView_Create) s_lib.getSymbol("sfView_Create");
    sfView_CreateFromRect = cast(pf_sfView_CreateFromRect) s_lib.getSymbol("sfView_CreateFromRect");
    sfView_Destroy = cast(pf_sfView_Destroy) s_lib.getSymbol("sfView_Destroy");
    sfView_SetCenter = cast(pf_sfView_SetCenter) s_lib.getSymbol("sfView_SetCenter");
    sfView_SetHalfSize = cast(pf_sfView_SetHalfSize) s_lib.getSymbol("sfView_SetHalfSize");
    sfView_SetFromRect = cast(pf_sfView_SetFromRect) s_lib.getSymbol("sfView_SetFromRect");
    sfView_GetCenterX = cast(pf_sfView_GetCenterX) s_lib.getSymbol("sfView_GetCenterX");
    sfView_GetCenterY = cast(pf_sfView_GetCenterY) s_lib.getSymbol("sfView_GetCenterY");
    sfView_GetHalfSizeX = cast(pf_sfView_GetHalfSizeX) s_lib.getSymbol("sfView_GetHalfSizeX");
    sfView_GetHalfSizeY = cast(pf_sfView_GetHalfSizeY) s_lib.getSymbol("sfView_GetHalfSizeY");
    sfView_GetRect = cast(pf_sfView_GetRect) s_lib.getSymbol("sfView_GetRect");
    sfView_Move = cast(pf_sfView_Move) s_lib.getSymbol("sfView_Move");
    sfView_Zoom = cast(pf_sfView_Zoom) s_lib.getSymbol("sfView_Zoom");
    
}



