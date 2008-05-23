#include "WindowSettings.hpp"

static PyMemberDef PySfWindowSettings_members[] = {
	{"DepthBits", T_UINT, offsetof(PySfWindowSettings, DepthBits), 0, "Depth buffer bits (24 by default)"},
	{"StencilBits", T_UINT, offsetof(PySfWindowSettings, StencilBits), 0, "Stencil buffer bits (8 by default)"},
	{"AntialiasingLevel", T_UINT, offsetof(PySfWindowSettings, AntialiasingLevel), 0, "Antialiasing level (0 by default)"},
	{NULL}  /* Sentinel */
};


static void
PySfWindowSettings_dealloc(PySfWindowSettings *self)
{
	self->ob_type->tp_free((PyObject*)self);
}

void
PySfWindowSettingsUpdate(PySfWindowSettings *self)
{
	self->obj->DepthBits = self->DepthBits;
	self->obj->StencilBits = self->StencilBits;
	self->obj->AntialiasingLevel = self->AntialiasingLevel;
}

static PyObject *
PySfWindowSettings_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
	PySfWindowSettings *self;

	self = (PySfWindowSettings *)type->tp_alloc(type, 0);

	if (self != NULL)
	{
		self->DepthBits = 24;
		self->StencilBits = 8;
		self->AntialiasingLevel = 0;
	}

	return (PyObject *)self;
}


static int
PySfWindowSettings_init(PySfWindowSettings *self, PyObject *args, PyObject *kwds)
{
	const char *kwlist[] = {"DepthBits", "StencilBits", "AntialiasingLevel", NULL};
	if (! PyArg_ParseTupleAndKeywords(args, kwds, "|III", (char **)kwlist, &(self->DepthBits), &(self->StencilBits), &(self->AntialiasingLevel)))
		return -1;
	self->obj = new sf::WindowSettings(self->DepthBits, self->StencilBits, self->AntialiasingLevel);

	return 0;
}

static PyMethodDef PySfWindowSettings_methods[] = {
	{NULL}  /* Sentinel */
};


PyTypeObject PySfWindowSettingsType = {
	PyObject_HEAD_INIT(NULL)
	0,						/*ob_size*/
	"WindowSettings",             /*tp_name*/
	sizeof(PySfWindowSettings),   /*tp_basicsize*/
	0,						/*tp_itemsize*/
	(destructor)PySfWindowSettings_dealloc, /*tp_dealloc*/
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
	"sfSettings is an utility class for manipulating Settingss", /* tp_doc */
	0,						/* tp_traverse */
	0,						/* tp_clear */
	0,						/* tp_richcompare */
	0,						/* tp_weaklistoffset */
	0,						/* tp_iter */
	0,						/* tp_iternext */
	PySfWindowSettings_methods,	/* tp_methods */
	PySfWindowSettings_members,	/* tp_members */
	0,						/* tp_getset */
	0,						/* tp_base */
	0,						/* tp_dict */
	0,						/* tp_descr_get */
	0,						/* tp_descr_set */
	0,						/* tp_dictoffset */
	(initproc)PySfWindowSettings_init, /* tp_init */
	0,						/* tp_alloc */
	PySfWindowSettings_new,		/* tp_new */
};

PySfWindowSettings *
GetNewPySfWindowSettings()
{
	return PyObject_New(PySfWindowSettings, &PySfWindowSettingsType);
}

