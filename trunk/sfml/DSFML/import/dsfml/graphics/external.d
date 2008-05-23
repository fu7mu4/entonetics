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

module dsfml.graphics.external;

import dsfml.window.event;
import dsfml.window.external;
import dsfml.window.videomode;
import dsfml.window.windowhandle;
import dsfml.window.windowsettings;

import dsfml.graphics.blendmode;
import dsfml.graphics.color;
import dsfml.graphics.textstyle;



struct sfFloatRect
{
    float Left;
    float Top;
    float Right;
    float Bottom;
}

struct sfIntRect
{
    int Left;
    int Top;
    int Right;
    int Bottom;
}


version(Dynamic)
{
    extern (C)
    {
        ////////////////////////////////////////////////////////////
        //image.d
        ////////////////////////////////////////////////////////////
        
        
        ////////////////////////////////////////////////////////////
        /// sfImage is the low-level class for loading and
        /// manipulating images
        ////////////////////////////////////////////////////////////
        struct sfImage {};
    
    
    	typedef sfImage* function() pf_sfImage_Create;
    	typedef sfImage* function(uint, uint, Color) pf_sfImage_CreateFromColor;
    	typedef sfImage* function(uint, uint, ubyte*) pf_sfImage_CreateFromPixels;
    	typedef sfImage* function(char*) pf_sfImage_CreateFromFile;
    	typedef sfImage* function(byte* ,size_t) pf_sfImage_CreateFromMemory;
    	typedef void function(sfImage*) pf_sfImage_Destroy;
    	typedef bool function(sfImage*, char*) pf_sfImage_SaveToFile;
    	typedef void function(sfImage*, Color, ubyte) pf_sfImage_CreateMaskFromColor;
    	typedef bool function(sfImage*, uint, uint, Color) pf_sfImage_Resize;
    	typedef void function(sfImage*, uint, uint, Color) pf_sfImage_SetPixel;
    	typedef Color function(sfImage*, uint, uint) pf_sfImage_GetPixel;
    	typedef ubyte* function(sfImage*) pf_sfImage_GetPixelsPtr;
    	typedef void function(sfImage*) pf_sfImage_Bind;
    	typedef void function(sfImage*, int) pf_sfImage_SetSmooth;
    	typedef uint function(sfImage*) pf_sfImage_GetWidth;
    	typedef uint function(sfImage*) pf_sfImage_GetHeight;
    	typedef bool function(sfImage*) pf_sfImage_IsSmooth;
    
    	pf_sfImage_Create sfImage_Create;
    	pf_sfImage_CreateFromColor sfImage_CreateFromColor;
    	pf_sfImage_CreateFromPixels sfImage_CreateFromPixels;
    	pf_sfImage_CreateFromFile sfImage_CreateFromFile;
    	pf_sfImage_CreateFromMemory sfImage_CreateFromMemory;
    	pf_sfImage_Destroy sfImage_Destroy;
    	pf_sfImage_SaveToFile sfImage_SaveToFile;
    	pf_sfImage_CreateMaskFromColor sfImage_CreateMaskFromColor;
    	pf_sfImage_Resize sfImage_Resize;
    	pf_sfImage_SetPixel sfImage_SetPixel;
    	pf_sfImage_GetPixel sfImage_GetPixel;
    	pf_sfImage_GetPixelsPtr sfImage_GetPixelsPtr;
    	pf_sfImage_Bind sfImage_Bind;
    	pf_sfImage_SetSmooth sfImage_SetSmooth;
    	pf_sfImage_GetWidth sfImage_GetWidth;
    	pf_sfImage_GetHeight sfImage_GetHeight;
    	pf_sfImage_IsSmooth sfImage_IsSmooth;
    
        ////////////////////////////////////////////////////////////
        //postfx.d
        ////////////////////////////////////////////////////////////
        
        struct sfPostFX {};
    
    
    	typedef sfPostFX* function(char*) pf_sfPostFX_CreateFromFile;
    	typedef sfPostFX* function(char*) pf_sfPostFX_CreateFromMemory;
    	typedef void function(sfPostFX*) pf_sfPostFX_Destroy;
    	typedef void function(sfPostFX*, char*, float) pf_sfPostFX_SetParameter1;
    	typedef void function(sfPostFX*, char*, float, float) pf_sfPostFX_SetParameter2;
    	typedef void function(sfPostFX*, char*, float, float, float) pf_sfPostFX_SetParameter3;
    	typedef void function(sfPostFX*, char*, float, float, float, float) pf_sfPostFX_SetParameter4;
    	typedef void function(sfPostFX*, char*, sfImage*) pf_sfPostFX_SetTexture;
    	typedef bool function() pf_sfPostFX_CanUsePostFX;
    
    	pf_sfPostFX_CreateFromFile sfPostFX_CreateFromFile;
    	pf_sfPostFX_CreateFromMemory sfPostFX_CreateFromMemory;
    	pf_sfPostFX_Destroy sfPostFX_Destroy;
    	pf_sfPostFX_SetParameter1 sfPostFX_SetParameter1;
    	pf_sfPostFX_SetParameter2 sfPostFX_SetParameter2;
    	pf_sfPostFX_SetParameter3 sfPostFX_SetParameter3;
    	pf_sfPostFX_SetParameter4 sfPostFX_SetParameter4;
    	pf_sfPostFX_SetTexture sfPostFX_SetTexture;
    	pf_sfPostFX_CanUsePostFX sfPostFX_CanUsePostFX;
    
    
    
    
    
        ////////////////////////////////////////////////////////////
        /// sfRenderWindow is a simple wrapper for sfWindow that
        /// allows easy 2D rendering
        ////////////////////////////////////////////////////////////
        struct sfRenderWindow {};
    
    
    	typedef sfRenderWindow* function(VideoMode, char*, ulong, WindowSettings) pf_sfRenderWindow_Create;
    	typedef sfRenderWindow* function(WindowHandle, WindowSettings) pf_sfRenderWindow_CreateFromHandle;
    	typedef void function(sfRenderWindow*) pf_sfRenderWindow_Destroy;
    	typedef sfInput* function(sfRenderWindow*) pf_sfRenderWindow_GetInput;
    	typedef void function(sfRenderWindow*, sfPostFX*) pf_sfRenderWindow_DrawPostFX;
    	typedef void function(sfRenderWindow*, sfSprite*) pf_sfRenderWindow_DrawSprite;
    	typedef void function(sfRenderWindow*, sfString*) pf_sfRenderWindow_DrawString;
    	typedef void function(sfRenderWindow*, sfShape*) pf_sfRenderWindow_DrawShape;
    	typedef sfImage* function(sfRenderWindow*) pf_sfRenderWindow_Capture;
    	typedef void function(sfRenderWindow*, Color) pf_sfRenderWindow_SetBackgroundColor;
    	typedef void function(sfRenderWindow*, sfView*) pf_sfRenderWindow_SetView;
    	typedef sfView* function(sfRenderWindow*) pf_sfRenderWindow_GetView;
    	typedef sfView* function (sfRenderWindow*) pf_sfRenderWindow_GetDefaultView;
    	typedef void function(sfRenderWindow*, uint, uint, float*, float*, sfView*) pf_sfRenderWindow_ConvertCoords;
    	typedef void function(sfRenderWindow*, bool) pf_sfRenderWindow_PreserveOpenGLStates;
    
    	pf_sfRenderWindow_Create sfRenderWindow_Create;
    	pf_sfRenderWindow_CreateFromHandle sfRenderWindow_CreateFromHandle;
    	pf_sfRenderWindow_Destroy sfRenderWindow_Destroy;
    	pf_sfRenderWindow_GetInput sfRenderWindow_GetInput;
    	pf_sfRenderWindow_DrawPostFX sfRenderWindow_DrawPostFX;
    	pf_sfRenderWindow_DrawSprite sfRenderWindow_DrawSprite;
    	pf_sfRenderWindow_DrawString sfRenderWindow_DrawString;
    	pf_sfRenderWindow_DrawShape sfRenderWindow_DrawShape;
    	pf_sfRenderWindow_Capture sfRenderWindow_Capture;
    	pf_sfRenderWindow_SetBackgroundColor sfRenderWindow_SetBackgroundColor;
    	pf_sfRenderWindow_SetView sfRenderWindow_SetView;
    	pf_sfRenderWindow_GetView sfRenderWindow_GetView;
    	pf_sfRenderWindow_GetDefaultView sfRenderWindow_GetDefaultView;
    	pf_sfRenderWindow_ConvertCoords sfRenderWindow_ConvertCoords;
    	pf_sfRenderWindow_PreserveOpenGLStates sfRenderWindow_PreserveOpenGLStates;
    
    
    
    
        ////////////////////////////////////////////////////////////
        /// sfSprite defines a sprite : texture, transformations,
        /// color, and draw on screen
        ////////////////////////////////////////////////////////////
        struct sfSprite {};
        
    	typedef sfSprite* function() pf_sfSprite_Create;
    	typedef void function(sfSprite*) pf_sfSprite_Destroy;
    	typedef void function(sfSprite*, float) pf_sfSprite_SetX;
    	typedef void function(sfSprite*, float) pf_sfSprite_SetY;
    	typedef void function(sfSprite*, float, float) pf_sfSprite_SetPosition;
    	typedef void function(sfSprite*, float) pf_sfSprite_SetScaleX;
    	typedef void function(sfSprite*, float) pf_sfSprite_SetScaleY;
    	typedef void function(sfSprite*, float, float) pf_sfSprite_SetScale;
    	typedef void function(sfSprite*, float) pf_sfSprite_SetRotation;
    	typedef void function(sfSprite*, float, float) pf_sfSprite_SetCenter;
    	typedef void function(sfSprite*, Color) pf_sfSprite_SetColor;
    	typedef void function(sfSprite*, BlendMode) pf_sfSprite_SetBlendMode;
    	typedef float function(sfSprite*) pf_sfSprite_GetX;
    	typedef float function(sfSprite*) pf_sfSprite_GetY;
    	typedef float function(sfSprite*) pf_sfSprite_GetScaleX;
    	typedef float function(sfSprite*) pf_sfSprite_GetScaleY;
    	typedef float function(sfSprite*) pf_sfSprite_GetRotation;
    	typedef float function(sfSprite*) pf_sfSprite_GetCenterX;
    	typedef float function(sfSprite*) pf_sfSprite_GetCenterY;
    	typedef Color function(sfSprite*) pf_sfSprite_GetColor;
    	typedef BlendMode function(sfSprite*) pf_sfSprite_GetBlendMode;
    	typedef void function(sfSprite*, float, float) pf_sfSprite_Move;
    	typedef void function(sfSprite*, float, float) pf_sfSprite_Scale;
    	typedef void function(sfSprite*, float) pf_sfSprite_Rotate;
    	typedef void function(sfSprite*, sfImage*) pf_sfSprite_SetImage;
    	typedef void function(sfSprite*, sfIntRect*) pf_sfSprite_SetSubRect;
    	typedef void function(sfSprite*, float, float) pf_sfSprite_Resize;
    	typedef void function(sfSprite*, int) pf_sfSprite_FlipX;
    	typedef void function(sfSprite*, int) pf_sfSprite_FlipY;
    	typedef sfImage* function(sfSprite*) pf_sfSprite_GetImage;
    	typedef sfIntRect* function(sfSprite*) pf_sfSprite_GetSubRect;
    	typedef float function(sfSprite*) pf_sfSprite_GetWidth;
    	typedef float function(sfSprite*) pf_sfSprite_GetHeight;
    	typedef Color function(sfSprite*, uint, uint) pf_sfSprite_GetPixel;
    
    	pf_sfSprite_Create sfSprite_Create;
    	pf_sfSprite_Destroy sfSprite_Destroy;
    	pf_sfSprite_SetX sfSprite_SetX;
    	pf_sfSprite_SetY sfSprite_SetY;
    	pf_sfSprite_SetPosition sfSprite_SetPosition;
    	pf_sfSprite_SetScaleX sfSprite_SetScaleX;
    	pf_sfSprite_SetScaleY sfSprite_SetScaleY;
    	pf_sfSprite_SetScale sfSprite_SetScale;
    	pf_sfSprite_SetRotation sfSprite_SetRotation;
    	pf_sfSprite_SetCenter sfSprite_SetCenter;
    	pf_sfSprite_SetColor sfSprite_SetColor;
    	pf_sfSprite_SetBlendMode sfSprite_SetBlendMode;
    	pf_sfSprite_GetX sfSprite_GetX;
    	pf_sfSprite_GetY sfSprite_GetY;
    	pf_sfSprite_GetScaleX sfSprite_GetScaleX;
    	pf_sfSprite_GetScaleY sfSprite_GetScaleY;
    	pf_sfSprite_GetRotation sfSprite_GetRotation;
    	pf_sfSprite_GetCenterX sfSprite_GetCenterX;
    	pf_sfSprite_GetCenterY sfSprite_GetCenterY;
    	pf_sfSprite_GetColor sfSprite_GetColor;
    	pf_sfSprite_GetBlendMode sfSprite_GetBlendMode;
    	pf_sfSprite_Move sfSprite_Move;
    	pf_sfSprite_Scale sfSprite_Scale;
    	pf_sfSprite_Rotate sfSprite_Rotate;
    	pf_sfSprite_SetImage sfSprite_SetImage;
    	pf_sfSprite_SetSubRect sfSprite_SetSubRect;
    	pf_sfSprite_Resize sfSprite_Resize;
    	pf_sfSprite_FlipX sfSprite_FlipX;
    	pf_sfSprite_FlipY sfSprite_FlipY;
    	pf_sfSprite_GetImage sfSprite_GetImage;
    	pf_sfSprite_GetSubRect sfSprite_GetSubRect;
    	pf_sfSprite_GetWidth sfSprite_GetWidth;
    	pf_sfSprite_GetHeight sfSprite_GetHeight;
    	pf_sfSprite_GetPixel sfSprite_GetPixel;
    
    
    
        ////////////////////////////////////////////////////////////
        /// sfSprite defines a sprite : texture, transformations,
        /// color, and draw on screen
        ////////////////////////////////////////////////////////////
        struct sfString {};
        
    
    	typedef sfString* function() pf_sfString_Create;
    	typedef void function(sfString*) pf_sfString_Destroy;
    	typedef void function(sfString*, float) pf_sfString_SetX;
    	typedef void function(sfString*, float) pf_sfString_SetY;
    	typedef void function(sfString*, float, float) pf_sfString_SetPosition;
    	typedef void function(sfString*, float) pf_sfString_SetScaleX;
    	typedef void function(sfString*, float) pf_sfString_SetScaleY;
    	typedef void function(sfString*, float, float) pf_sfString_SetScale;
    	typedef void function(sfString*, float) pf_sfString_SetRotation;
    	typedef void function(sfString*, float, float) pf_sfString_SetCenter;
    	typedef void function(sfString*, Color) pf_sfString_SetColor;
    	typedef void function(sfString*, BlendMode) pf_sfString_SetBlendMode;
    	typedef float function(sfString*) pf_sfString_GetX;
    	typedef float function(sfString*) pf_sfString_GetY;
    	typedef float function(sfString*) pf_sfString_GetScaleX;
    	typedef float function(sfString*) pf_sfString_GetScaleY;
    	typedef float function(sfString*) pf_sfString_GetRotation;
    	typedef float function(sfString*) pf_sfString_GetCenterX;
    	typedef float function(sfString*) pf_sfString_GetCenterY;
    	typedef Color function(sfString*) pf_sfString_GetColor;
    	typedef BlendMode function(sfString*) pf_sfString_GetBlendMode;
    	typedef void function(sfString*, float, float) pf_sfString_Move;
    	typedef void function(sfString*, float, float) pf_sfString_Scale;
    	typedef void function(sfString*, float) pf_sfString_Rotate;
    	typedef void function(sfString*, char*) pf_sfString_SetText;
    	typedef void function(sfString*, wchar*) pf_sfString_SetUnicodeText;
    	typedef void function(sfString*, sfFont*) pf_sfString_SetFont;
    	typedef void function(sfString*, float) pf_sfString_SetSize;
    	typedef void function(sfString*, TextStyle) pf_sfString_SetStyle;
    	typedef wchar* function(sfString*) pf_sfString_GetUnicodeText;
    	typedef char* function(sfString*) pf_sfString_GetText;
    	typedef sfFont* function(sfString*) pf_sfString_GetFont;
    	typedef float function(sfString*) pf_sfString_GetSize;
    	typedef TextStyle function (sfString*) pf_sfString_GetStyle;
    	typedef sfFloatRect function(sfString*) pf_sfString_GetRect;
    
    	pf_sfString_Create sfString_Create;
    	pf_sfString_Destroy sfString_Destroy;
    	pf_sfString_SetX sfString_SetX;
    	pf_sfString_SetY sfString_SetY;
    	pf_sfString_SetPosition sfString_SetPosition;
    	pf_sfString_SetScaleX sfString_SetScaleX;
    	pf_sfString_SetScaleY sfString_SetScaleY;
    	pf_sfString_SetScale sfString_SetScale;
    	pf_sfString_SetRotation sfString_SetRotation;
    	pf_sfString_SetCenter sfString_SetCenter;
    	pf_sfString_SetColor sfString_SetColor;
    	pf_sfString_SetBlendMode sfString_SetBlendMode;
    	pf_sfString_GetX sfString_GetX;
    	pf_sfString_GetY sfString_GetY;
    	pf_sfString_GetScaleX sfString_GetScaleX;
    	pf_sfString_GetScaleY sfString_GetScaleY;
    	pf_sfString_GetRotation sfString_GetRotation;
    	pf_sfString_GetCenterX sfString_GetCenterX;
    	pf_sfString_GetCenterY sfString_GetCenterY;
    	pf_sfString_GetColor sfString_GetColor;
    	pf_sfString_GetBlendMode sfString_GetBlendMode;
    	pf_sfString_Move sfString_Move;
    	pf_sfString_Scale sfString_Scale;
    	pf_sfString_Rotate sfString_Rotate;
    	pf_sfString_SetText sfString_SetText;
    	pf_sfString_SetUnicodeText sfString_SetUnicodeText;
    	pf_sfString_SetFont sfString_SetFont;
    	pf_sfString_SetSize sfString_SetSize;
    	pf_sfString_SetStyle sfString_SetStyle;
    	pf_sfString_GetUnicodeText sfString_GetUnicodeText;
    	pf_sfString_GetText sfString_GetText;
    	pf_sfString_GetFont sfString_GetFont;
    	pf_sfString_GetSize sfString_GetSize;
    	pf_sfString_GetStyle sfString_GetStyle;
    	pf_sfString_GetRect sfString_GetRect;
    	
    	//shape.d
    	struct sfShape {};
    	
    	typedef sfShape* function() pf_sfShape_Create;
        typedef sfShape* function(float, float, float, float, float, Color, float, Color) pf_sfShape_CreateLine;
        typedef sfShape* function(float, float, float, float, Color, float, Color) pf_sfShape_CreateRectangle;
        typedef sfShape* function(float, float, float, Color, float, Color) pf_sfShape_CreateCircle;
        typedef void function(sfShape*) pf_sfShape_Destroy;
        typedef void function(sfShape*, float) pf_sfShape_SetX;
        typedef void function(sfShape*, float) pf_sfShape_SetY;
        typedef void function(sfShape*, float, float) pf_sfShape_SetPosition;
        typedef void function(sfShape*, float) pf_sfShape_SetScaleX;
        typedef void function(sfShape*, float) pf_sfShape_SetScaleY;
        typedef void function(sfShape*, float, float) pf_sfShape_SetScale;
        typedef void function(sfShape*, float) pf_sfShape_SetRotation;
        typedef void function(sfShape*, float, float) pf_sfShape_SetCenter;
        typedef void function(sfShape*, Color) pf_sfShape_SetColor;
        typedef void function(sfShape*, BlendMode) pf_sfShape_SetBlendMode;
        typedef float function(sfShape*) pf_sfShape_GetX;
        typedef float function(sfShape*) pf_sfShape_GetY;
        typedef float function(sfShape*) pf_sfShape_GetScaleX;
        typedef float function(sfShape*) pf_sfShape_GetScaleY;
        typedef float function(sfShape*) pf_sfShape_GetRotation;
        typedef float function(sfShape*) pf_sfShape_GetCenterX;
        typedef float function(sfShape*) pf_sfShape_GetCenterY;
        typedef Color function(sfShape*) pf_sfShape_GetColor;
        typedef BlendMode function(sfShape* Shape) pf_sfShape_GetBlendMode;
        typedef void function(sfShape* Shape, float, float) pf_sfShape_Move;
        typedef void function(sfShape* Shape, float, float) pf_sfShape_Scale;
        typedef void function(sfShape* Shape, float) pf_sfShape_Rotate;
        typedef void function(sfShape* Shape, float, float, Color, Color) pf_sfShape_AddPoint;
        typedef void function(sfShape* Shape, bool) pf_sfShape_EnableFill;
        typedef void function(sfShape* Shape, bool) pf_sfShape_EnableOutline;
        typedef void function(sfShape* Shape, float) pf_sfShape_SetOutlineWidth; 
        typedef uint function(sfShape* Shape) pf_sfShape_GetNbPoints;
        typedef void function(sfShape* Shape, uint, float*, float*) pf_sfShape_GetPoint;
        typedef float function(sfShape* Shape) pf_sfShape_GetOutlineWidth;
        
        pf_sfShape_Create sfShape_Create;
        pf_sfShape_CreateLine sfShape_CreateLine;
        pf_sfShape_CreateRectangle sfShape_CreateRectangle;
        pf_sfShape_CreateCircle sfShape_CreateCircle;
        pf_sfShape_Destroy sfShape_Destroy;
        pf_sfShape_SetX sfShape_SetX;
        pf_sfShape_SetY sfShape_SetY;
        pf_sfShape_SetPosition sfShape_SetPosition;
        pf_sfShape_SetScaleX sfShape_SetScaleX;
        pf_sfShape_SetScaleY sfShape_SetScaleY;
        pf_sfShape_SetScale sfShape_SetScale;
        pf_sfShape_SetRotation sfShape_SetRotation;
        pf_sfShape_SetCenter sfShape_SetCenter;
        pf_sfShape_SetColor  sfShape_SetColor;
        pf_sfShape_SetBlendMode sfShape_SetBlendMode;
        pf_sfShape_GetX sfShape_GetX;
        pf_sfShape_GetY sfShape_GetY;
        pf_sfShape_GetScaleX sfShape_GetScaleX;
        pf_sfShape_GetScaleY sfShape_GetScaleY;
        pf_sfShape_GetRotation sfShape_GetRotation;
        pf_sfShape_GetCenterX sfShape_GetCenterX;
        pf_sfShape_GetCenterY sfShape_GetCenterY;
        pf_sfShape_GetColor sfShape_GetColor;
        pf_sfShape_GetBlendMode sfShape_GetBlendMode;
        pf_sfShape_Move sfShape_Move;
        pf_sfShape_Scale sfShape_Scale;
        pf_sfShape_Rotate sfShape_Rotate;
        pf_sfShape_AddPoint sfShape_AddPoint;
        pf_sfShape_EnableFill sfShape_EnableFill;
        pf_sfShape_EnableOutline sfShape_EnableOutline;
        pf_sfShape_SetOutlineWidth sfShape_SetOutlineWidth;
        pf_sfShape_GetNbPoints sfShape_GetNbPoints;
        pf_sfShape_GetPoint sfShape_GetPoint;
        pf_sfShape_GetOutlineWidth sfShape_GetOutlineWidth;
        
        //font.d
        struct sfFont {};
        
        typedef sfFont* function() pf_sfFont_Create;
        typedef sfFont* function(char*, uint, wchar*) pf_sfFont_CreateFromFile;
        typedef sfFont* function(byte*, size_t, uint, wchar*) pf_sfFont_CreateFromMemory;
        typedef void function(sfFont*) pf_sfFont_Destroy;
        typedef sfFont* function() pf_sfFont_GetDefaultFont;
        
        pf_sfFont_Create sfFont_Create;
        pf_sfFont_CreateFromFile sfFont_CreateFromFile;
        pf_sfFont_CreateFromMemory sfFont_CreateFromMemory;
        pf_sfFont_Destroy sfFont_Destroy;
        pf_sfFont_GetDefaultFont sfFont_GetDefaultFont;
        
        //view.d
        struct sfView{};
        
        typedef sfView* function() pf_sfView_Create;
        typedef sfView* function(sfFloatRect) pf_sfView_CreateFromRect;
        typedef void function(sfView*) pf_sfView_Destroy;
        typedef void function(sfView*, float, float) pf_sfView_SetCenter;
        typedef void function(sfView*, float, float) pf_sfView_SetHalfSize;
        typedef void function(sfView*, sfFloatRect ViewRect) pf_sfView_SetFromRect;
        typedef float function(sfView*) pf_sfView_GetCenterX;
        typedef float function(sfView*) pf_sfView_GetCenterY;
        typedef float function(sfView*) pf_sfView_GetHalfSizeX;
        typedef float function(sfView*) pf_sfView_GetHalfSizeY;
        typedef sfFloatRect function(sfView*) pf_sfView_GetRect;
        typedef void function(sfView*, float, float) pf_sfView_Move;
        typedef void function(sfView*, float) pf_sfView_Zoom;

        pf_sfView_Create sfView_Create;
        pf_sfView_CreateFromRect sfView_CreateFromRect;
        pf_sfView_Destroy sfView_Destroy;
        pf_sfView_SetCenter sfView_SetCenter;
        pf_sfView_SetHalfSize sfView_SetHalfSize;
        pf_sfView_SetFromRect sfView_SetFromRect;
        pf_sfView_GetCenterX sfView_GetCenterX;
        pf_sfView_GetCenterY sfView_GetCenterY;
        pf_sfView_GetHalfSizeX sfView_GetHalfSizeX;
        pf_sfView_GetHalfSizeY sfView_GetHalfSizeY;
        pf_sfView_GetRect sfView_GetRect;
        pf_sfView_Move sfView_Move;
        pf_sfView_Zoom sfView_Zoom;
    }
}
else
{
    extern(C)
    {
        //font.d
        struct sfFont {};
        
        sfFont* sfFont_Create();
        sfFont* sfFont_CreateFromFile(char* Filename, uint CharSize, wchar* Charset);
        sfFont* sfFont_CreateFromMemory(byte* data, size_t sizeInBytes, uint CharSize, wchar* Charset);
        void sfFont_Destroy(sfFont*);
        sfFont* sfFont_GetDefaultFont();

        //sprite.d
        struct sfSprite {};
        
        sfSprite* sfSprite_Create();
        void sfSprite_Destroy(sfSprite*);
        void sfSprite_SetX(sfSprite*, float);
        void sfSprite_SetY(sfSprite*, float);
        void sfSprite_SetPosition(sfSprite*, float, float);
        void sfSprite_SetScaleX(sfSprite*, float);
        void sfSprite_SetScaleY(sfSprite*, float);
        void sfSprite_SetScale(sfSprite*, float, float);
        void sfSprite_SetRotation(sfSprite*, float);
        void sfSprite_SetCenter(sfSprite*, float, float);
        void sfSprite_SetColor(sfSprite*, Color);
        void sfSprite_SetBlendMode(sfSprite*, BlendMode);
        float sfSprite_GetX(sfSprite*);
        float sfSprite_GetY(sfSprite*);
        float sfSprite_GetScaleX(sfSprite*);
        float sfSprite_GetScaleY(sfSprite*);
        float sfSprite_GetRotation(sfSprite*);
        float sfSprite_GetCenterX(sfSprite*);
        float sfSprite_GetCenterY(sfSprite*);
        Color sfSprite_GetColor(sfSprite*);
        BlendMode sfSprite_GetBlendMode(sfSprite*);
        void sfSprite_Move(sfSprite*, float, float);
        void sfSprite_Scale(sfSprite*, float, float);
        void sfSprite_Rotate(sfSprite*, float);
        void sfSprite_SetImage(sfSprite*, sfImage*);
        void sfSprite_SetSubRect(sfSprite*, sfIntRect*);
        void sfSprite_Resize(sfSprite*, float, float);
        void sfSprite_FlipX(sfSprite*, int);
        void sfSprite_FlipY(sfSprite*, int);
        sfImage* sfSprite_GetImage(sfSprite*);
        sfIntRect* sfSprite_GetSubRect(sfSprite*);
        float sfSprite_GetWidth(sfSprite*);
        float sfSprite_GetHeight(sfSprite*);
        Color sfSprite_GetPixel(sfSprite*, uint, uint);
    
        //string.d
        struct sfString {};
        
        sfString* sfString_Create();
        void sfString_Destroy(sfString*);
        void sfString_SetX(sfString*, float);
        void sfString_SetY(sfString*, float);
        void sfString_SetPosition(sfString*, float, float);
        void sfString_SetScaleX(sfString*, float);
        void sfString_SetScaleY(sfString*, float);
        void sfString_SetScale(sfString*, float, float);
        void sfString_SetRotation(sfString*, float);
        void sfString_SetCenter(sfString*, float, float);
        void sfString_SetColor(sfString*, Color);
        void sfString_SetBlendMode(sfString*, BlendMode);
        float sfString_GetX(sfString*);
        float sfString_GetY(sfString*);
        float sfString_GetScaleX(sfString*);
        float sfString_GetScaleY(sfString*);
        float sfString_GetRotation(sfString*);
        float sfString_GetCenterX(sfString*);
        float sfString_GetCenterY(sfString*);
        Color sfString_GetColor(sfString*);
        BlendMode sfString_GetBlendMode(sfString*);
        void sfString_Move(sfString*, float, float);
        void sfString_Scale(sfString*, float, float);
        void sfString_Rotate(sfString*, float);
        void sfString_SetText(sfString*, char*);
        void sfString_SetUnicodeText(sfString*, wchar*);
        void sfString_SetFont(sfString*, sfFont*);
        void sfString_SetSize(sfString*, float);
        void sfString_SetStyle(sfString*, TextStyle);
        wchar* sfString_GetUnicodeText(sfString*);
        char* sfString_GetText(sfString*);
        sfFont* sfString_GetFont(sfString*);
        float sfString_GetSize(sfString*);
        TextStyle sfString_GetStyle(sfString*);
        sfFloatRect sfString_GetRect(sfString*);
        
        //shape.d
        struct sfShape {};
        
        sfShape* sfShape_Create();
        sfShape* sfShape_CreateLine(float P1X, float P1Y, float P2X, float P2Y, float Thickness, Color Col, float Outline, Color OutlineCol);
        sfShape* sfShape_CreateRectangle(float P1X, float P1Y, float P2X, float P2Y, Color Col, float Outline, Color OutlineCol);
        sfShape* sfShape_CreateCircle(float X, float Y, float Radius, Color Col, float Outline, Color OutlineCol);
        void sfShape_Destroy(sfShape* Shape);
        void sfShape_SetX(sfShape* Shape, float X);
        void sfShape_SetY(sfShape* Shape, float Y);
        void sfShape_SetPosition(sfShape* Shape, float X, float Y);
        void sfShape_SetScaleX(sfShape* Shape, float Scale);
        void sfShape_SetScaleY(sfShape* Shape, float Scale);
        void sfShape_SetScale(sfShape* Shape, float ScaleX, float ScaleY);
        void sfShape_SetRotation(sfShape* Shape, float Rotation);
        void sfShape_SetCenter(sfShape* Shape, float X, float Y);
        void sfShape_SetColor(sfShape* Shape, Color Color);
        void sfShape_SetBlendMode(sfShape* Shape, BlendMode Mode);
        float sfShape_GetX(sfShape* Shape);
        float sfShape_GetY(sfShape* Shape);
        float sfShape_GetScaleX(sfShape* Shape);
        float sfShape_GetScaleY(sfShape* Shape);
        float sfShape_GetRotation(sfShape* Shape);
        float sfShape_GetCenterX(sfShape* Shape);
        float sfShape_GetCenterY(sfShape* Shape);
        Color sfShape_GetColor(sfShape* Shape);
        BlendMode sfShape_GetBlendMode(sfShape* Shape);
        void sfShape_Move(sfShape* Shape, float OffsetX, float OffsetY);
        void sfShape_Scale(sfShape* Shape, float FactorX, float FactorY);
        void sfShape_Rotate(sfShape* Shape, float Angle);
        void sfShape_AddPoint(sfShape* Shape, float X, float Y, Color Col, Color OutlineCol);
        void sfShape_EnableFill(sfShape* Shape, bool Enable);
        void sfShape_EnableOutline(sfShape* Shape, bool Enable);
        void sfShape_SetOutlineWidth(sfShape* Shape, float Width);
        uint sfShape_GetNbPoints(sfShape* Shape);
        void sfShape_GetPoint(sfShape* Shape, uint Index, float* X, float* Y);
        float sfShape_GetOutlineWidth(sfShape* Shape);
                
        //renderwindow.d
        struct sfRenderWindow {};
        
        sfRenderWindow* sfRenderWindow_Create(VideoMode, char*, ulong, WindowSettings);
        sfRenderWindow* sfRenderWindow_CreateFromHandle(WindowHandle, WindowSettings);
        void sfRenderWindow_Destroy(sfRenderWindow*);
        sfInput* sfRenderWindow_GetInput(sfRenderWindow*);
        void sfRenderWindow_DrawPostFX(sfRenderWindow*, sfPostFX*);
        void sfRenderWindow_DrawSprite(sfRenderWindow*, sfSprite*);
        void sfRenderWindow_DrawString(sfRenderWindow*, sfString*);
        void sfRenderWindow_DrawShape(sfRenderWindow*, sfShape*);
        sfImage* sfRenderWindow_Capture(sfRenderWindow*);
        void sfRenderWindow_SetBackgroundColor(sfRenderWindow*, Color);
        void sfRenderWindow_SetView(sfRenderWindow*, sfView*);
        sfView* sfRenderWindow_GetView(sfRenderWindow*);
        sfView* sfRenderWindow_GetDefaultView(sfRenderWindow*);
        void sfRenderWindow_ConvertCoords(sfRenderWindow*, uint, uint, float*, float*, sfView*);
        void sfRenderWindow_PreserveOpenGLStates(sfRenderWindow*, bool);
    
        //postFX.d
        struct sfPostFX {};
        
        sfPostFX* sfPostFX_CreateFromFile(char*);
        sfPostFX* sfPostFX_CreateFromMemory(char*);
        void sfPostFX_Destroy(sfPostFX*);
        void sfPostFX_SetParameter1(sfPostFX*, char*, float);
        void sfPostFX_SetParameter2(sfPostFX*, char*, float, float);
        void sfPostFX_SetParameter3(sfPostFX*, char*, float, float, float);
        void sfPostFX_SetParameter4(sfPostFX*, char*, float, float, float, float);
        void sfPostFX_SetTexture(sfPostFX*, char*, sfImage*);
        bool sfPostFX_CanUsePostFX();
        
        //image.d
        struct sfImage {};
        
        sfImage* sfImage_Create();
        sfImage* sfImage_CreateFromColor(uint, uint, Color);
        sfImage* sfImage_CreateFromPixels(uint, uint, ubyte*);
        sfImage* sfImage_CreateFromFile(char*);
        sfImage* sfImage_CreateFromMemory(byte* ,size_t);
        void sfImage_Destroy(sfImage*);
        bool sfImage_SaveToFile(sfImage*, char*);
        void sfImage_CreateMaskFromColor(sfImage*, Color, ubyte);
        bool sfImage_Resize(sfImage*, uint, uint, Color);
        void sfImage_SetPixel(sfImage*, uint, uint, Color);
        Color sfImage_GetPixel(sfImage*, uint, uint);
        ubyte* sfImage_GetPixelsPtr(sfImage*);
        void sfImage_Bind(sfImage*);
        void sfImage_SetSmooth(sfImage*, int);
        uint sfImage_GetWidth(sfImage*);
        uint sfImage_GetHeight(sfImage*);
        bool sfImage_IsSmooth(sfImage*);
        
        //view.d
        struct sfView{};
        
        sfView* sfView_Create();
        sfView* sfView_CreateFromRect(sfFloatRect);
        void sfView_Destroy(sfView*);
        void sfView_SetCenter(sfView*, float, float);
        void sfView_SetHalfSize(sfView*, float, float);
        void sfView_SetFromRect(sfView*, sfFloatRect ViewRect);
        float sfView_GetCenterX(sfView*);
        float sfView_GetCenterY(sfView*);
        float sfView_GetHalfSizeX(sfView*);
        float sfView_GetHalfSizeY(sfView*);
        sfFloatRect sfView_GetRect(sfView*);
        void sfView_Move(sfView*, float, float);
        void sfView_Zoom(sfView*, float);
    }
}
