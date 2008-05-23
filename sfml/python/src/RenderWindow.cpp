#include "RenderWindow.hpp"

#include "Event.hpp"
#include "VideoMode.hpp"
#include "Drawable.hpp"
#include "Color.hpp"
#include "Rect.hpp"
#include "View.hpp"
#include "Image.hpp"

#include "SFML/Window/WindowStyle.hpp"


extern PyTypeObject PySfEventType;
extern PyTypeObject PySfViewType;
extern PyTypeObject PySfColorType;
extern PyTypeObject PySfWindowType;
extern PyTypeObject PySfWindowSettingsType;
extern PyTypeObject PySfVideoModeType;

static PyMemberDef PySfRenderWindow_members[] = {
	{NULL}  /* Sentinel */
};


static void
PySfRenderWindow_dealloc(PySfRenderWindow* self)
{
	delete self->obj;
	self->ob_type->tp_free((PyObject*)self);
}

static PyObject *
PySfRenderWindow_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
	PySfRenderWindow *self;

	self = (PySfRenderWindow *)type->tp_alloc(type, 0);
	if (self != NULL)
	{
	}

	return (PyObject *)self;
}


static PyObject*
PySfRenderWindow_Create(PySfRenderWindow* self, PyObject *args, PyObject *kwds)
{
	PyObject *VideoModeTmp=NULL;
	sf::VideoMode *VideoMode;
	char *Title=NULL;
	unsigned long WindowStyle = sf::Style::Resize | sf::Style::Close;
	PySfWindowSettings *ParamsTmp=NULL;
	sf::WindowSettings *Params;

	char *kwlist[] = {"VideoMode", "Title", "WindowStyle", "Params", NULL};

	if (! PyArg_ParseTupleAndKeywords(args, kwds, "O!s|IO!", kwlist, &PySfVideoModeType, &VideoModeTmp, &Title, &WindowStyle, &PySfWindowSettingsType, &ParamsTmp))
		return NULL; 

	if (VideoModeTmp) {
		VideoMode = ((PySfVideoMode *)VideoModeTmp)->obj;
		PySfVideoModeUpdate((PySfVideoMode *)VideoModeTmp);
	}
	else
		return NULL;

	if (ParamsTmp)
		Params = ParamsTmp->obj;
	else
		Params = new sf::WindowSettings();

	self->obj->Create(*VideoMode, Title, WindowStyle, *Params);

	Py_RETURN_NONE;
}

static int
PySfRenderWindow_init(PySfRenderWindow *self, PyObject *args, PyObject *kwds)
{
	self->obj = new sf::RenderWindow();
	PySfRenderWindow_Create(self, args, kwds);
	return 0;
}


static PyObject *
PySfRenderWindow_Capture(PySfRenderWindow *self)
{
	PySfImage *Image;

	Image = GetNewPySfImage();
	Image->obj = new sf::Image(self->obj->Capture());
	return (PyObject *)Image;
}

static PyObject *
PySfRenderWindow_ConvertCoords(PySfRenderWindow *self, PyObject *args)
{
	unsigned int WindowX, WindowY;
	PySfView *PyTargetView = NULL;
	sf::View *TargetView = NULL;
	sf::Vector2f Vect;

	if (! PyArg_ParseTuple(args, "II|O!", &WindowX, &WindowY, &PySfViewType, &PyTargetView))
		return NULL;

	if (PyTargetView)
		TargetView = PyTargetView->obj;

	Vect = self->obj->ConvertCoords(WindowX, WindowY, TargetView);
	return Py_BuildValue("ff", Vect.x, Vect.y);
}

static PyObject *
PySfRenderWindow_Draw(PySfRenderWindow *self, PyObject *args)
{
	PySfDrawable *Drawable = (PySfDrawable *)args;

	if (!args)
		return NULL;

	if (PyObject_HasAttrString(args, "Render"))
	{
		Drawable->obj->RenderWindow = self;
		Drawable->obj->RenderFunction = PyObject_GetAttrString(args, "Render");
	}

	self->obj->Draw( *(Drawable->obj) );
	Py_RETURN_NONE;
}

static PyObject *
PySfRenderWindow_GetDefaultView(PySfRenderWindow *self)
{
	PySfView *View;

	View = GetNewPySfView();
	View->obj = &(self->obj->GetDefaultView());

	return (PyObject *)View;
}

static PyObject *
PySfRenderWindow_GetView(PySfRenderWindow *self)
{
	PySfView *View;

	View = GetNewPySfView();
	View->obj = new sf::View(self->obj->GetView());

	return (PyObject *)View;
}

static PyObject *
PySfRenderWindow_PreserveOpenGLStates(PySfRenderWindow *self, PyObject *args)
{
	bool Optimize = true;
	if (args == Py_False)
		Optimize = false;
	self->obj->PreserveOpenGLStates(Optimize);
	Py_RETURN_NONE;
}

static PyObject *
PySfRenderWindow_SetBackgroundColor(PySfRenderWindow* self, PyObject *args)
{
	PySfColor *Color = (PySfColor *)args;
	if (! PyObject_TypeCheck(Color, &PySfColorType))
	{
		PyErr_SetString(PyExc_TypeError, "Argument is not a sfColor");
		return NULL;
	}
	PySfColorUpdate(Color);
	self->obj->SetBackgroundColor(*(Color->obj));
	Py_RETURN_NONE;
}

static PyObject *
PySfRenderWindow_SetView(PySfRenderWindow* self, PyObject *args)
{
	PySfView *View = (PySfView *)args;
	if (! PyObject_TypeCheck(View, &PySfViewType))
	{
		PyErr_SetString(PyExc_TypeError, "Argument is not a sfView");
		return NULL;
	}
	self->obj->SetView( *(View->obj));
	Py_RETURN_NONE;
}

static PyMethodDef PySfRenderWindow_methods[] = {
	{"Capture", (PyCFunction)PySfRenderWindow_Capture, METH_NOARGS, "Save the content of the window to an image."},
	{"ConvertCoords", (PyCFunction)PySfRenderWindow_ConvertCoords, METH_VARARGS, "Convert a point in window coordinates into view coordinates\n\
param WindowX :    X coordinate of the point to convert, relative to the window\n\
param WindowY :    Y coordinate of the point to convert, relative to the window\n\
param TargetView : Target view to convert the point to (NULL by default -- uses the current view)."},
	{"Draw", (PyCFunction)PySfRenderWindow_Draw, METH_O, "Draw something on the window."},
	{"GetDefaultView", (PyCFunction)PySfRenderWindow_GetDefaultView, METH_NOARGS, "Get the default view of the window for read / write."},
	{"GetView", (PyCFunction)PySfRenderWindow_GetView, METH_NOARGS, "Get the current view rectangle."},
	{"PreserveOpenGLStates", (PyCFunction)PySfRenderWindow_PreserveOpenGLStates, METH_O, "\
Tell SFML to preserve external OpenGL states, at the expense of\
more CPU charge. Use this function if you don't want SFML\
to mess up your own OpenGL states (if any).\
Don't enable state preservation if not needed, as it will allow\
SFML to do internal optimizations and improve performances.\
This parameter is false by default\n\
param Preserve : True to preserve OpenGL states, false to let SFML optimize"},
	{"SetBackgroundColor", (PyCFunction)PySfRenderWindow_SetBackgroundColor, METH_O, "Change the background color of the window."},
	{"SetView", (PyCFunction)PySfRenderWindow_SetView, METH_O, "Change the current active view."},
	{NULL}  /* Sentinel */
};

PyTypeObject PySfRenderWindowType = {
	PyObject_HEAD_INIT(NULL)
	0,                         /*ob_size*/
	"RenderWindow",             /*tp_name*/
	sizeof(PySfRenderWindow),             /*tp_basicsize*/
	0,                         /*tp_itemsize*/
	(destructor)PySfRenderWindow_dealloc, /*tp_dealloc*/
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
	Py_TPFLAGS_DEFAULT, /*tp_flags*/
	"Simple wrapper for sfWindow that allows easy 2D rendering.",           /* tp_doc */
	0,		               /* tp_traverse */
	0,		               /* tp_clear */
	0,		               /* tp_richcompare */
	0,		               /* tp_weaklistoffset */
	0,		               /* tp_iter */
	0,		               /* tp_iternext */
	PySfRenderWindow_methods,             /* tp_methods */
	PySfRenderWindow_members,             /* tp_members */
	0,                         /* tp_getset */
	&PySfWindowType,                         /* tp_base */
	0,                         /* tp_dict */
	0,                         /* tp_descr_get */
	0,                         /* tp_descr_set */
	0,                         /* tp_dictoffset */
	(initproc)PySfRenderWindow_init,      /* tp_init */
	0,                         /* tp_alloc */
	PySfRenderWindow_new,                 /* tp_new */
};


