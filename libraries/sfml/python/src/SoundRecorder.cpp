#include "SoundRecorder.hpp"



static PyMemberDef PySfSoundRecorder_members[] = {
    {NULL}  /* Sentinel */
};



static void
PySfSoundRecorder_dealloc(PySfSoundRecorder* self)
{
	delete self->obj;
	self->ob_type->tp_free((PyObject*)self);
}

static PyObject *
PySfSoundRecorder_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
	PySfSoundRecorder *self;

	self = (PySfSoundRecorder *)type->tp_alloc(type, 0);

	if (self != NULL)
	{
		self->Callback = NULL;
	}

	return (PyObject *)self;
}

static bool
PySfSoundRecorder_Callback(const short int *Samples, std::size_t SamplesCount, void *Data)
{
	PySfSoundRecorder *self = (PySfSoundRecorder *)Data;
	if (PyObject_CallFunction(self->Callback, "s#O", (char *)Samples, SamplesCount*2, self->UserData) == Py_True)
		return true;
	else
		return false;
}

static int
PySfSoundRecorder_init(PySfSoundRecorder *self, PyObject *args)
{
	PyObject *Callback, *UserData=NULL;
	if (! PyArg_ParseTuple(args, "O|O", &Callback, &UserData))
		return -1;

	self->Callback = Callback;
	self->UserData = UserData;
	self->obj = new sf::SoundRecorder(&PySfSoundRecorder_Callback, (void *)self);

	return 0;
}


static PyObject *
PySfSoundRecorder_Start(PySfSoundRecorder* self, PyObject *args)
{
	self->obj->Start( PyInt_AsLong(args) );
	Py_RETURN_NONE;
}

static PyObject *
PySfSoundRecorder_Stop(PySfSoundRecorder* self)
{
	self->obj->Stop();
	Py_RETURN_NONE;
}

static PyObject *
PySfSoundRecorder_GetSampleRate(PySfSoundRecorder* self)
{
	return PyInt_FromLong(self->obj->GetSampleRate());
}

static PyObject *
PySfSoundRecorder_CanCapture(PySfSoundRecorder* self)
{
	if (sf::SoundRecorder::CanCapture())
		Py_RETURN_TRUE;
	else
		Py_RETURN_FALSE;
}



static PyMethodDef PySfSoundRecorder_methods[] = {
	{"Start", (PyCFunction)PySfSoundRecorder_Start, METH_O, "Start the capture. Warning : only one capture can happen at the same time.\nParam SampleRate : Sound frequency (the more samples, the higher the quality) (44100 by default = CD quality)."},
	{"Stop", (PyCFunction)PySfSoundRecorder_Stop, METH_NOARGS, "Stop the capture."},
	{"GetSampleRate", (PyCFunction)PySfSoundRecorder_GetSampleRate, METH_NOARGS, "Get the sample rate. Returns the frequency, in samples per second."},
	{"CanCapture", (PyCFunction)PySfSoundRecorder_CanCapture, METH_STATIC | METH_NOARGS, "Tell if the system supports sound capture. If not, this class won't be usable.\n Returns True if audio capture is supported."},
	{NULL}  /* Sentinel */
};


PyTypeObject PySfSoundRecorderType = {
	PyObject_HEAD_INIT(NULL)
	0,                         /*ob_size*/
	"SoundRecorder",             /*tp_name*/
	sizeof(PySfSoundRecorder),             /*tp_basicsize*/
	0,                         /*tp_itemsize*/
	(destructor)PySfSoundRecorder_dealloc, /*tp_dealloc*/
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
	"SoundRecorder is an interface for capturing sound data, it is meant to be used as a base class.\n\n\
Initialisation function: SoundRecorder(Callback, UserData)\n\
Construct the sound recorder with a callback function for processing captured samples.\n\
Callback : Callback function for processing captured samples. This function must take two parameters: the first one is a string containing captured samples, the second one is UserData.\n\
UserData : Data to pass to the callback function (None by default).\n",           /* tp_doc */
	0,		               /* tp_traverse */
	0,		               /* tp_clear */
	0,		               /* tp_richcompare */
	0,		               /* tp_weaklistoffset */
	0,		               /* tp_iter */
	0,		               /* tp_iternext */
	PySfSoundRecorder_methods,             /* tp_methods */
	PySfSoundRecorder_members,             /* tp_members */
	0,                         /* tp_getset */
	0,                         /* tp_base */
	0,                         /* tp_dict */
	0,                         /* tp_descr_get */
	0,                         /* tp_descr_set */
	0,                         /* tp_dictoffset */
	(initproc)PySfSoundRecorder_init,      /* tp_init */
	0,                         /* tp_alloc */
	PySfSoundRecorder_new,                 /* tp_new */
};

