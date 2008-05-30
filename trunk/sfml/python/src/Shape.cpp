#include "Shape.hpp"

#include <SFML/Graphics/Color.hpp>
#include "Color.hpp"

extern PyTypeObject PySfColorType;

static PyMemberDef PySfShape_members[] = {
    {NULL}  /* Sentinel */
};



static void
PySfShape_dealloc(PySfShape* self)
{
	delete self->obj;
	self->ob_type->tp_free((PyObject*)self);
}

static PyObject *
PySfShape_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
	PySfShape *self;

	self = (PySfShape *)type->tp_alloc(type, 0);

	if (self != NULL)
	{
	}

	return (PyObject *)self;
}

static int
PySfShape_init(PySfShape *self, PyObject *args)
{
	self->obj = new sf::Shape();
	return 0;
}


// void AddPoint(float X, float Y, const Color& Col = Color(255, 255, 255), const Color& OutlineCol = Color(0, 0, 0));
static PyObject *
PySfShape_AddPoint(PySfShape* self, PyObject *args, PyObject *kwds)
{
	char *kwlist[] = {"X", "Y", "Col", "OutlineCol", NULL};
	float X, Y;
	sf::Color *Col, *OutlineCol;
	PySfColor *ColTmp=NULL, *OutlineColTmp=NULL;
	if (!PyArg_ParseTupleAndKeywords(args, kwds, "ff|O!O!", kwlist, &X, &Y, &PySfColorType, &Col, &PySfColorType, &OutlineCol))
		return NULL;

	if (ColTmp)
	{
		PySfColorUpdate(ColTmp);
		Col = ColTmp->obj;
	}
	else
		Col = (sf::Color *)&sf::Color::Black;

	if (OutlineColTmp)
	{
		PySfColorUpdate(OutlineColTmp);
		OutlineCol = OutlineColTmp->obj;
	}
	else
		OutlineCol = (sf::Color *)&sf::Color::Black;

	self->obj->AddPoint(X, Y, *Col, *OutlineCol);

	Py_RETURN_NONE;
}

static PyObject *
PySfShape_SetOutlineWidth(PySfShape* self, PyObject *args)
{
	self->obj->SetOutlineWidth(PyFloat_AsDouble(args));
	Py_RETURN_NONE;
}

static PyObject *
PySfShape_GetOutlineWidth(PySfShape* self)
{
	return PyFloat_FromDouble(self->obj->GetOutlineWidth());
}

// static Shape Line(float X0, float Y0, float X1, float Y1, float Thickness, const Color& Col, float Outline = 0.f, const Color& OutlineCol = sf::Color(0, 0, 0));
static PyObject *
PySfShape_Line(PySfShape* self, PyObject *args, PyObject *kwds)
{
	char *kwlist[] = {"X0", "Y0", "X1", "Y1", "Thickness", "Col", "Outline", "OutlineCol", NULL};
	PySfShape *Line = GetNewPySfShape();
	float X0, Y0, X1, Y1, Thickness, Outline = 0.f;
	sf::Color *OutlineCol;
	PySfColor *ColTmp, *OutlineColTmp=NULL;
	if (!PyArg_ParseTupleAndKeywords(args, kwds, "fffffO!|fO!", kwlist, &X0, &Y0, &X1, &Y1, &Thickness, &PySfColorType, &ColTmp, &Outline, &PySfColorType, &OutlineColTmp))
		return NULL;
	if (OutlineColTmp)
	{
		PySfColorUpdate(OutlineColTmp);
		OutlineCol = OutlineColTmp->obj;
	}
	else
		OutlineCol = (sf::Color *)&sf::Color::Black;

	PySfColorUpdate(ColTmp);
	Line->obj = new sf::Shape(sf::Shape::Line(X0, Y0, X1, Y1, Thickness, *(ColTmp->obj), Outline, *OutlineCol));
	return (PyObject *)Line;
}

// static Shape Rectangle(float X0, float Y0, float X1, float Y1, const Color& Col, float Outline = 0.f, const Color& OutlineCol = sf::Color(0, 0, 0));
static PyObject *
PySfShape_Rectangle(PySfShape* self, PyObject *args, PyObject *kwds)
{
	char *kwlist[] = {"X0", "Y0", "X1", "Y1", "Col", "Outline", "OutlineCol", NULL};
	PySfShape *Rectangle = GetNewPySfShape();
	float X0, Y0, X1, Y1, Outline = 0.f;
	sf::Color *OutlineCol;
	PySfColor *ColTmp, *OutlineColTmp=NULL;
	if (!PyArg_ParseTupleAndKeywords(args, kwds, "ffffO!|fO!", kwlist, &X0, &Y0, &X1, &Y1, &PySfColorType, &ColTmp, &Outline, &PySfColorType, &OutlineColTmp))
		return NULL;
	if (OutlineColTmp)
	{
		PySfColorUpdate(OutlineColTmp);
		OutlineCol = OutlineColTmp->obj;
	}
	else
		OutlineCol = (sf::Color *)&sf::Color::Black;

	PySfColorUpdate(ColTmp);
	Rectangle->obj = new sf::Shape(sf::Shape::Rectangle(X0, Y0, X1, Y1, *(ColTmp->obj), Outline, *OutlineCol));
	return (PyObject *)Rectangle;
}

// static Shape Circle(float X, float Y, float Radius, const Color& Col, float Outline = 0.f, const Color& OutlineCol = sf::Color(0, 0, 0));
static PyObject *
PySfShape_Circle(PySfShape* self, PyObject *args, PyObject *kwds)
{
	char *kwlist[] = {"X", "Y", "Radius", "Col", "Outline", "OutlineCol", NULL};
	PySfShape *Circle = GetNewPySfShape();
	float X, Y, Radius, Outline = 0.f;
	sf::Color *OutlineCol;
	PySfColor *ColTmp, *OutlineColTmp=NULL;
	if (!PyArg_ParseTupleAndKeywords(args, kwds, "fffO!|fO!", kwlist, &X, &Y, &Radius, &PySfColorType, &ColTmp, &Outline, &PySfColorType, &OutlineColTmp))
		return NULL;
	if (OutlineColTmp)
	{
		PySfColorUpdate(OutlineColTmp);
		OutlineCol = OutlineColTmp->obj;
	}
	else
		OutlineCol = (sf::Color *)&sf::Color::Black;

	PySfColorUpdate(ColTmp);
	Circle->obj = new sf::Shape(sf::Shape::Circle(X, Y, Radius, *(ColTmp->obj), Outline, *OutlineCol));
	return (PyObject *)Circle;
}

static PyObject *
PySfShape_GetPoint(PySfShape* self, PyObject *args)
{
	sf::Vector2f result = self->obj->GetPoint(PyLong_AsUnsignedLong(args));
	return Py_BuildValue("ff", result.x, result.y);
}

static PyObject *
PySfShape_GetNbPoints(PySfShape* self, PyObject *args)
{
	return PyLong_FromUnsignedLong(self->obj->GetNbPoints());
}

static PyObject *
PySfShape_EnableFill(PySfShape* self, PyObject *args)
{
	if (args == Py_False)
		self->obj->EnableFill(false);
	else
		self->obj->EnableFill(true);
	Py_RETURN_NONE;
}

static PyObject *
PySfShape_EnableOutline(PySfShape* self, PyObject *args)
{
	if (args == Py_False)
		self->obj->EnableOutline(false);
	else
		self->obj->EnableOutline(true);
	Py_RETURN_NONE;
}

static PyMethodDef PySfShape_methods[] = {
	{"GetPoint", (PyCFunction)PySfShape_GetPoint, METH_O, "Get a point of the shape.\n    param Index-th point."},
	{"GetNbPoints", (PyCFunction)PySfShape_GetNbPoints, METH_NOARGS, "Get the number of points composing the shape.\n    param Total number of points."},
	{"EnableFill", (PyCFunction)PySfShape_EnableFill, METH_O, "Enable or disable filling the shape. Fill is enabled by default.\n    param Enable : True to enable, false to disable."},
	{"EnableOutline", (PyCFunction)PySfShape_EnableOutline, METH_O, "Enable or disable drawing the shape outline. Outline is enabled by default.\n    param Enable : True to enable, false to disable"},
	{"AddPoint", (PyCFunction)PySfShape_AddPoint, METH_VARARGS | METH_KEYWORDS, "Add a point to the shape.\n    param X : X coordinate of the point\n    param Y : Y coordinate of the point\n    param Col : Color of the point (white by default)\n    param OutlineCol : Outline color of the point (black by default)."},
	{"SetOutlineWidth", (PyCFunction)PySfShape_SetOutlineWidth, METH_O, "Change the width of the shape outline.\n    param Width : New width (use 0 to remove the outline)."},
	{"GetOutlineWidth", (PyCFunction)PySfShape_GetOutlineWidth, METH_NOARGS, "Get the width of the shape outline.\n    param return Current outline width"},
	{"Line", (PyCFunction)PySfShape_Line, METH_STATIC | METH_VARARGS | METH_KEYWORDS, "Line(X0, Y0, X1, Y1, Thickness, Col, Outline = 0., OutlineCol = sf.Color(0, 0, 0))\n\n\
Create a shape made of a single line.\n\
    param X0 :         X coordinate of the first point.\n    param Y0 :         Y coordinate of the first point.\n\
    param X1 :         X coordinate of the second point.\n    param Y1 :         Y coordinate of the second point.\n\
    param Thickness :  Line thickness.\n    param Col :        Color used to draw the line\n    param Outline :    Outline width (0 by default)\n\
    param OutlineCol : Color used to draw the outline (black by default)."},
	{"Rectangle", (PyCFunction)PySfShape_Rectangle, METH_STATIC | METH_VARARGS | METH_KEYWORDS, "Rectangle(X0, Y0, X1, Y1, Col, Outline = 0., OutlineCol = sf.Color(0, 0, 0))\n\n\
Create a shape made of a single rectangle.\n\
    param X0 :         X coordinate of the first point.\n    param Y0 :         Y coordinate of the first point.\n\
    param X1 :         X coordinate of the second point.\n    param Y1 :         Y coordinate of the second point.\n\
    param Col :        Color used to fill the rectangle.\n    param Outline :    Outline width (0 by default).\n\
    param OutlineCol : Color used to draw the outline (black by default)."},
	{"Circle", (PyCFunction)PySfShape_Circle, METH_STATIC | METH_VARARGS | METH_KEYWORDS, "Circle(X, Y, Radius, Col, Outline = 0., OutlineCol = sf.Color(0, 0, 0))\n\n\
Create a shape made of a single circle.\n\
    param X :          X coordinate of the center.\n    param Y :          Y coordinate of the center.\n    param Radius :     Radius\n\
    param Col :        Color used to fill the rectangle.\n    param Outline :    Outline width (0 by default).\n\
    param OutlineCol : Color used to draw the outline (black by default)."},
	{NULL}  /* Sentinel */
};


PyTypeObject PySfShapeType = {
	PyObject_HEAD_INIT(NULL)
	0,                         /*ob_size*/
	"Shape",             /*tp_name*/
	sizeof(PySfShape),             /*tp_basicsize*/
	0,                         /*tp_itemsize*/
	(destructor)PySfShape_dealloc, /*tp_dealloc*/
	0,                         /*tp_print*/
	0,                         /*tp_getattr*/
	0,                         /*tp_setattr*/
	0,                         /*tp_compare*/
	0,                         /*tp_repr*/
	0,                         /*tp_as_number*/
	0,                         /*tp_as_sequence*/
	0,                         /*tp_as_mapping*/
	0,                         /*tp_hash */
	0,                         /*tp_call*/
	0,                         /*tp_str*/
	0,                         /*tp_getattro*/
	0,                         /*tp_setattro*/
	0,                         /*tp_as_buffer*/
	Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /*tp_flags*/
	"Shape defines a drawable convex shape ; it also defines helper functions to draw simple shapes like lines, rectangles, circles, etc.", /* tp_doc */
	0,		               /* tp_traverse */
	0,		               /* tp_clear */
	0,		               /* tp_richcompare */
	0,		               /* tp_weaklistoffset */
	0,		               /* tp_iter */
	0,		               /* tp_iternext */
	PySfShape_methods,             /* tp_methods */
	PySfShape_members,             /* tp_members */
	0,                         /* tp_getset */
	0,                         /* tp_base */
	0,                         /* tp_dict */
	0,                         /* tp_descr_get */
	0,                         /* tp_descr_set */
	0,                         /* tp_dictoffset */
	(initproc)PySfShape_init,      /* tp_init */
	0,                         /* tp_alloc */
	PySfShape_new,                 /* tp_new */
};


PySfShape *
GetNewPySfShape()
{
	return PyObject_New(PySfShape, &PySfShapeType);
}

