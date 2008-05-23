#include "Drawable.hpp"

void CustomDrawable::Render (const sf::RenderWindow& Window) const
{
	if (RenderFunction)
		PyObject_CallFunction(RenderFunction, "O", RenderWindow);
}


extern PyTypeObject PySfColorType;

static PyMemberDef PySfDrawable_members[] = {
	{NULL}  /* Sentinel */
};



static void
PySfDrawable_dealloc(PySfDrawable *self)
{
	delete self->obj;
	self->ob_type->tp_free((PyObject*)self);
}

static PyObject *
PySfDrawable_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
	PySfDrawable *self;

	self = (PySfDrawable *)type->tp_alloc(type, 0);

	if (self != NULL)
	{
	}

	return (PyObject *)self;
}


static int
PySfDrawable_init(PySfDrawable *self, PyObject *args, PyObject *kwds)
{
	self->obj = new CustomDrawable();
	return 0;
}
static PyObject *
PySfDrawable_SetX(PySfDrawable* self, PyObject *args)
{
	self->obj->SetX(PyFloat_AsDouble(args));
	Py_RETURN_NONE;
}
static PyObject *
PySfDrawable_SetY(PySfDrawable* self, PyObject *args)
{
	self->obj->SetY(PyFloat_AsDouble(args));
	Py_RETURN_NONE;
}
static PyObject *
PySfDrawable_SetScale(PySfDrawable* self, PyObject *args)
{
	float ScaleX, ScaleY;
	if ( !PyArg_ParseTuple(args, "ff", &ScaleX, &ScaleY) )
		return NULL;
	self->obj->SetScale(ScaleX, ScaleY);
	Py_RETURN_NONE;
}
static PyObject *
PySfDrawable_SetScaleX(PySfDrawable* self, PyObject *args)
{
	self->obj->SetScaleX(PyFloat_AsDouble(args));
	Py_RETURN_NONE;
}
static PyObject *
PySfDrawable_SetScaleY(PySfDrawable* self, PyObject *args)
{
	self->obj->SetScaleY(PyFloat_AsDouble(args));
	Py_RETURN_NONE;
}

static PyObject *
PySfDrawable_SetRotation(PySfDrawable* self, PyObject *args)
{
	self->obj->SetRotation(PyFloat_AsDouble(args));
	Py_RETURN_NONE;
}
static PyObject *
PySfDrawable_SetCenter(PySfDrawable* self, PyObject *args)
{
	float x, y;
	if ( !PyArg_ParseTuple(args, "ff", &x, &y) )
		return NULL;
	self->obj->SetCenter(x, y);
	Py_RETURN_NONE;
}
static PyObject *
PySfDrawable_GetCenter(PySfDrawable* self)
{
	sf::Vector2f Vect = self->obj->GetCenter();
	return Py_BuildValue("ff", Vect.x, Vect.y);
}

static PyObject *
PySfDrawable_SetColor(PySfDrawable* self, PyObject *args)
{
	PySfColor *Color = (PySfColor *)args;
	if (! PyObject_TypeCheck(args, &PySfColorType))
	{
		PyErr_SetString(PyExc_TypeError, "Argument is not a sfColor");
		return NULL;
	}
	self->obj->SetColor(*(Color->obj));
	Py_RETURN_NONE;
}
static PyObject *
PySfDrawable_GetPosition(PySfDrawable* self)
{
	sf::Vector2f Vect = self->obj->GetPosition();
	return Py_BuildValue("ff", Vect.x, Vect.y);
}
static PyObject *
PySfDrawable_GetScale(PySfDrawable* self)
{
	sf::Vector2f Vect = self->obj->GetScale();
	return Py_BuildValue("ff", Vect.x, Vect.y);
}
static PyObject *
PySfDrawable_GetRotation(PySfDrawable* self)
{
	return PyFloat_FromDouble(self->obj->GetRotation());
}

static PyObject *
PySfDrawable_GetColor(PySfDrawable* self)
{
	PySfColor *Color;

	Color = GetNewPySfColor();
	Color->obj = new sf::Color( self->obj->GetColor() );
	Color->r = Color->obj->r;
	Color->g = Color->obj->g;
	Color->b = Color->obj->b;
	Color->a = Color->obj->a;

	return (PyObject *)Color;
}
static PyObject *
PySfDrawable_Move(PySfDrawable* self, PyObject *args)
{
	float x, y;
	if ( !PyArg_ParseTuple(args, "ff", &x, &y) )
		return NULL;
	self->obj->Move(x, y);
	Py_RETURN_NONE;
}
static PyObject *
PySfDrawable_Rotate(PySfDrawable* self, PyObject *args)
{
	self->obj->Rotate(PyFloat_AsDouble(args));
	Py_RETURN_NONE;
}
static PyObject *
PySfDrawable_Scale(PySfDrawable* self, PyObject *args)
{
	float FactorX, FactorY;
	if ( !PyArg_ParseTuple(args, "ff", &FactorX, &FactorY) )
		return NULL;
	self->obj->Scale(FactorX, FactorY);
	Py_RETURN_NONE;
}

static PyObject *
PySfDrawable_SetBlendMode(PySfDrawable* self, PyObject *args)
{
	self->obj->SetBlendMode((sf::Blend::Mode)PyLong_AsUnsignedLong(args));
	Py_RETURN_NONE;
}

static PyObject *
PySfDrawable_SetPosition(PySfDrawable* self, PyObject *args)
{
	float Left, Top;
	if ( !PyArg_ParseTuple(args, "ff", &Left, &Top) )
		return NULL;
	self->obj->SetPosition(Left, Top);
	Py_RETURN_NONE;
}

static PyMethodDef PySfDrawable_methods[] = {
	{"SetX", (PyCFunction)PySfDrawable_SetX, METH_O, "Set the X position of the object."},
	{"SetY", (PyCFunction)PySfDrawable_SetY, METH_O, "Set the Y position of the object."},
	{"SetScale", (PyCFunction)PySfDrawable_SetScale, METH_VARARGS, "Set the uniform scale of the object."},
	{"SetScaleX", (PyCFunction)PySfDrawable_SetScaleX, METH_O, "Set the scale of the object."},
	{"SetScaleY", (PyCFunction)PySfDrawable_SetScaleY, METH_O, "Set the scale of the object."},
	{"SetRotation", (PyCFunction)PySfDrawable_SetRotation, METH_O, "Set the orientation of the object."},
	{"SetCenter", (PyCFunction)PySfDrawable_SetCenter, METH_VARARGS, "Set the center of the object, in coordinates relative to the object."},
	{"GetCenter", (PyCFunction)PySfDrawable_GetCenter, METH_NOARGS, "Get the center of the object, in coordinates relative to the object."},
	{"SetColor", (PyCFunction)PySfDrawable_SetColor, METH_O, "Set the color of the object."},
	{"GetPosition", (PyCFunction)PySfDrawable_GetPosition, METH_NOARGS, "Get the position of the object."},
	{"GetScale", (PyCFunction)PySfDrawable_GetScale, METH_NOARGS, "Get the scale of the object."},
	{"GetRotation", (PyCFunction)PySfDrawable_GetRotation, METH_NOARGS, "Get the orientation of the object."},
	{"GetColor", (PyCFunction)PySfDrawable_GetColor, METH_NOARGS, "Get the color of the object."},
	{"Move", (PyCFunction)PySfDrawable_Move, METH_VARARGS, "Move the object."},
	{"Scale", (PyCFunction)PySfDrawable_Scale, METH_VARARGS, "Scale the object."},
	{"Rotate", (PyCFunction)PySfDrawable_Rotate, METH_O, "Rotate the object."},
	{"SetBlendMode", (PyCFunction)PySfDrawable_SetBlendMode, METH_O, "Set the blending mode for the object."},
	{"SetPosition", (PyCFunction)PySfDrawable_SetPosition, METH_VARARGS, "Set the position of the object."},
	{NULL}  /* Sentinel */
};

PyTypeObject PySfDrawableType = {
	PyObject_HEAD_INIT(NULL)
	0,						/*ob_size*/
	"Drawable",				/*tp_name*/
	sizeof(PySfDrawable),	/*tp_basicsize*/
	0,						/*tp_itemsize*/
	(destructor)PySfDrawable_dealloc, /*tp_dealloc*/
	0,						/*tp_print*/
	0,						/*tp_getattr*/
	0,						/*tp_setattr*/
	0,						/*tp_compare*/
	0,						/*tp_repr*/
	0,						/*tp_as_number*/
	0,						/*tp_as_sequence*/
	0,						/*tp_as_mapping*/
	0,						/*tp_hash */
	0,						/*tp_call*/
	0,						/*tp_str*/
	0,						/*tp_getattro*/
	0,						/*tp_setattro*/
	0,						/*tp_as_buffer*/
	Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /*tp_flags*/
	"sfDrawable defines a sprite : texture, transformations, color, and draw on screen", /* tp_doc */
	0,						/* tp_traverse */
	0,						/* tp_clear */
	0,						/* tp_richcompare */
	0,						/* tp_weaklistoffset */
	0,						/* tp_iter */
	0,						/* tp_iternext */
	PySfDrawable_methods,	/* tp_methods */
	PySfDrawable_members,	/* tp_members */
	0,						/* tp_getset */
	0,						/* tp_base */
	0,						/* tp_dict */
	0,						/* tp_descr_get */
	0,						/* tp_descr_set */
	0,						/* tp_dictoffset */
	(initproc)PySfDrawable_init, /* tp_init */
	0,						/* tp_alloc */
	PySfDrawable_new,		/* tp_new */
};


