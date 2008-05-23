#include "Sprite.hpp"


extern PyTypeObject PySfColorType;
extern PyTypeObject PySfImageType;
extern PyTypeObject PySfIntRectType;
extern PyTypeObject PySfDrawableType;

static PyMemberDef PySfSprite_members[] = {
	{NULL}  /* Sentinel */
};



static void
PySfSprite_dealloc(PySfSprite *self)
{
	Py_DECREF(self->Image);
	delete self->obj;
	self->ob_type->tp_free((PyObject*)self);
}

static PyObject *
PySfSprite_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
	PySfSprite *self;

	self = (PySfSprite *)type->tp_alloc(type, 0);

	if (self != NULL)
	{
		self->Image = NULL;
	}

	return (PyObject *)self;
}


static int
PySfSprite_init(PySfSprite *self, PyObject *args, PyObject *kwds)
{
	char *kwlist[] = {"Image", "X", "Y", "ScaleX", "ScaleY", "Rotation", "Color", NULL};
	float X=0, Y=0, ScaleX=1, ScaleY=1, Rotation=0;
	PySfImage *Image=NULL;
	PySfColor *Color=NULL;

	if (! PyArg_ParseTupleAndKeywords(args, kwds, "O!|fffffO!", kwlist, &PySfImageType, &Image, &X, &Y, &ScaleX, &ScaleY, &Rotation, &PySfColorType, &Color))
		return -1;

	Py_INCREF(Image);
	self->Image = Image;
	if (Color != NULL)
		self->obj = new sf::Sprite(*(Image->obj), sf::Vector2f(X, Y), sf::Vector2f(ScaleX, ScaleY), Rotation, *(Color->obj));
	else
		self->obj = new sf::Sprite(*(Image->obj), sf::Vector2f(X, Y), sf::Vector2f(ScaleX, ScaleY), Rotation);


	return 0;
}



static PyObject *
PySfSprite_SetImage(PySfSprite* self, PyObject *args)
{
	PySfImage *Image = (PySfImage *)args;
	if (! PyObject_TypeCheck(Image, &PySfImageType))
	{
		PyErr_SetString(PyExc_TypeError, "Argument is not a sfImage");
		return NULL;
	}
	Py_DECREF(self->Image);
	Py_INCREF(Image);
	self->Image = Image;
	self->obj->SetImage(*(Image->obj));
	Py_RETURN_NONE;
}

static PyObject *
PySfSprite_GetImage(PySfSprite* self)
{
	Py_INCREF(self->Image);
	return (PyObject *)(self->Image);
}

static PyObject *
PySfSprite_GetPixel(PySfSprite* self, PyObject *args, PyObject *kwds)
{
	PySfColor *Color;
	unsigned int x=0, y=0;
	char *kwlist[] = {"x", "y", NULL};


	if (! PyArg_ParseTupleAndKeywords(args, kwds, "II", kwlist, &x, &y))
		return NULL; 

	Color = GetNewPySfColor();
	Color->obj = new sf::Color(self->obj->GetPixel(x, y));
	Color->r = Color->obj->r;
	Color->g = Color->obj->g;
	Color->b = Color->obj->b;
	Color->a = Color->obj->a;

	return (PyObject *)Color;
}

static PyObject *
PySfSprite_Resize(PySfSprite* self, PyObject *args)
{
	float W=0, H=0;

	if (! PyArg_ParseTuple(args, "ff", &W, &H))
		return NULL; 

	self->obj->Resize(W,H);
	Py_RETURN_NONE;
}

static PyObject *
PySfSprite_GetSubRect(PySfSprite* self)
{
	PySfIntRect *Rect;

	Rect = GetNewPySfIntRect();
	Rect->obj = new sf::IntRect(self->obj->GetSubRect());
	Rect->Left = Rect->obj->Left;
	Rect->Top = Rect->obj->Top;
	Rect->Right = Rect->obj->Right;
	Rect->Bottom = Rect->obj->Bottom;

	return (PyObject *)Rect;
}

static PyObject *
PySfSprite_SetSubRect(PySfSprite* self, PyObject *args)
{
	PySfIntRect *Rect = (PySfIntRect *)args;
	if (! PyObject_TypeCheck(Rect, &PySfIntRectType))
	{
		PyErr_SetString(PyExc_TypeError, "Argument is not a sfIntRect");
		return NULL;
	}
	self->obj->SetSubRect(*(Rect->obj));
	Py_RETURN_NONE;
}

static PyObject *
PySfSprite_FlipX(PySfSprite* self, PyObject *args)
{
	bool Flip = true;
	if (args == Py_False)
		Flip = false;
	self->obj->FlipX(Flip);
	Py_RETURN_NONE;
}

static PyObject *
PySfSprite_FlipY(PySfSprite* self, PyObject *args)
{
	bool Flip = true;
	if (args == Py_False)
		Flip = false;
	self->obj->FlipY(Flip);
	Py_RETURN_NONE;
}

static PyObject *
PySfSprite_GetSize(PySfSprite* self)
{
	sf::Vector2f Vect = self->obj->GetSize();
	return Py_BuildValue("ff", Vect.x, Vect.y);
}

static PyMethodDef PySfSprite_methods[] = {
	{"SetImage", (PyCFunction)PySfSprite_SetImage, METH_O, "Change the image of the sprite."},
	{"GetImage", (PyCFunction)PySfSprite_GetImage, METH_NOARGS, "Get the source image of the sprite."},
	{"GetSize", (PyCFunction)PySfSprite_GetSize, METH_NOARGS, "Get the sprite's size."},
	{"GetPixel", (PyCFunction)PySfSprite_GetPixel, METH_VARARGS | METH_KEYWORDS, "Get the color of a given pixel in the sprite."},
	{"Resize", (PyCFunction)PySfSprite_Resize, METH_VARARGS, "Resize the object (by changing its scale factors)."},
	{"GetSubRect", (PyCFunction)PySfSprite_GetSubRect, METH_NOARGS, "Get the sub-rectangle of the sprite inside the source image."},
	{"SetSubRect", (PyCFunction)PySfSprite_SetSubRect, METH_O, "Set the sub-rectangle of the sprite inside the source image."},
	{"FlipX", (PyCFunction)PySfSprite_FlipX, METH_O, "Flip the sprite horizontally."},
	{"FlipY", (PyCFunction)PySfSprite_FlipY, METH_O, "Flip the sprite vertically."},
	{NULL}  /* Sentinel */
};

PyTypeObject PySfSpriteType = {
	PyObject_HEAD_INIT(NULL)
	0,						/*ob_size*/
	"Sprite",				/*tp_name*/
	sizeof(PySfSprite),		/*tp_basicsize*/
	0,						/*tp_itemsize*/
	(destructor)PySfSprite_dealloc, /*tp_dealloc*/
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
	"sfSprite defines a sprite : texture, transformations, color, and draw on screen", /* tp_doc */
	0,						/* tp_traverse */
	0,						/* tp_clear */
	0,						/* tp_richcompare */
	0,						/* tp_weaklistoffset */
	0,						/* tp_iter */
	0,						/* tp_iternext */
	PySfSprite_methods,		/* tp_methods */
	PySfSprite_members,		/* tp_members */
	0,						/* tp_getset */
	&PySfDrawableType,		/* tp_base */
	0,						/* tp_dict */
	0,						/* tp_descr_get */
	0,						/* tp_descr_set */
	0,						/* tp_dictoffset */
	(initproc)PySfSprite_init, /* tp_init */
	0,						/* tp_alloc */
	PySfSprite_new,			/* tp_new */
};


