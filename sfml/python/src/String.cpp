#include "String.hpp"
#include "Font.hpp"
#include "Color.hpp"
#include "Rect.hpp"


extern PyTypeObject PySfColorType;
extern PyTypeObject PySfImageType;
extern PyTypeObject PySfDrawableType;
extern PyTypeObject PySfFontType;

static PyMemberDef PySfString_members[] = {
    {NULL}  /* Sentinel */
};



static void
PySfString_dealloc(PySfString *self)
{
	delete self->obj;
	self->ob_type->tp_free((PyObject*)self);
}

static PyObject *
PySfString_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
	PySfString *self;

	self = (PySfString *)type->tp_alloc(type, 0);

	if (self != NULL)
	{
	}

	return (PyObject *)self;
}


static int
PySfString_init(PySfString *self, PyObject *args, PyObject *kwds)
{
	char *kwlist[] = {"Text", "Font", "Size", NULL};
	float Size = 30.f;
	std::string Text = "";
	PySfFont *FontTmp = NULL;
	sf::Font *Font = (sf::Font *)&(sf::Font::GetDefaultFont());

	if (! PyArg_ParseTupleAndKeywords(args, kwds, "|sO!f", kwlist, &Text, &PySfFontType, &FontTmp, &Size))
		return -1;

	if (FontTmp)
		Font = (FontTmp->obj);

	self->obj = new sf::String(*(new std::string(Text)), *Font, Size);
	return 0;
}



static PyObject *
PySfString_SetText(PySfString* self, PyObject *args)
{
	self->obj->SetText(PyString_AsString(args));
	Py_RETURN_NONE;
}

static PyObject *
PySfString_SetFont(PySfString* self, PyObject *args)
{
	PySfFont *Font = (PySfFont *)args;
	if (!PyObject_TypeCheck(Font, &PySfFontType))
		PyErr_SetString(PyExc_ValueError, "Argument must be a sf.Font");
	self->obj->SetFont(*(Font->obj));
	Py_RETURN_NONE;
}

static PyObject *
PySfString_SetSize(PySfString* self, PyObject *args)
{
	self->obj->SetSize(PyFloat_AsDouble(args));
	Py_RETURN_NONE;
}

static PyObject *
PySfString_GetSize(PySfString* self)
{
	return PyFloat_FromDouble(self->obj->GetSize());
}

static PyObject *
PySfString_SetStyle(PySfString* self, PyObject *args)
{
	self->obj->SetStyle(PyLong_AsUnsignedLong(args));
	Py_RETURN_NONE;
}

static PyObject *
PySfString_GetStyle(PySfString* self)
{
	return PyLong_FromUnsignedLong(self->obj->GetStyle());
}

static PyObject *
PySfString_GetText(PySfString* self)
{
	return PyString_FromString((self->obj->GetText()).c_str());
}

static PyObject *
PySfString_GetFont(PySfString* self)
{
	PySfFont *Font = GetNewPySfFont();
	Font->obj = (sf::Font *) (&(self->obj->GetFont()));
	return (PyObject *)Font;
}

static PyObject *
PySfString_GetRect(PySfString* self)
{
	PySfFloatRect *Rect;

	Rect = GetNewPySfFloatRect();
	Rect->obj = new sf::FloatRect (self->obj->GetRect());
	Rect->Left = Rect->obj->Left;
	Rect->Top = Rect->obj->Top;
	Rect->Right = Rect->obj->Right;
	Rect->Bottom = Rect->obj->Bottom;

	return (PyObject *)Rect;
}


static PyMethodDef PySfString_methods[] = {
	{"SetText", (PyCFunction)PySfString_SetText, METH_O, "Set the text."},
	{"GetText", (PyCFunction)PySfString_GetText, METH_NOARGS, "Get the text."},
	{"SetFont", (PyCFunction)PySfString_SetFont, METH_O, "Set the font of the string."},
	{"GetFont", (PyCFunction)PySfString_GetFont, METH_NOARGS, "Get the font used by the string."},
	{"SetSize", (PyCFunction)PySfString_SetSize, METH_O, "Set the size of the string."},
	{"GetSize", (PyCFunction)PySfString_GetSize, METH_NOARGS, "Get the size of the characters."},
	{"SetStyle", (PyCFunction)PySfString_SetStyle, METH_O, "Set the style of the text. The default style is Regular."},
	{"GetStyle", (PyCFunction)PySfString_GetStyle, METH_NOARGS, "Get the style of the text."},
	{"GetRect", (PyCFunction)PySfString_GetRect, METH_NOARGS, "Get the string rectangle on screen."},
	{NULL}  /* Sentinel */
};

PyTypeObject PySfStringType = {
	PyObject_HEAD_INIT(NULL)
	0,                         /*ob_size*/
	"String",             /*tp_name*/
	sizeof(PySfString),             /*tp_basicsize*/
	0,                         /*tp_itemsize*/
	(destructor)PySfString_dealloc, /*tp_dealloc*/
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
	"sfString defines a string : texture, transformations, color, and draw on screen",           /* tp_doc */
	0,		               /* tp_traverse */
	0,		               /* tp_clear */
	0,		               /* tp_richcompare */
	0,		               /* tp_weaklistoffset */
	0,		               /* tp_iter */
	0,		               /* tp_iternext */
	PySfString_methods,             /* tp_methods */
	PySfString_members,             /* tp_members */
	0,                         /* tp_getset */
	&PySfDrawableType,                         /* tp_base */
	0,                         /* tp_dict */
	0,                         /* tp_descr_get */
	0,                         /* tp_descr_set */
	0,                         /* tp_dictoffset */
	(initproc)PySfString_init,      /* tp_init */
	0,                         /* tp_alloc */
	PySfString_new,                 /* tp_new */
};



void PySfString_InitConst()
{
	PyObject *obj;
	obj = PyInt_FromLong(sf::String::Regular);
	PyDict_SetItemString(PySfStringType.tp_dict, "Regular", obj);
	Py_DECREF(obj);
	obj = PyInt_FromLong(sf::String::Bold);
	PyDict_SetItemString(PySfStringType.tp_dict, "Bold", obj);
	Py_DECREF(obj);
	obj = PyInt_FromLong(sf::String::Italic);
	PyDict_SetItemString(PySfStringType.tp_dict, "Italic", obj);
	Py_DECREF(obj);
	obj = PyInt_FromLong(sf::String::Underlined);
	PyDict_SetItemString(PySfStringType.tp_dict, "Underlined", obj);
	Py_DECREF(obj);
}

