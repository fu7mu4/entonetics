#include <SFML/Graphics/Drawable.hpp>

#include <Python.h>
#include <structmember.h>

#include "Blend.hpp"


typedef struct {
	PyObject_HEAD
} PySfBlend;



static PyMemberDef PySfBlend_members[] = {
	{NULL}  /* Sentinel */
};


static void
PySfBlend_dealloc(PySfBlend *self)
{
	self->ob_type->tp_free((PyObject*)self);
}

static PyObject *
PySfBlend_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
	PySfBlend *self;

	self = (PySfBlend *)type->tp_alloc(type, 0);
	if (self != NULL)
	{
	}

	return (PyObject *)self;
}


static int
PySfBlend_init(PySfBlend *self, PyObject *args, PyObject *kwds)
{
	return 0;
}

static PyMethodDef PySfBlend_methods[] = {
	{NULL}  /* Sentinel */
};

PyTypeObject PySfBlendType = {
	PyObject_HEAD_INIT(NULL)
	0,                         /*ob_size*/
	"Blend",             /*tp_name*/
	sizeof(PySfBlend),             /*tp_basicsize*/
	0,                         /*tp_itemsize*/
	(destructor)PySfBlend_dealloc, /*tp_dealloc*/
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
	"sfBlend doc",           /* tp_doc */
	0,		               /* tp_traverse */
	0,		               /* tp_clear */
	0,		               /* tp_richcompare */
	0,		               /* tp_weaklistoffset */
	0,		               /* tp_iter */
	0,		               /* tp_iternext */
	PySfBlend_methods,             /* tp_methods */
	PySfBlend_members,             /* tp_members */
	0,                         /* tp_getset */
	0,                         /* tp_base */
	0,                         /* tp_dict */
	0,                         /* tp_descr_get */
	0,                         /* tp_descr_set */
	0,                         /* tp_dictoffset */
	(initproc)PySfBlend_init,      /* tp_init */
	0,                         /* tp_alloc */
	PySfBlend_new,                 /* tp_new */
};

void PySfBlend_InitConst()
{
	PyObject *obj;
	obj = PyInt_FromLong(sf::Blend::Alpha);
	PyDict_SetItemString(PySfBlendType.tp_dict, "Alpha", obj);
	Py_DECREF(obj);
	obj = PyInt_FromLong(sf::Blend::Add);
	PyDict_SetItemString(PySfBlendType.tp_dict, "Add", obj);
	Py_DECREF(obj);
	obj = PyInt_FromLong(sf::Blend::Multiply);
	PyDict_SetItemString(PySfBlendType.tp_dict, "Multiply", obj);
	Py_DECREF(obj);
	obj = PyInt_FromLong(sf::Blend::None);
	PyDict_SetItemString(PySfBlendType.tp_dict, "None", obj);
	Py_DECREF(obj);
}

