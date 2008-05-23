/*
* License Applicability. Except to the extent portions of this file are
* made subject to an alternative license as permitted in the SGI Free
* Software License B, Version 1.1 (the "License"), the contents of this
* file are subject only to the provisions of the License. You may not use
* this file except in compliance with the License. You may obtain a copy
* of the License at Silicon Graphics, Inc., attn: Legal Services, 1600
* Amphitheatre Parkway, Mountain View, CA 94043-1351, or at:
* 
* http://oss.sgi.com/projects/FreeB
* 
* Note that, as provided in the License, the Software is distributed on an
* "AS IS" basis, with ALL EXPRESS AND IMPLIED WARRANTIES AND CONDITIONS
* DISCLAIMED, INCLUDING, WITHOUT LIMITATION, ANY IMPLIED WARRANTIES AND
* CONDITIONS OF MERCHANTABILITY, SATISFACTORY QUALITY, FITNESS FOR A
* PARTICULAR PURPOSE, AND NON-INFRINGEMENT.
* 
* Original Code. The Original Code is: OpenGL Sample Implementation,
* Version 1.2.1, released January 26, 2000, developed by Silicon Graphics,
* Inc. The Original Code is Copyright (c) 1991-2000 Silicon Graphics, Inc.
* Copyright in any portions created by third parties is as indicated
* elsewhere herein. All Rights Reserved.
* 
* Additional Notice Provisions: This software was created using the
* OpenGL(R) version 1.2.1 Sample Implementation published by SGI, but has
* not been independently verified as being compliant with the OpenGL(R)
* version 1.2.1 Specification.
*/

//==============================================================================
//  DSFML specifics
//==============================================================================

module dsfml.GL.glu;

version (Windows)
{
    version(build)
    {
        pragma(link, "Glu32");
    }
}
version (linux)
{
    version(build)
    {
        pragma(link, "GLU");
    }
}

import dsfml.GL.gl;

//==============================================================================
//==============================================================================


//==============================================================================
// CONSTANTS
//==============================================================================
// StringName
const GLuint GLU_VERSION			= 100800;
const GLuint GLU_EXTENSIONS			= 100801;
// ErrorCode
const GLuint GLU_INVALID_ENUM			= 100900;
const GLuint GLU_INVALID_VALUE			= 100901;
const GLuint GLU_OUT_OF_MEMORY			= 100902;
const GLuint GLU_INVALID_OPERATION		= 100904;
// NurbsDisplay
const GLuint GLU_OUTLINE_POLYGON		= 100240;
const GLuint GLU_OUTLINE_PATCH			= 100241;
// NurbsCallback
const GLuint GLU_NURBS_ERROR			= 100103;
const GLuint GLU_ERROR				= 100103;
const GLuint GLU_NURBS_BEGIN			= 100164;
const GLuint GLU_NURBS_BEGIN_EXT		= 100164;
const GLuint GLU_NURBS_VERTEX			= 100165;
const GLuint GLU_NURBS_VERTEX_EXT		= 100165;
const GLuint GLU_NURBS_NORMAL			= 100166;
const GLuint GLU_NURBS_NORMAL_EXT		= 100166;
const GLuint GLU_NURBS_COLOR			= 100167;
const GLuint GLU_NURBS_COLOR_EXT		= 100167;
const GLuint GLU_NURBS_TEXTURE_COORD		= 100168;
const GLuint GLU_NURBS_TEX_COORD_EXT		= 100168;
const GLuint GLU_NURBS_END			= 100169;
const GLuint GLU_NURBS_END_EXT			= 100169;
const GLuint GLU_NURBS_BEGIN_DATA		= 100170;
const GLuint GLU_NURBS_BEGIN_DATA_EXT		= 100170;
const GLuint GLU_NURBS_VERTEX_DATA		= 100171;
const GLuint GLU_NURBS_VERTEX_DATA_EXT		= 100171;
const GLuint GLU_NURBS_NORMAL_DATA		= 100172;
const GLuint GLU_NURBS_NORMAL_DATA_EXT		= 100172;
const GLuint GLU_NURBS_COLOR_DATA		= 100173;
const GLuint GLU_NURBS_COLOR_DATA_EXT		= 100173;
const GLuint GLU_NURBS_TEXTURE_COORD_DATA	= 100174;
const GLuint GLU_NURBS_TEX_COORD_DATA_EXT 	= 100174;
const GLuint GLU_NURBS_END_DATA			= 100175;
const GLuint GLU_NURBS_END_DATA_EXT		= 100175;
// NurbsError
const GLuint GLU_NURBS_ERROR1			= 100251;
const GLuint GLU_NURBS_ERROR2			= 100252;
const GLuint GLU_NURBS_ERROR3			= 100253;
const GLuint GLU_NURBS_ERROR4			= 100254;
const GLuint GLU_NURBS_ERROR5			= 100255;
const GLuint GLU_NURBS_ERROR6			= 100256;
const GLuint GLU_NURBS_ERROR7			= 100257;
const GLuint GLU_NURBS_ERROR8			= 100258;
const GLuint GLU_NURBS_ERROR9			= 100259;
const GLuint GLU_NURBS_ERROR10			= 100260;
const GLuint GLU_NURBS_ERROR11			= 100261;
const GLuint GLU_NURBS_ERROR12			= 100262;
const GLuint GLU_NURBS_ERROR13			= 100263;
const GLuint GLU_NURBS_ERROR14			= 100264;
const GLuint GLU_NURBS_ERROR15			= 100265;
const GLuint GLU_NURBS_ERROR16			= 100266;
const GLuint GLU_NURBS_ERROR17			= 100267;
const GLuint GLU_NURBS_ERROR18			= 100268;
const GLuint GLU_NURBS_ERROR19			= 100269;
const GLuint GLU_NURBS_ERROR20			= 100270;
const GLuint GLU_NURBS_ERROR21			= 100271;
const GLuint GLU_NURBS_ERROR22			= 100272;
const GLuint GLU_NURBS_ERROR23			= 100273;
const GLuint GLU_NURBS_ERROR24			= 100274;
const GLuint GLU_NURBS_ERROR25			= 100275;
const GLuint GLU_NURBS_ERROR26			= 100276;
const GLuint GLU_NURBS_ERROR27			= 100277;
const GLuint GLU_NURBS_ERROR28			= 100278;
const GLuint GLU_NURBS_ERROR29			= 100279;
const GLuint GLU_NURBS_ERROR30			= 100280;
const GLuint GLU_NURBS_ERROR31			= 100281;
const GLuint GLU_NURBS_ERROR32			= 100282;
const GLuint GLU_NURBS_ERROR33			= 100283;
const GLuint GLU_NURBS_ERROR34			= 100284;
const GLuint GLU_NURBS_ERROR35			= 100285;
const GLuint GLU_NURBS_ERROR36			= 100286;
const GLuint GLU_NURBS_ERROR37			= 100287;
// NurbsProperty
const GLuint GLU_AUTO_LOAD_MATRIX		= 100200;
const GLuint GLU_CULLING			= 100201;
const GLuint GLU_SAMPLING_TOLERANCE		= 100203;
const GLuint GLU_DISPLAY_MODE			= 100204;
const GLuint GLU_PARAMETRIC_TOLERANCE		= 100202;
const GLuint GLU_SAMPLING_METHOD		= 100205;
const GLuint GLU_U_STEP				= 100206;
const GLuint GLU_V_STEP				= 100207;
const GLuint GLU_NURBS_MODE			= 100160;
const GLuint GLU_NURBS_MODE_EXT			= 100160;
const GLuint GLU_NURBS_TESSELLATOR		= 100161;
const GLuint GLU_NURBS_TESSELLATOR_EXT		= 100161;
const GLuint GLU_NURBS_RENDERER			= 100162;
const GLuint GLU_NURBS_RENDERER_EXT		= 100162;
// NurbsSampling
const GLuint GLU_OBJECT_PARAMETRIC_ERROR	= 100208;
const GLuint GLU_OBJECT_PARAMETRIC_ERROR_EXT	= 100208;
const GLuint GLU_OBJECT_PATH_LENGTH		= 100209;
const GLuint GLU_OBJECT_PATH_LENGTH_EXT		= 100209;
const GLuint GLU_PATH_LENGTH			= 100215;
const GLuint GLU_PARAMETRIC_ERROR		= 100216;
const GLuint GLU_DOMAIN_DISTANCE		= 100217;
// NurbsTrim
const GLuint GLU_MAP1_TRIM_2			= 100210;
const GLuint GLU_MAP2_TRIM_3			= 100211;
// QuadricDrawStyle
const GLuint GLU_POINT				= 100010;
const GLuint GLU_LINE				= 100011;
const GLuint GLU_FILL				= 100012;
const GLuint GLU_SILHOUETTE			= 100013;
// QuadricNormal
const GLuint GLU_TESS_BEGIN			= 100100;
const GLuint GLU_BEGIN				= 100100;
const GLuint GLU_TESS_VERTEX			= 100101;
const GLuint GLU_VERTEX				= 100101;
const GLuint GLU_TESS_END			= 100102;
const GLuint GLU_END				= 100102;
const GLuint GLU_TESS_ERROR			= 100103;
const GLuint GLU_TESS_EDGE_FLAG			= 100104;
const GLuint GLU_EDGE_FLAG			= 100104;
const GLuint GLU_TESS_COMBINE			= 100105;
const GLuint GLU_TESS_BEGIN_DATA		= 100106;
const GLuint GLU_TESS_VERTEX_DATA		= 100107;
const GLuint GLU_TESS_END_DATA			= 100108;
const GLuint GLU_TESS_ERROR_DATA		= 100109;
const GLuint GLU_TESS_EDGE_FLAG_DATA		= 100110;
const GLuint GLU_TESS_COMBINE_DATA		= 100111;
// TessContour
const GLuint GLU_CW				= 100120;
const GLuint GLU_CCW				= 100121;
const GLuint GLU_INTERIOR			= 100122;
const GLuint GLU_EXTERIOR			= 100123;
const GLuint GLU_UNKNOWN			= 100124;
// TessProperty
const GLuint GLU_TESS_WINDING_RULE		= 100140;
const GLuint GLU_TESS_BOUNDARY_ONLY		= 100141;
const GLuint GLU_TESS_TOLERANCE			= 100142;
// TessError
const GLuint GLU_TESS_ERROR1			= 100151;
const GLuint GLU_TESS_ERROR2			= 100152;
const GLuint GLU_TESS_ERROR3			= 100153;
const GLuint GLU_TESS_ERROR4			= 100154;
const GLuint GLU_TESS_ERROR5			= 100155;
const GLuint GLU_TESS_ERROR6			= 100156;
const GLuint GLU_TESS_ERROR7			= 100157;
const GLuint GLU_TESS_ERROR8			= 100158;
const GLuint GLU_TESS_MISSING_BEGIN_POLYGON	= 100151;
const GLuint GLU_TESS_MISSING_BEGIN_COUNTER	= 100152;
const GLuint GLU_TESS_MISSING_END_POLYGON	= 100153;
const GLuint GLU_TESS_MISSING_END_COUNTER	= 100154;
const GLuint GLU_TESS_COORD_TOO_LARGE		= 100155;
const GLuint GLU_TESS_NEED_COMBINE_CALLBACK	= 100156;
// TessWinding
const GLuint GLU_TESS_WINDING_ODD		= 100130;
const GLuint GLU_TESS_WINDING_NONZERO		= 100131;
const GLuint GLU_TESS_WINDING_POSITIVE		= 100132;
const GLuint GLU_TESS_WINDING_NEGATIVE		= 100133;
const GLuint GLU_TESS_WINDING_ABS_GEQ_TWO	= 100134;

const GLdouble GLU_TESS_MAX_COORD		= 1.0e150;

//==============================================================================
// TYPES
//==============================================================================

struct GLUnurbs { }
struct GLUquadric { }
struct GLUtesselator { }

typedef GLUnurbs GLUnurbsObj;
typedef GLUquadric GLUquadricObj;
typedef GLUtesselator GLUtesselatorObj;
typedef GLUtesselator GLUtriangulatorObj;

//==============================================================================
// FUNCTIONS
//==============================================================================
typedef GLvoid function() _GLUfuncptr;
extern (System)
{
    GLvoid gluBeginCurve(GLUnurbs*);
    GLvoid gluBeginPolygon(GLUtesselator*);
    GLvoid gluBeginSurface(GLUnurbs*);
    GLvoid gluBeginTrim(GLUnurbs*);
    GLint gluBuild1DMipmapLevels(GLenum, GLint, GLsizei, GLenum, GLenum, GLint, GLint, GLint, GLvoid*);
    GLint gluBuild1DMipmaps(GLenum, GLint, GLsizei, GLenum, GLenum, GLvoid*);
    GLint gluBuild2DMipmapLevels(GLenum, GLint, GLsizei, GLsizei, GLenum, GLenum, GLint, GLint, GLint, GLvoid*);
    GLint gluBuild2DMipmaps(GLenum, GLint, GLsizei, GLsizei, GLenum, GLenum, GLvoid*);
    GLint gluBuild3DMipmapLevels(GLenum, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLenum, GLint, GLint, GLint, GLvoid*);
    GLint gluBuild3DMipmaps(GLenum, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLenum, GLvoid*);
    GLboolean gluCheckExtension(GLubyte*, GLubyte*);
    GLvoid gluCylinder(GLUquadric*, GLdouble, GLdouble, GLdouble, GLint, GLint);
    GLvoid gluDeleteNurbsRenderer(GLUnurbs*);
    GLvoid gluDeleteQuadric(GLUquadric*);
    GLvoid gluDeleteTess(GLUtesselator*);
    GLvoid gluDisk(GLUquadric*, GLdouble, GLdouble, GLint, GLint);
    GLvoid gluEndCurve(GLUnurbs*);
    GLvoid gluEndPolygon(GLUtesselator*);
    GLvoid gluEndSurface(GLUnurbs*);
    GLvoid gluEndTrim(GLUnurbs*);
    GLchar* gluErrorString(GLenum);
    GLvoid gluGetNurbsProperty(GLUnurbs*,GLenum,GLfloat*);
    GLchar* gluGetString(GLenum);
    GLvoid gluGetTessProperty(GLUtesselator*,GLenum,GLdouble*);
    GLvoid gluLoadSamplingMatrices(GLUnurbs*, GLfloat*, GLfloat*, GLint*);
    GLvoid gluLookAt(GLdouble, GLdouble, GLdouble, GLdouble, GLdouble, GLdouble, GLdouble, GLdouble, GLdouble);
    GLUnurbs* gluNewNurbsRenderer();
    GLUquadric* gluNewQuadric();
    GLUtesselator* gluNewTess();
    GLvoid gluNextContour(GLUtesselator*, GLenum);
    GLvoid gluNurbsCallback(GLUnurbs*, GLenum, _GLUfuncptr);
    GLvoid gluNurbsCallbackData(GLUnurbs*, GLvoid*);
    GLvoid gluNurbsCallbackDataEXT(GLUnurbs*, GLvoid*);
    GLvoid gluNurbsCurve(GLUnurbs*, GLint, GLfloat*, GLint, GLfloat*, GLint, GLenum);
    GLvoid gluNurbsProperty(GLUnurbs*, GLenum, GLfloat);
    GLvoid gluNurbsSurface(GLUnurbs*, GLint, GLfloat*, GLint, GLfloat*, GLint, GLint, GLfloat*, GLint, GLint, GLenum);
    GLvoid gluOrtho2D(GLdouble, GLdouble, GLdouble, GLdouble);
    GLvoid gluPartialDisk(GLUquadric*, GLdouble, GLdouble, GLint, GLint, GLdouble, GLdouble);
    GLvoid gluPerspective(GLdouble, GLdouble, GLdouble, GLdouble);
    GLvoid gluPickMatrix(GLdouble, GLdouble, GLdouble, GLdouble, GLint*);
    GLint gluProject(GLdouble, GLdouble, GLdouble, GLdouble*, GLdouble*, GLint*, GLdouble*, GLdouble*, GLdouble*);
    GLvoid gluPwlCurve(GLUnurbs*, GLint, GLfloat*, GLint, GLenum);
    GLvoid gluQuadricCallback(GLUquadric*, GLenum,_GLUfuncptr);
    GLvoid gluQuadricDrawStyle(GLUquadric*, GLenum);
    GLvoid gluQuadricNormals(GLUquadric*, GLenum);
    GLvoid gluQuadricOrientation(GLUquadric*, GLenum);
    GLvoid gluQuadricTexture(GLUquadric*, GLboolean);
    GLint gluScaleImage(GLenum, GLsizei, GLsizei, GLenum, GLvoid*, GLsizei, GLsizei, GLenum, GLvoid*);
    GLvoid gluSphere(GLUquadric*, GLdouble, GLint, GLint);
    GLvoid gluTessBeginContour(GLUtesselator*);
    GLvoid gluTessBeginPolygon(GLUtesselator*, GLvoid*);
    GLvoid gluTessCallback(GLUtesselator*, GLenum, _GLUfuncptr);
    GLvoid gluTessEndContour(GLUtesselator*);
    GLvoid gluTessEndPolygon(GLUtesselator*);
    GLvoid gluTessNormal(GLUtesselator*, GLdouble, GLdouble, GLdouble);
    GLvoid gluTessProperty(GLUtesselator*, GLenum, GLdouble);
    GLvoid gluTessVertex(GLUtesselator*, GLdouble*, GLvoid*);
    GLint gluUnProject(GLdouble, GLdouble, GLdouble, GLdouble*, GLdouble*, GLint*, GLdouble*, GLdouble*, GLdouble*);
    GLint gluUnProject4(GLdouble, GLdouble, GLdouble, GLdouble, GLdouble*, GLdouble*, GLint*, GLdouble, GLdouble, GLdouble*, GLdouble*, GLdouble*, GLdouble*);
}
