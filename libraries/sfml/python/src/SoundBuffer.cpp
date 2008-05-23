#include "SoundBuffer.hpp"


static PyMemberDef PySfSoundBuffer_members[] = {
	{NULL}  /* Sentinel */
};


static void
PySfSoundBuffer_dealloc(PySfSoundBuffer *self)
{
	delete self->obj;
	self->ob_type->tp_free((PyObject*)self);
}

static PyObject *
PySfSoundBuffer_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
	PySfSoundBuffer *self;

	self = (PySfSoundBuffer *)type->tp_alloc(type, 0);
	if (self != NULL)
	{
	}

	return (PyObject *)self;
}


static int
PySfSoundBuffer_init(PySfSoundBuffer *self, PyObject *args, PyObject *kwds)
{
	self->obj = new sf::SoundBuffer();
	return 0;
}

static PyObject*
PySfSoundBuffer_LoadFromFile(PySfSoundBuffer *self, PyObject *args)
{
	char *path = PyString_AsString(args);
	if (self->obj->LoadFromFile(path))
		Py_RETURN_TRUE;
	else
		Py_RETURN_FALSE;
}

static PyObject*
PySfSoundBuffer_LoadFromString(PySfSoundBuffer *self, PyObject *args)
{
	char *Data = PyString_AsString(args);
	std::size_t SizeInBytes = PyString_Size(args);
	std::cout << SizeInBytes << "\n";
	if (self->obj->LoadFromMemory(Data, SizeInBytes))
		Py_RETURN_TRUE;
	else
		Py_RETURN_FALSE;
}

static PyObject*
PySfSoundBuffer_LoadFromPtr(PySfSoundBuffer *self, PyObject *args)
{
	PyObject *DataTmp;
	char *Data;
	std::size_t SizeInBytes = 0;

	if (! PyArg_ParseTuple(args, "OI", &DataTmp, &SizeInBytes))
		return NULL;

	if (!PyCObject_Check(DataTmp))
		return NULL;

	Data = (char *)PyCObject_AsVoidPtr(DataTmp);
	if (self->obj->LoadFromMemory(Data, SizeInBytes))
		Py_RETURN_TRUE;
	else
		Py_RETURN_FALSE;
}

// bool LoadFromMemory(const char* Data, std::size_t SizeInBytes);

static PyObject*
PySfSoundBuffer_LoadFromSamples(PySfSoundBuffer *self, PyObject *args)
{
	// bool LoadFromSamples(const Int16* Samples, std::size_t SamplesCount, unsigned int ChannelsCount, unsigned int SampleRate);
	// Py_ssize_t (*readbufferproc) (PyObject *self, Py_ssize_t segment, void **ptrptr)
/*
	char *Samples;
	PyObject *SamplesObj;
	std::size_t SamplesCount;
	unsigned int ChannelsCount, SampleRate;
	if (! PyArg_ParseTuple(args, "OIII", &SamplesObj, &SamplesCount, &ChannelsCount, &SampleRate))
		return NULL;
	readbufferproc(SamplesObj, 0, &Samples);
	if (self->obj->LoadFromSamples((const short*)Samples, SamplesCount, ChannelsCount, SampleRate))
		Py_RETURN_TRUE;
	else
		Py_RETURN_FALSE;
*/
	
	PyErr_SetString(PyExc_NotImplementedError, "LoadFromSamples not implemented yet. However you can try to use LoadFromSamplesString by converting your sound samples to a string. If it is an array, use its tostring() method.");
	Py_RETURN_NONE;
}

static PyObject*
PySfSoundBuffer_LoadFromSamplesString(PySfSoundBuffer *self, PyObject *args)
{
	// bool LoadFromSamples(const Int16* Samples, std::size_t SamplesCount, unsigned int ChannelsCount, unsigned int SampleRate);
	char *Samples;
	std::size_t SamplesCount;
	unsigned int ChannelsCount, SampleRate;
	if (! PyArg_ParseTuple(args, "wIII", &Samples, &SamplesCount, &ChannelsCount, &SampleRate))
		return NULL; 
	if (self->obj->LoadFromSamples((const short*)Samples, SamplesCount, ChannelsCount, SampleRate))
		Py_RETURN_TRUE;
	else
		Py_RETURN_FALSE;
}

static PyObject*
PySfSoundBuffer_GetSamples(PySfSoundBuffer *self)
{
	return PyCObject_FromVoidPtr((void *)(self->obj->GetSamples()), NULL);
}

static PyObject*
PySfSoundBuffer_GetSamplesString(PySfSoundBuffer *self)
{
	return PyString_FromString((const char *)(self->obj->GetSamples()));
}

static PyObject*
PySfSoundBuffer_SaveToFile(PySfSoundBuffer *self, PyObject *args)
{
	char *path = PyString_AsString(args);
	if (self->obj->SaveToFile(path))
		Py_RETURN_TRUE;
	else
		Py_RETURN_FALSE;
}

static PyObject*
PySfSoundBuffer_GetDuration(PySfSoundBuffer *self)
{
	return PyFloat_FromDouble((double)(self->obj->GetDuration()));
}

static PyObject*
PySfSoundBuffer_GetChannelsCount(PySfSoundBuffer *self)
{
	return PyLong_FromUnsignedLong(self->obj->GetChannelsCount());
}

static PyObject*
PySfSoundBuffer_GetSampleRate(PySfSoundBuffer *self)
{
	return PyLong_FromUnsignedLong(self->obj->GetSampleRate());
}

static PyObject*
PySfSoundBuffer_GetSamplesCount(PySfSoundBuffer *self)
{
	return PyLong_FromUnsignedLong(self->obj->GetSamplesCount());
}


static PyMethodDef PySfSoundBuffer_methods[] = {
	{"LoadFromFile", (PyCFunction)PySfSoundBuffer_LoadFromFile, METH_O, "Load the sound buffer from a file."},
	{"SaveToFile", (PyCFunction)PySfSoundBuffer_SaveToFile, METH_O, "Save the sound buffer to a file."},
	{"LoadFromPtr", (PyCFunction)PySfSoundBuffer_LoadFromPtr, METH_VARARGS, "Load the sound buffer from a C pointer."},
	{"LoadFromString", (PyCFunction)PySfSoundBuffer_LoadFromString, METH_O, "Load the sound buffer from a string in memory. Takes only one parameter: the string."},
	{"LoadFromSamples", (PyCFunction)PySfSoundBuffer_LoadFromSamples, METH_VARARGS, "Load the sound buffer from an array of samples - assumed format for samples is 16 bits signed integer."},
	{"LoadFromSamplesString", (PyCFunction)PySfSoundBuffer_LoadFromSamplesString, METH_VARARGS, "Load the sound buffer from an array of samples - assumed format for samples is 16 bits signed integer. The samples must be converted to a string."},
	{"GetDuration", (PyCFunction)PySfSoundBuffer_GetDuration, METH_NOARGS, "Get the sound duration."},
	{"GetChannelsCount", (PyCFunction)PySfSoundBuffer_GetChannelsCount, METH_NOARGS, "Return the number of channels (1 = mono, 2 = stereo)."},
	{"GetSampleRate", (PyCFunction)PySfSoundBuffer_GetSampleRate, METH_NOARGS, "Get the sound frequency (sample rate)."},
	{"GetSamplesCount", (PyCFunction)PySfSoundBuffer_GetSamplesCount, METH_NOARGS, "Return the samples count."},
	{"GetSamples", (PyCFunction)PySfSoundBuffer_GetSamples, METH_NOARGS, "Return the sound samples as a C pointer."},
	{"GetSamplesString", (PyCFunction)PySfSoundBuffer_GetSamplesString, METH_NOARGS, "Return the sound samples as a string."},
	{NULL}  /* Sentinel */
};

PyTypeObject PySfSoundBufferType = {
	PyObject_HEAD_INIT(NULL)
	0,                         /*ob_size*/
	"SoundBuffer",             /*tp_name*/
	sizeof(PySfSoundBuffer),             /*tp_basicsize*/
	0,                         /*tp_itemsize*/
	(destructor)PySfSoundBuffer_dealloc, /*tp_dealloc*/
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
	"sfSoundBuffer defines a big sound played using streaming, so usually what we call a SoundBuffer :)",           /* tp_doc */
	0,		               /* tp_traverse */
	0,		               /* tp_clear */
	0,		               /* tp_richcompare */
	0,		               /* tp_weaklistoffset */
	0,		               /* tp_iter */
	0,		               /* tp_iternext */
	PySfSoundBuffer_methods,             /* tp_methods */
	PySfSoundBuffer_members,             /* tp_members */
	0,                         /* tp_getset */
	0,                         /* tp_base */
	0,                         /* tp_dict */
	0,                         /* tp_descr_get */
	0,                         /* tp_descr_set */
	0,                         /* tp_dictoffset */
	(initproc)PySfSoundBuffer_init,      /* tp_init */
	0,                         /* tp_alloc */
	PySfSoundBuffer_new,                 /* tp_new */
};

PySfSoundBuffer *
GetNewPySfSoundBuffer()
{
	return PyObject_New(PySfSoundBuffer, &PySfSoundBufferType);
}

