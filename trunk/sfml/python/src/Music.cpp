#include "Music.hpp"


static PyMemberDef PySfMusic_members[] = {
	{NULL}  /* Sentinel */
};


static void
PySfMusic_dealloc(PySfMusic *self)
{
	delete self->obj;
	self->ob_type->tp_free((PyObject*)self);
}

static PyObject *
PySfMusic_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
	PySfMusic *self;

	self = (PySfMusic *)type->tp_alloc(type, 0);
	if (self != NULL)
	{
	}

	return (PyObject *)self;
}


static int
PySfMusic_init(PySfMusic *self, PyObject *args, PyObject *kwds)
{
	unsigned int BufferSize=44100;
	if (PyTuple_Size(args) == 1)
	{
		if ( !PyArg_ParseTuple(args, "I", &BufferSize))
			return -1;
	}
	self->obj = new sf::Music(BufferSize);
	return 0;
}

static PyObject*
PySfMusic_OpenFromMemory(PySfMusic *self, PyObject *args)
{
	unsigned int SizeInBytes;
	char *Data;

	if (! PyArg_ParseTuple(args, "s#", &Data, &SizeInBytes))
		return NULL; 

	if (self->obj->OpenFromMemory(Data, (std::size_t) SizeInBytes))
		Py_RETURN_TRUE;
	else
		Py_RETURN_FALSE;
}

static PyObject*
PySfMusic_OpenFromFile(PySfMusic *self, PyObject *args)
{
	char *path = PyString_AsString(args);
	if (self->obj->OpenFromFile(path))
		Py_RETURN_TRUE;
	else
		Py_RETURN_FALSE;
}

static PyObject*
PySfMusic_SetLoop(PySfMusic *self, PyObject *args)
{
	if (args == Py_True)
		self->obj->SetLoop(true);
	else
		self->obj->SetLoop(false);
	Py_RETURN_NONE;
}

static PyObject*
PySfMusic_GetLoop(PySfMusic *self)
{
	if (self->obj->GetLoop())
		Py_RETURN_TRUE;
	else
		Py_RETURN_FALSE;
}

static PyObject*
PySfMusic_GetDuration(PySfMusic *self)
{
	return PyFloat_FromDouble((double)(self->obj->GetDuration()));
}

static PyObject*
PySfMusic_Play(PySfMusic *self)
{
	self->obj->Play();
	Py_RETURN_NONE;
}

static PyObject*
PySfMusic_Stop(PySfMusic *self)
{
	self->obj->Stop();
	Py_RETURN_NONE;
}

static PyObject*
PySfMusic_GetChannelsCount(PySfMusic *self)
{
	return PyLong_FromUnsignedLong(self->obj->GetChannelsCount());
}

static PyObject*
PySfMusic_GetSampleRate(PySfMusic *self)
{
	return PyLong_FromUnsignedLong(self->obj->GetSampleRate());
}

static PyObject*
PySfMusic_GetStatus(PySfMusic *self)
{
	return PyLong_FromUnsignedLong(self->obj->GetStatus());
}

static PyObject*
PySfMusic_Initialize(PySfMusic *self, PyObject *args)
{
	unsigned int ChannelsCount, SampleRate;
	if (! PyArg_ParseTuple(args, "II", &ChannelsCount, &SampleRate))
		return NULL; 
	// self->obj->Initialize(ChannelsCount, SampleRate);
	Py_RETURN_NONE;
}

static PyMethodDef PySfMusic_methods[] = {
	{"OpenFromFile", (PyCFunction)PySfMusic_OpenFromFile, METH_O, "Open a music file (doesn't play it -- call Play() for that)."},
	{"OpenFromMemory", (PyCFunction)PySfMusic_OpenFromMemory, METH_VARARGS, "Open a music file (doesn't play it -- call Play() for that)."},
	{"SetLoop", (PyCFunction)PySfMusic_SetLoop, METH_O, "Set the music loop state."},
	{"GetLoop", (PyCFunction)PySfMusic_GetLoop, METH_NOARGS, "Tell whether or not the music is looping."},
	{"GetDuration", (PyCFunction)PySfMusic_GetDuration, METH_NOARGS, "Get the sound duration."},
	{"Play", (PyCFunction)PySfMusic_Play, METH_NOARGS, "Start playing the audio stream."},
	{"Stop", (PyCFunction)PySfMusic_Stop, METH_NOARGS, "Stop playing the audio stream."},
	{"GetChannelsCount", (PyCFunction)PySfMusic_GetChannelsCount, METH_NOARGS, "Return the number of channels (1 = mono, 2 = stereo)"},
	{"GetSampleRate", (PyCFunction)PySfMusic_GetSampleRate, METH_NOARGS, "Get the sound frequency (sample rate)."},
	{"GetStatus", (PyCFunction)PySfMusic_GetStatus, METH_NOARGS, "Get the status of the sound (stopped, paused, playing)."},
	{"Initialize", (PyCFunction)PySfMusic_Initialize, METH_VARARGS, "Set the audio stream parameters, you must call it before Play()."},
	{NULL}  /* Sentinel */
};

PyTypeObject PySfMusicType = {
	PyObject_HEAD_INIT(NULL)
	0,                         /*ob_size*/
	"Music",             /*tp_name*/
	sizeof(PySfMusic),             /*tp_basicsize*/
	0,                         /*tp_itemsize*/
	(destructor)PySfMusic_dealloc, /*tp_dealloc*/
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
	"sfMusic defines a big sound played using streaming, so usually what we call a music :)",           /* tp_doc */
	0,		               /* tp_traverse */
	0,		               /* tp_clear */
	0,		               /* tp_richcompare */
	0,		               /* tp_weaklistoffset */
	0,		               /* tp_iter */
	0,		               /* tp_iternext */
	PySfMusic_methods,             /* tp_methods */
	PySfMusic_members,             /* tp_members */
	0,                         /* tp_getset */
	0,                         /* tp_base */
	0,                         /* tp_dict */
	0,                         /* tp_descr_get */
	0,                         /* tp_descr_set */
	0,                         /* tp_dictoffset */
	(initproc)PySfMusic_init,      /* tp_init */
	0,                         /* tp_alloc */
	PySfMusic_new,                 /* tp_new */
};


