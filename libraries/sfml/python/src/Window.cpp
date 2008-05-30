#include "Window.hpp"

#include "SFML/Window/WindowStyle.hpp"

extern PyTypeObject PySfEventType;
extern PyTypeObject PySfWindowSettingsType;
extern PyTypeObject PySfVideoModeType;

static PyMemberDef PySfWindow_members[] = {
	{NULL}  /* Sentinel */
};

static void
PySfWindow_dealloc(PySfWindow* self)
{
	delete self->obj;
	self->ob_type->tp_free((PyObject*)self);
}

static PyObject *
PySfWindow_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
	PySfWindow *self;

	self = (PySfWindow *)type->tp_alloc(type, 0);
	if (self != NULL)
	{
		self->Settings = GetNewPySfWindowSettings();
	}

	return (PyObject *)self;
}

static PyObject*
PySfWindow_GetEvent(PySfWindow *self, PyObject *args)
{
	PySfEvent *PyEvent = (PySfEvent *)args;

	if (! PyObject_TypeCheck(PyEvent, &PySfEventType))
	{
		PyErr_SetString(PyExc_TypeError, "Argument is not a sfEvent");
		return NULL;
	}

	if (self->obj->GetEvent(*(PyEvent->obj)))
	{
		PyEvent->Type = PyEvent->obj->Type;
		PyEvent->Text->Unicode = PyEvent->obj->Text.Unicode;
		PyEvent->Key->Code = PyEvent->obj->Key.Code;
		if (PyEvent->obj->Key.Alt)
			PyEvent->Key->Alt = Py_True;
		else
			PyEvent->Key->Alt = Py_False;
		if (PyEvent->obj->Key.Control)
			PyEvent->Key->Control = Py_True;
		else
			PyEvent->Key->Control = Py_False;
		if (PyEvent->obj->Key.Shift)
			PyEvent->Key->Shift = Py_True;
		else
			PyEvent->Key->Shift = Py_False;
		PyEvent->MouseButton->Button = PyEvent->obj->MouseButton.Button;
		PyEvent->MouseMove->X = PyEvent->obj->MouseMove.X;
		PyEvent->MouseMove->Y = PyEvent->obj->MouseMove.Y;
		PyEvent->JoyMove->JoystickId = PyEvent->obj->JoyMove.JoystickId;
		PyEvent->JoyButton->JoystickId = PyEvent->obj->JoyButton.JoystickId;
		PyEvent->JoyButton->Button = PyEvent->obj->JoyButton.Button;
		PyEvent->JoyMove->Axis = PyEvent->obj->JoyMove.Axis;
		PyEvent->JoyMove->Position = PyEvent->obj->JoyMove.Position;
		PyEvent->Size->Width = PyEvent->obj->Size.Width;
		PyEvent->Size->Height = PyEvent->obj->Size.Height;
		PyEvent->MouseWheel->Delta = PyEvent->obj->MouseWheel.Delta;
		Py_RETURN_TRUE;
	}
	else
		Py_RETURN_FALSE;
}



static PyObject*
PySfWindow_Create(PySfWindow* self, PyObject *args, PyObject *kwds)
{
	PyObject *VideoModeTmp=NULL;
	sf::VideoMode *VideoMode;
	char *Title=NULL;
	unsigned long WindowStyle = sf::Style::Resize | sf::Style::Close;
	PySfWindowSettings *ParamsTmp=NULL;
	sf::WindowSettings *Params = NULL;

	const char *kwlist[] = {"VideoMode", "Title", "WindowStyle", "Params", NULL};

	if (! PyArg_ParseTupleAndKeywords(args, kwds, "O!s|IO!", (char **)kwlist, &PySfVideoModeType, &VideoModeTmp, &Title, &WindowStyle, &PySfWindowSettingsType, &ParamsTmp))
		return NULL; 

	if (VideoModeTmp) {
		VideoMode = ((PySfVideoMode *)VideoModeTmp)->obj;
		PySfVideoModeUpdate((PySfVideoMode *)VideoModeTmp);
	}
	else
		return NULL;

	if (ParamsTmp)
	{
		PySfWindowSettingsUpdate(ParamsTmp);
		Params = ParamsTmp->obj;
	}

	self->obj->Create(*VideoMode, Title, WindowStyle, *Params);

	Py_RETURN_NONE;
}

static int
PySfWindow_init(PySfWindow *self, PyObject *args, PyObject *kwds)
{
	self->obj = new sf::Window();
	PySfWindow_Create(self, args, kwds);
	return 0;
}

static PyObject *
PySfWindow_Close(PySfWindow *self)
{
	self->obj->Close();
	Py_RETURN_NONE;
}
static PyObject *
PySfWindow_IsOpened(PySfWindow *self)
{
	if (self->obj->IsOpened())
		Py_RETURN_TRUE;
	else
		Py_RETURN_NONE;
}
static PyObject *
PySfWindow_GetWidth(PySfWindow *self)
{
	return PyLong_FromUnsignedLong(self->obj->GetWidth());
}
static PyObject *
PySfWindow_GetHeight(PySfWindow *self)
{
	return PyLong_FromUnsignedLong(self->obj->GetHeight());
}

static PyObject *
PySfWindow_UseVerticalSync(PySfWindow *self, PyObject *args)
{
	bool Enabled = false;
	if (args == Py_True)
		Enabled = true;
	self->obj->UseVerticalSync(Enabled);
	Py_RETURN_NONE;
}
static PyObject *
PySfWindow_ShowMouseCursor(PySfWindow *self, PyObject *args)
{
	bool Show = false;
	if (args == Py_True)
		Show = true;
	self->obj->ShowMouseCursor(Show);
	Py_RETURN_NONE;
}

static PyObject *
PySfWindow_SetActive(PySfWindow *self, PyObject *args)
{
	bool Active = false;
	if (args == Py_True)
		Active = true;
	if (self->obj->SetActive(Active))
		Py_RETURN_TRUE;
	else
		Py_RETURN_FALSE;
}
static PyObject *
PySfWindow_Display(PySfWindow *self)
{
	self->obj->Display();
	Py_RETURN_NONE;
}
static PyObject *
PySfWindow_GetFrameTime(PySfWindow *self)
{
	return PyFloat_FromDouble(self->obj->GetFrameTime());
}

static PyObject *
PySfWindow_GetInput(PySfWindow *self)
{
	PySfInput *Input;
	Input = GetNewPySfInput();
	Input->obj = (sf::Input *)&self->obj->GetInput();
	return (PyObject *)Input;
}

static PyObject *
PySfWindow_GetSettings(PySfWindow *self)
{
	PySfWindowSettings *Settings;
	Settings = GetNewPySfWindowSettings();
	Settings->obj = (sf::WindowSettings *)&self->obj->GetSettings();
	Settings->DepthBits = Settings->obj->DepthBits;
	Settings->StencilBits = Settings->obj->StencilBits;
	Settings->AntialiasingLevel = Settings->obj->AntialiasingLevel;
	return (PyObject *)Settings;
}

static PyObject *
PySfWindow_SetPosition(PySfWindow* self, PyObject *args)
{
	int Left=0, Top=0;
	if (! PyArg_ParseTuple(args, "ii", &Left, &Top))
		return NULL; 

	self->obj->SetPosition(Left,Top);
	Py_RETURN_NONE;
}

static PyObject *
PySfWindow_SetFramerateLimit(PySfWindow *self, PyObject *args)
{
	self->obj->SetFramerateLimit(PyLong_AsUnsignedLong(args));
	Py_RETURN_NONE;
}

static PyObject *
PySfWindow_Show(PySfWindow *self, PyObject *args)
{
	if (args == Py_True)
		self->obj->Show(true);
	else
		self->obj->Show(false);
	Py_RETURN_NONE;
}

static PyObject *
PySfWindow_EnableKeyRepeat(PySfWindow *self, PyObject *args)
{
	if (args == Py_True)
		self->obj->EnableKeyRepeat(true);
	else
		self->obj->EnableKeyRepeat(false);
	Py_RETURN_NONE;
}

static PyObject *
PySfWindow_SetCursorPosition(PySfWindow* self, PyObject *args)
{
	unsigned int Left=0, Top=0;
	if (! PyArg_ParseTuple(args, "II", &Left, &Top))
		return NULL; 

	self->obj->SetCursorPosition(Left,Top);
	Py_RETURN_NONE;
}

static PyObject *
PySfWindow_SetJoystickThreshold(PySfWindow* self, PyObject *args)
{
	self->obj->SetJoystickThreshold(PyFloat_AsDouble(args));
	Py_RETURN_NONE;
}

static PyObject *
PySfWindow_ForceContextInit(PySfWindow* self, PyObject *args)
{
	self->obj->ForceContextInit();
	Py_RETURN_NONE;
}


static PyMethodDef PySfWindow_methods[] = {
	{"Close", (PyCFunction)PySfWindow_Close, METH_NOARGS, "Close (destroy) the window. The sf.Window instance remains valid and you can call Create to recreate the window."},
	{"Create", (PyCFunction)PySfWindow_Create, METH_VARARGS | METH_KEYWORDS, "Create a window"},
	{"Display", (PyCFunction)PySfWindow_Display, METH_NOARGS, "Display the window on screen."},
	{"EnableKeyRepeat", (PyCFunction)PySfWindow_EnableKeyRepeat, METH_O, "Activate of deactivate the window as the current target for rendering."},
	{"ForceContextInit", (PyCFunction)PySfWindow_ForceContextInit, METH_NOARGS | METH_STATIC, "Force a valid OpenGL context to exist even if no window has been created."},
	{"GetEvent", (PyCFunction)PySfWindow_GetEvent, METH_O, "Get the event on top of events stack, if any, and pop it."},
	{"GetFrameTime", (PyCFunction)PySfWindow_GetFrameTime, METH_NOARGS, "Get time elapsed since last frame."},
	{"GetHeight", (PyCFunction)PySfWindow_GetHeight, METH_NOARGS, "Get the height of the rendering region of the window."},
	{"GetInput", (PyCFunction)PySfWindow_GetInput, METH_NOARGS, "Get the input manager of the window."},
	{"GetSettings", (PyCFunction)PySfWindow_GetSettings, METH_NOARGS, "Get the creation settings of the window."},
	{"GetWidth", (PyCFunction)PySfWindow_GetWidth, METH_NOARGS, "Get the width of the rendering region of the window."},
	{"IsOpened", (PyCFunction)PySfWindow_IsOpened, METH_NOARGS, "Tell whether or not the window is opened (ie. has been created). Note that a hidden window (Show(false)) will still return true."},
	{"SetActive", (PyCFunction)PySfWindow_SetActive, METH_O, "Activate or deactivate the window as the current target for rendering."},
	{"SetCursorPosition", (PyCFunction)PySfWindow_SetCursorPosition, METH_VARARGS, "Change the position of the mouse cursor."},
	{"SetFramerateLimit", (PyCFunction)PySfWindow_SetFramerateLimit, METH_O, "Set the framerate at a fixed frequency."},
	{"SetJoystickThreshold", (PyCFunction)PySfWindow_SetJoystickThreshold, METH_O, "Change the joystick threshold, ie. the value below which no move event will be generated"},
	{"SetPosition", (PyCFunction)PySfWindow_SetPosition, METH_VARARGS, "Change the position of the window on screen."},
	{"Show", (PyCFunction)PySfWindow_Show, METH_O, "Show or hide the window."},
	{"ShowMouseCursor", (PyCFunction)PySfWindow_ShowMouseCursor, METH_O, "Show or hide the mouse cursor."},
	{"UseVerticalSync", (PyCFunction)PySfWindow_UseVerticalSync, METH_O, "Enable / disable vertical synchronization."},
	{NULL}  /* Sentinel */
};

PyTypeObject PySfWindowType = {
	PyObject_HEAD_INIT(NULL)
	0,                         /*ob_size*/
	"Window",             /*tp_name*/
	sizeof(PySfWindow),             /*tp_basicsize*/
	0,                         /*tp_itemsize*/
	(destructor)PySfWindow_dealloc, /*tp_dealloc*/
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
	"sfWindow objects",           /* tp_doc */
	0,		               /* tp_traverse */
	0,		               /* tp_clear */
	0,		               /* tp_richcompare */
	0,		               /* tp_weaklistoffset */
	0,		               /* tp_iter */
	0,		               /* tp_iternext */
	PySfWindow_methods,             /* tp_methods */
	PySfWindow_members,             /* tp_members */
	0,                         /* tp_getset */
	0,                         /* tp_base */
	0,                         /* tp_dict */
	0,                         /* tp_descr_get */
	0,                         /* tp_descr_set */
	0,                         /* tp_dictoffset */
	(initproc)PySfWindow_init,      /* tp_init */
	0,                         /* tp_alloc */
	PySfWindow_new,                 /* tp_new */
};


