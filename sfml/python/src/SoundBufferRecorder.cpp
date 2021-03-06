#include "SoundBufferRecorder.hpp"

#include "SoundBuffer.hpp"

extern PyTypeObject PySfSoundRecorderType;

static PyMemberDef PySfSoundBufferRecorder_members[] = {
    {NULL}  /* Sentinel */
};



static void
PySfSoundBufferRecorder_dealloc(PySfSoundBufferRecorder *self)
{
	delete self->obj;
	self->ob_type->tp_free((PyObject*)self);
}

static PyObject *
PySfSoundBufferRecorder_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
	PySfSoundBufferRecorder *self;

	self = (PySfSoundBufferRecorder *)type->tp_alloc(type, 0);

	if (self != NULL)
	{
	}

	return (PyObject *)self;
}

static int
PySfSoundBufferRecorder_init(PySfSoundBufferRecorder *self, PyObject *args)
{
	self->obj = new sf::SoundBufferRecorder();
	return 0;
}

static PyObject *
PySfSoundBufferRecorder_GetBuffer(PySfSoundBufferRecorder* self)
{
	PySfSoundBuffer *SoundBuffer = GetNewPySfSoundBuffer();
	SoundBuffer->obj = new sf::SoundBuffer( self->obj->GetBuffer() );
	return (PyObject *)SoundBuffer;
}


static PyMethodDef PySfSoundBufferRecorder_methods[] = {
	{"GetBuffer", (PyCFunction)PySfSoundBufferRecorder_GetBuffer, METH_NOARGS, "Get the sound buffer containing the captured audio data. Returns a SoundBuffer object."},
	{NULL}  /* Sentinel */
};

PyTypeObject PySfSoundBufferRecorderType = {
	PyObject_HEAD_INIT(NULL)
	0,                         /*ob_size*/
	"SoundBufferRecorder",             /*tp_name*/
	sizeof(PySfSoundBufferRecorder),             /*tp_basicsize*/
	0,                         /*tp_itemsize*/
	(destructor)PySfSoundBufferRecorder_dealloc, /*tp_dealloc*/
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
	"Specialized SoundRecorder which saves the captured audio data into a sound buffer.",           /* tp_doc */
	0,		               /* tp_traverse */
	0,		               /* tp_clear */
	0,		               /* tp_richcompare */
	0,		               /* tp_weaklistoffset */
	0,		               /* tp_iter */
	0,		               /* tp_iternext */
	PySfSoundBufferRecorder_methods,             /* tp_methods */
	PySfSoundBufferRecorder_members,             /* tp_members */
	0,                         /* tp_getset */
	&PySfSoundRecorderType,                         /* tp_base */
	0,                         /* tp_dict */
	0,                         /* tp_descr_get */
	0,                         /* tp_descr_set */
	0,                         /* tp_dictoffset */
	(initproc)PySfSoundBufferRecorder_init,      /* tp_init */
	0,                         /* tp_alloc */
	PySfSoundBufferRecorder_new,                 /* tp_new */
};


