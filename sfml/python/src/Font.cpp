#include "Font.hpp"

static PyMemberDef PySfFont_members[] = {
	{NULL}  /* Sentinel */
};



static void
PySfFont_dealloc(PySfFont *self)
{
	self->ob_type->tp_free((PyObject*)self);
}

static PyObject *
PySfFont_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
	PySfFont *self;

	self = (PySfFont *)type->tp_alloc(type, 0);

	if (self != NULL)
	{
	}

	return (PyObject *)self;
}

static int
PySfFont_init(PySfFont *self, PyObject *args, PyObject *kwds)
{
	self->obj = new sf::Font();
	return 0;
}

static PyObject *
PySfFont_LoadFromFile(PySfFont* self, PyObject *args)
{
	unsigned int Charsize=30;
	char *Filename;
	std::wstring Charset = L"";

	if (! PyArg_ParseTuple(args, "s|Is", &Filename, &Charsize, &Charset))
		return NULL;

	if (self->obj->LoadFromFile(Filename, Charsize, Charset))
		Py_RETURN_TRUE;
	else
		Py_RETURN_FALSE;
}

static PyObject *
PySfFont_LoadFromMemory(PySfFont* self, PyObject *args)
{
	unsigned int Charsize=30, Size;
	char *Data;
	std::wstring Charset = L"";

	if (! PyArg_ParseTuple(args, "s#|Is", &Data, &Size, &Charsize, &Charset))
		return NULL;

	if (self->obj->LoadFromMemory(Data, Size, Charsize, Charset))
		Py_RETURN_TRUE;
	else
		Py_RETURN_FALSE;
}

static PyObject *
PySfFont_GetDefaultFont(PySfFont* self, PyObject *args)
{
	PySfFont *Font = GetNewPySfFont();
	Font->obj = new sf::Font(self->obj->GetDefaultFont());
	return (PyObject *)Font;
}

static PyMethodDef PySfFont_methods[] = {
	{"LoadFromFile", (PyCFunction)PySfFont_LoadFromFile, METH_VARARGS, "Load the font from a file.\nparam Filename : Font file to load\nparam CharSize : Size of characters in bitmap - the bigger, the higher quality (30 by default)\nparam Charset :  Characters set to generate (empty by default - takes the ASCII range [31, 255])\nreturn True if loading was successful."},
	{"LoadFromMemory", (PyCFunction)PySfFont_LoadFromMemory, METH_VARARGS, "Load the font from a file in memory.\nparam Data : data to load\nparam SizeInBytes : Size of the data, in bytes\nparam CharSize : Size of characters in bitmap - the bigger, the higher quality (30 by default)\nparam Charset : Characters set to generate (empty by default - takes the ASCII range [31, 255])\nreturn True if loading was successful."},
	{"GetDefaultFont", (PyCFunction)PySfFont_GetDefaultFont, METH_NOARGS | METH_STATIC, "Get the SFML default built-in font (Arial)."},
	{NULL}  /* Sentinel */
};


PyTypeObject PySfFontType = {
	PyObject_HEAD_INIT(NULL)
	0,                         /*ob_size*/
	"Font",             /*tp_name*/
	sizeof(PySfFont),             /*tp_basicsize*/
	0,                         /*tp_itemsize*/
	(destructor)PySfFont_dealloc, /*tp_dealloc*/
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
	"sf.Font is the low-level class for loading and manipulating character fonts. This class is meant to be used by sf.Font.",           /* tp_doc */
	0,		               /* tp_traverse */
	0,		               /* tp_clear */
	0,		               /* tp_richcompare */
	0,		               /* tp_weaklistoffset */
	0,		               /* tp_iter */
	0,		               /* tp_iternext */
	PySfFont_methods,             /* tp_methods */
	PySfFont_members,             /* tp_members */
	0,                         /* tp_getset */
	0,                         /* tp_base */
	0,                         /* tp_dict */
	0,                         /* tp_descr_get */
	0,                         /* tp_descr_set */
	0,                         /* tp_dictoffset */
	(initproc)PySfFont_init,      /* tp_init */
	0,                         /* tp_alloc */
	PySfFont_new,                 /* tp_new */
};

PySfFont *
GetNewPySfFont()
{
	return PyObject_New(PySfFont, &PySfFontType);
}


