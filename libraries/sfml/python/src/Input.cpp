#include "Input.hpp"


static PyMemberDef PySfInput_members[] = {
	{NULL}  /* Sentinel */
};


static void
PySfInput_dealloc(PySfInput *self)
{
	// delete self->obj;
	self->ob_type->tp_free((PyObject*)self);
}

static PyObject *
PySfInput_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
	PySfInput *self;

	self = (PySfInput *)type->tp_alloc(type, 0);
	if (self != NULL)
	{
	}

	return (PyObject *)self;
}


static int
PySfInput_init(PySfInput *self, PyObject *args, PyObject *kwds)
{
	PyErr_SetString(PyExc_StandardError, "You can't create an Input object yourself, because an Input object must always be associated to its window.\nThe only way to get an Input is by creating a window and calling: Input = MyWindow.GetInput().");
	return -1;
}

static PyObject*
PySfInput_IsKeyDown(PySfInput *self, PyObject *args)
{
	if (self->obj->IsKeyDown( (sf::Key::Code) PyInt_AsLong(args) ))
		Py_RETURN_TRUE;
	else
		Py_RETURN_FALSE;
}

static PyObject*
PySfInput_IsMouseButtonDown(PySfInput *self, PyObject *args)
{
	if (self->obj->IsMouseButtonDown( (sf::Mouse::Button) PyInt_AsLong(args) ))
		Py_RETURN_TRUE;
	else
		Py_RETURN_FALSE;
}

static PyObject*
PySfInput_IsJoystickButtonDown(PySfInput *self, PyObject *args)
{
	unsigned int JoyId, Button;
	if (! PyArg_ParseTuple (args, "II", &JoyId, &Button))
		return NULL;
	if (self->obj->IsJoystickButtonDown(JoyId, Button))
		Py_RETURN_TRUE;
	else
		Py_RETURN_FALSE;
}

static PyObject*
PySfInput_GetMouseX(PySfInput *self)
{
	return PyInt_FromLong(self->obj->GetMouseX());
}
static PyObject*
PySfInput_GetMouseY(PySfInput *self)
{
	return PyInt_FromLong(self->obj->GetMouseY());
}

static PyObject*
PySfInput_GetJoystickAxis(PySfInput *self, PyObject *args)
{
	unsigned int JoyId, Axis;
	if (! PyArg_ParseTuple (args, "II", &JoyId, &Axis))
		return NULL;
	return PyFloat_FromDouble(self->obj->GetJoystickAxis(JoyId, (sf::Joy::Axis) Axis));
}

static PyMethodDef PySfInput_methods[] = {
	{"IsKeyDown", (PyCFunction)PySfInput_IsKeyDown, METH_O, "Get the state of a key."},
	{"IsMouseButtonDown", (PyCFunction)PySfInput_IsMouseButtonDown, METH_O, "Get the state of a mouse button."},
	{"IsJoystickButtonDown", (PyCFunction)PySfInput_IsJoystickButtonDown, METH_VARARGS, "Get the state of a joystick button."},
	{"GetMouseX", (PyCFunction)PySfInput_GetMouseX, METH_NOARGS, "Get the mouse X position."},
	{"GetMouseY", (PyCFunction)PySfInput_GetMouseY, METH_NOARGS, "Get the mouse Y position."},
	{"GetJoystickAxis", (PyCFunction)PySfInput_GetJoystickAxis, METH_O | METH_VARARGS, "Get a joystick axis position."},
	{NULL}  /* Sentinel */
};

PyTypeObject PySfInputType = {
	PyObject_HEAD_INIT(NULL)
	0,                         /*ob_size*/
	"Input",             /*tp_name*/
	sizeof(PySfInput),             /*tp_basicsize*/
	0,                         /*tp_itemsize*/
	(destructor)PySfInput_dealloc, /*tp_dealloc*/
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
	"sfInput handles real-time input from keyboard and mouse.",           /* tp_doc */
	0,		               /* tp_traverse */
	0,		               /* tp_clear */
	0,		               /* tp_richcompare */
	0,		               /* tp_weaklistoffset */
	0,		               /* tp_iter */
	0,		               /* tp_iternext */
	PySfInput_methods,             /* tp_methods */
	PySfInput_members,             /* tp_members */
	0,                         /* tp_getset */
	0,                         /* tp_base */
	0,                         /* tp_dict */
	0,                         /* tp_descr_get */
	0,                         /* tp_descr_set */
	0,                         /* tp_dictoffset */
	(initproc)PySfInput_init,      /* tp_init */
	0,                         /* tp_alloc */
	PySfInput_new,                 /* tp_new */
};

PySfInput *
GetNewPySfInput()
{
	return PyObject_New(PySfInput, &PySfInputType);
}

