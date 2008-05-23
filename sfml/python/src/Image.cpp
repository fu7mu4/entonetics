#include "Image.hpp"

extern PyTypeObject PySfColorType;
extern PyTypeObject PySfIntRectType;

static PyMemberDef PySfImage_members[] = {
	{NULL}  /* Sentinel */
};


static void
PySfImage_dealloc(PySfImage* self)
{
	delete self->obj;
	self->ob_type->tp_free((PyObject*)self);
}

static PyObject *
PySfImage_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
	PySfImage *self;

	self = (PySfImage *)type->tp_alloc(type, 0);

	if (self != NULL)
	{
	}

	return (PyObject *)self;
}


static PyObject *
PySfImage_Create(PySfImage* self, PyObject *args, PyObject *kwds)
{
	PySfColor *ColorTmp=NULL;
	sf::Color *Color;
	unsigned int Width=0, Height=0;
	char *kwlist[] = {"Width", "Height", "Color", NULL};


	if (! PyArg_ParseTupleAndKeywords(args, kwds, "|IIO!", kwlist, &Width, &Height, &PySfColorType, &ColorTmp))
		return NULL; 


	if (ColorTmp)
	{
		Color = ColorTmp->obj;
		PySfColorUpdate(ColorTmp);
		self->obj->Create(Width, Height, *Color);
	}
	else
		self->obj->Create(Width, Height);

	Py_RETURN_NONE;
}

static PyObject *
PySfImage_Resize(PySfImage* self, PyObject *args, PyObject *kwds)
{
	PySfColor *ColorTmp=NULL;
	sf::Color *Color;
	unsigned int Width=0, Height=0;
	char *kwlist[] = {"Width", "Height", "Color", NULL};


	if (! PyArg_ParseTupleAndKeywords(args, kwds, "II|O!", kwlist, &Width, &Height, &PySfColorType, &ColorTmp))
		return NULL; 


	if (ColorTmp)
	{
		Color = ColorTmp->obj;
		PySfColorUpdate(ColorTmp);
		self->obj->Resize(Width, Height, *Color);
	}
	else
		self->obj->Resize(Width, Height);

	Py_RETURN_NONE;
}

static PyObject *
PySfImage_SetPixel(PySfImage* self, PyObject *args, PyObject *kwds)
{
	PySfColor *ColorTmp=NULL;
	sf::Color *Color;
	unsigned int x=0, y=0;
	char *kwlist[] = {"x", "y", "Color", NULL};


	if (! PyArg_ParseTupleAndKeywords(args, kwds, "II|O!", kwlist, &x, &y, &PySfColorType, &ColorTmp))
		return NULL; 


	if (ColorTmp)
	{
		Color = ColorTmp->obj;
		PySfColorUpdate(ColorTmp);
		self->obj->SetPixel(x, y, *Color);
	}

	Py_RETURN_NONE;
}

static PyObject *
PySfImage_GetPixel(PySfImage* self, PyObject *args, PyObject *kwds)
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
PySfImage_CreateMaskFromColor(PySfImage* self, PyObject *args)
{
	PySfColor *ColorTmp= (PySfColor *)args;
	sf::Color *Color;

	if ( ! PyObject_TypeCheck(ColorTmp, &PySfColorType))
		PyErr_SetString(PyExc_ValueError, "Argument must be a sf.Color");
	Color = ColorTmp->obj;
	PySfColorUpdate(ColorTmp);
	self->obj->CreateMaskFromColor(*Color);

	Py_RETURN_NONE;
}

static PyObject *
PySfImage_LoadFromMemory(PySfImage* self, PyObject *args)
{
	unsigned int SizeInBytes;
	char *Data;

	if (! PyArg_ParseTuple(args, "s#", &Data, &SizeInBytes))
		return NULL; 

	if (self->obj->LoadFromMemory(Data, (std::size_t) SizeInBytes))
		Py_RETURN_TRUE;
	else
		Py_RETURN_FALSE;

}

static PyObject *
PySfImage_LoadFromPixels(PySfImage* self, PyObject *args)
{
	unsigned int Width, Height, Size;
	char *Data;

	if (! PyArg_ParseTuple(args, "IIs#", &Width, &Height, &Data, &Size))
		return NULL; 

	self->obj->LoadFromPixels(Width, Height, (sf::Uint8*) Data);
	Py_RETURN_NONE;
}

static PyObject *
PySfImage_GetPixelsBuffer(PySfImage *self)
{
	return PyBuffer_FromMemory((void *)(self->obj->GetPixelsPtr()), self->obj->GetWidth()*self->obj->GetHeight()*4);
}

static PyObject *
PySfImage_GetPixelsPtr(PySfImage *self)
{
	return PyCObject_FromVoidPtr((void *)(self->obj->GetPixelsPtr()), NULL);
}

static PyObject *
PySfImage_GetPixelsString(PySfImage *self)
{
	return PyString_FromStringAndSize((const char *)(self->obj->GetPixelsPtr()), self->obj->GetWidth()*self->obj->GetHeight()*4);
}

static PyObject *
PySfImage_LoadFromFile (PySfImage *self, PyObject *args)
{
	char *path = PyString_AsString(args);

	if (self->obj->LoadFromFile(path))
		Py_RETURN_TRUE;
	else
		Py_RETURN_FALSE;
}

static PyObject *
PySfImage_SaveToFile (PySfImage *self, PyObject *args)
{
	char *path = PyString_AsString(args);

	if (self->obj->SaveToFile(path))
		Py_RETURN_TRUE;
	else
		Py_RETURN_FALSE;
}

static int
PySfImage_init(PySfImage *self, PyObject *args, PyObject *kwds)
{
	self->obj = new sf::Image();
	PySfImage_Create(self, args, kwds);
	return 0;
}

static PyObject *
PySfImage_Bind(PySfImage *self)
{
	self->obj->Bind();
	Py_RETURN_NONE;
}

static PyObject *
PySfImage_SetSmooth (PySfImage *self, PyObject *args)
{
	bool arg=false;
	if (args == Py_True)
		arg = true;
	self->obj->SetSmooth(arg);
	Py_RETURN_NONE;
}

static PyObject *
PySfImage_GetWidth(PySfImage *self)
{
	return PyLong_FromUnsignedLong(self->obj->GetWidth());
}

static PyObject *
PySfImage_GetHeight(PySfImage *self)
{
	return PyLong_FromUnsignedLong(self->obj->GetHeight());
}

static PyObject *
PySfImage_GetValidTextureSize(PySfImage* self, PyObject *args)
{
	unsigned long S = PyLong_AsUnsignedLong(args);
	return PyLong_FromUnsignedLong(sf::Image::GetValidTextureSize(S));
}

static PyObject *
PySfImage_GetTexCoords(PySfImage* self, PyObject *args)
{
	PySfIntRect *RectArg = NULL;
	bool Adjust = true;
	PyObject *AdjustObj = NULL;

	if (! PyArg_ParseTuple(args, "O!|O", &PySfIntRectType, &RectArg, &AdjustObj))

	if (AdjustObj == Py_False)
		Adjust = false;

	PySfFloatRect *Rect;

	Rect = GetNewPySfFloatRect();
	Rect->obj = new sf::FloatRect ( self->obj->GetTexCoords(*(RectArg->obj), Adjust) );
	Rect->Left = Rect->obj->Left;
	Rect->Top = Rect->obj->Top;
	Rect->Right = Rect->obj->Right;
	Rect->Bottom = Rect->obj->Bottom;

	return (PyObject *)Rect;
}

static PyMethodDef PySfImage_methods[] = {
	{"Create", (PyCFunction)PySfImage_Create, METH_VARARGS | METH_KEYWORDS, "Create an empty image."},
	{"Resize", (PyCFunction)PySfImage_Resize, METH_VARARGS | METH_KEYWORDS, "Resize the image - warning : this function does not scale the image, it just ajdusts size (add padding or remove pixels)."},
	{"SetPixel", (PyCFunction)PySfImage_SetPixel, METH_VARARGS | METH_KEYWORDS, "Change the color of a pixel Don't forget to call Update when you end modifying pixels."},
	{"GetPixel", (PyCFunction)PySfImage_GetPixel, METH_VARARGS | METH_KEYWORDS, "Get a pixel from the image."},
	{"LoadFromFile", (PyCFunction)PySfImage_LoadFromFile, METH_O, "Load the surface from a file."},
	{"SaveToFile", (PyCFunction)PySfImage_SaveToFile, METH_O, "Save the content of the image to a file."},
	{"LoadFromMemory", (PyCFunction)PySfImage_LoadFromMemory, METH_VARARGS, "Load the image from pixels in memory."},
	{"LoadFromPixels", (PyCFunction)PySfImage_LoadFromPixels, METH_VARARGS, "Load the image directly from an array of pixels."},
	{"GetPixelsPtr", (PyCFunction)PySfImage_GetPixelsPtr, METH_NOARGS, "Get a read-only pointer to the array of pixels (8 bits integers RGBA) Array size is GetWidth() x GetHeight() x 4. This pointer becomes invalid if you reload or resize the image. Returns a CType pointer."},
	{"GetPixelsBuffer", (PyCFunction)PySfImage_GetPixelsBuffer, METH_NOARGS, "Same as GetPixelsPtr, but creates a buffer out of pixels data."},
	{"GetPixelsString", (PyCFunction)PySfImage_GetPixelsString, METH_NOARGS, "Same as GetPixelsPtr, but creates a string out of pixels data."},
	{"CreateMaskFromColor", (PyCFunction)PySfImage_CreateMaskFromColor, METH_O, "Create transparency mask from a specified colorkey."},
	{"Bind", (PyCFunction)PySfImage_Bind, METH_NOARGS, "Bind the image for rendering."},
	{"SetSmooth", (PyCFunction)PySfImage_SetSmooth, METH_VARARGS, "Enable or disable image smooth filter."},
	{"GetWidth", (PyCFunction)PySfImage_GetWidth, METH_NOARGS, "Return the width of the image."},
	{"GetHeight", (PyCFunction)PySfImage_GetHeight, METH_NOARGS, "Return the height of the image."},
	{"GetTexCoords", (PyCFunction)PySfImage_GetTexCoords, METH_VARARGS, "Convert a subrect expressed in pixels, into float texture coordinates."},
	{"GetValidTextureSize", (PyCFunction)PySfImage_GetValidTextureSize, METH_STATIC | METH_O, "Get a valid texture size according to hardware support."},
	{NULL}  /* Sentinel */
};

PyTypeObject PySfImageType = {
	PyObject_HEAD_INIT(NULL)
	0,                         /*ob_size*/
	"Image",             /*tp_name*/
	sizeof(PySfImage),             /*tp_basicsize*/
	0,                         /*tp_itemsize*/
	(destructor)PySfImage_dealloc, /*tp_dealloc*/
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
	"sfImage is the low-level class for loading and manipulating images",           /* tp_doc */
	0,		               /* tp_traverse */
	0,		               /* tp_clear */
	0,		               /* tp_richcompare */
	0,		               /* tp_weaklistoffset */
	0,		               /* tp_iter */
	0,		               /* tp_iternext */
	PySfImage_methods,             /* tp_methods */
	PySfImage_members,             /* tp_members */
	0,                         /* tp_getset */
	0,                         /* tp_base */
	0,                         /* tp_dict */
	0,                         /* tp_descr_get */
	0,                         /* tp_descr_set */
	0,                         /* tp_dictoffset */
	(initproc)PySfImage_init,      /* tp_init */
	0,                         /* tp_alloc */
	PySfImage_new,                 /* tp_new */
};

PySfImage *
GetNewPySfImage()
{
	return PyObject_New(PySfImage, &PySfImageType);
}

