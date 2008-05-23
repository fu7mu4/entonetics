#include "Sound.hpp"

#include "SoundBuffer.hpp"

extern PyTypeObject PySfSoundBufferType;

typedef struct {
	PyObject_HEAD
	sf::Sound *obj;
} PySfSound;



static PyMemberDef PySfSound_members[] = {
	{NULL}  /* Sentinel */
};


static void
PySfSound_dealloc(PySfSound *self)
{
	delete self->obj;
	self->ob_type->tp_free((PyObject*)self);
}

static PyObject *
PySfSound_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
	PySfSound *self;

	self = (PySfSound *)type->tp_alloc(type, 0);
	if (self != NULL)
	{
	}

	return (PyObject *)self;
}


static int
PySfSound_init(PySfSound *self, PyObject *args, PyObject *kwds)
{
//  Sound(const SoundBuffer& Buffer, bool Loop = false, float Pitch = 1.f, float Volume = 100.f, float X = 0.f, float Y = 0.f, float Z = 0.f);

	char *kwlist[] = {"Buffer", "Loop", "Pitch", "Volume", "X", "Y", "Z", NULL};
	PySfSoundBuffer *BufferTmp=NULL;
	sf::SoundBuffer *Buffer;
	bool Loop=false;
	PyObject *LoopObj=Py_False;
	float Pitch=1.f, Volume=100.f, X=0.f, Y=0.f, Z=0.f;
	if ( !PyArg_ParseTupleAndKeywords(args, kwds, "|O!Offfff", kwlist, &PySfSoundBufferType, &BufferTmp, &LoopObj, &Pitch, &Volume, &X, &Y, &Z))
		return -1;

	if (LoopObj == Py_True)
		Loop = true;

	if (BufferTmp != NULL)
	{
		Buffer = BufferTmp->obj;
		self->obj = new sf::Sound(*Buffer, Loop, Pitch, Volume, sf::Vector3f(X, Y, Z));
	}
	else
		self->obj = new sf::Sound();
	return 0;
}

static PyObject*
PySfSound_SetBuffer(PySfSound *self, PyObject *args)
{
	PySfSoundBuffer *Buffer = (PySfSoundBuffer *)args;
	if ( ! PyObject_TypeCheck(args, &PySfSoundBufferType))
		PyErr_SetString(PyExc_TypeError, "The argument must be a sfSoundBuffer.");

	self->obj->SetBuffer(*(Buffer->obj));

	Py_RETURN_NONE;
}

static PyObject*
PySfSound_SetLoop(PySfSound *self, PyObject *args)
{
	if (args == Py_True)
		self->obj->SetLoop(true);
	else
		self->obj->SetLoop(false);
	Py_RETURN_NONE;
}

static PyObject*
PySfSound_SetPitch(PySfSound *self, PyObject *args)
{
	self->obj->SetPitch(PyFloat_AsDouble(args));
	Py_RETURN_NONE;
}

static PyObject*
PySfSound_SetVolume(PySfSound *self, PyObject *args)
{
	self->obj->SetVolume(PyFloat_AsDouble(args));
	Py_RETURN_NONE;
}

static PyObject*
PySfSound_GetPitch(PySfSound *self)
{
	return PyFloat_FromDouble(self->obj->GetPitch());
}

static PyObject*
PySfSound_GetVolume(PySfSound *self)
{
	return PyFloat_FromDouble(self->obj->GetVolume());
}

static PyObject*
PySfSound_GetPosition(PySfSound *self)
{
	sf::Vector3f Vect = self->obj->GetPosition();
	return Py_BuildValue("fff", Vect.x, Vect.y, Vect.z);
}

static PyObject*
PySfSound_GetPlayingOffset(PySfSound *self)
{
	return PyFloat_FromDouble(self->obj->GetPlayingOffset());
}

static PyObject*
PySfSound_GetLoop(PySfSound *self)
{
	if (self->obj->GetLoop())
		Py_RETURN_TRUE;
	else
		Py_RETURN_FALSE;
}

static PyObject*
PySfSound_Play(PySfSound *self)
{
	self->obj->Play();
	Py_RETURN_NONE;
}

static PyObject*
PySfSound_Pause(PySfSound *self)
{
	self->obj->Pause();
	Py_RETURN_NONE;
}

static PyObject*
PySfSound_Stop(PySfSound *self)
{
	self->obj->Stop();
	Py_RETURN_NONE;
}

static PyObject*
PySfSound_GetStatus(PySfSound *self)
{
	return PyLong_FromUnsignedLong(self->obj->GetStatus());
}

static PyObject*
PySfSound_SetPosition(PySfSound *self, PyObject *args)
{
	float X, Y, Z;
	if (! PyArg_ParseTuple(args, "fff", &X, &Y, &Z))
		return NULL; 
	self->obj->SetPosition(X, Y, Z);
	Py_RETURN_NONE;
}

static PyObject *
PySfSound_GetBuffer(PySfSound *self, PyObject *args)
{
	PySfSoundBuffer *Buffer;

	Buffer = GetNewPySfSoundBuffer();
	Buffer->obj = new sf::SoundBuffer(*(self->obj->GetBuffer()));

	return (PyObject *)Buffer;
}

static PyMethodDef PySfSound_methods[] = {
	{"SetLoop", (PyCFunction)PySfSound_SetLoop, METH_O, "Set the Sound loop state."},
	{"SetBuffer", (PyCFunction)PySfSound_SetBuffer, METH_O, "Set the source buffer."},
	{"SetPitch", (PyCFunction)PySfSound_SetPitch, METH_O, "Set the sound pitch."},
	{"SetVolume", (PyCFunction)PySfSound_SetVolume, METH_O, "Set the sound volume."},
	{"SetPosition", (PyCFunction)PySfSound_SetPosition, METH_VARARGS, "Set the sound position in the world."},
	{"GetLoop", (PyCFunction)PySfSound_GetLoop, METH_NOARGS, "Tell whether or not the Sound is looping."},
	{"GetBuffer", (PyCFunction)PySfSound_GetBuffer, METH_O, "Get the source buffer. Returns a new sfSoundBuffer object."},
	{"GetPitch", (PyCFunction)PySfSound_GetPitch, METH_NOARGS, "Get the sound pitch."},
	{"GetVolume", (PyCFunction)PySfSound_GetVolume, METH_NOARGS, "Get the sound volume."},
	{"GetPosition", (PyCFunction)PySfSound_GetPosition, METH_NOARGS, "Get the sound position in the world. Returns a tuple."},
	{"Play", (PyCFunction)PySfSound_Play, METH_NOARGS, "Play the sound."},
	{"Pause", (PyCFunction)PySfSound_Pause, METH_NOARGS, "Pause the sound."},
	{"Stop", (PyCFunction)PySfSound_Stop, METH_NOARGS, "Stop the sound."},
	{"GetStatus", (PyCFunction)PySfSound_GetStatus, METH_NOARGS, "Get the status of the sound (stopped, paused, playing)."},
	{"GetPlayingOffset", (PyCFunction)PySfSound_GetPlayingOffset, METH_NOARGS, "Get the current playing position of the sound."},
	{NULL}  /* Sentinel */
};

PyTypeObject PySfSoundType = {
	PyObject_HEAD_INIT(NULL)
	0,                         /*ob_size*/
	"Sound",             /*tp_name*/
	sizeof(PySfSound),             /*tp_basicsize*/
	0,                         /*tp_itemsize*/
	(destructor)PySfSound_dealloc, /*tp_dealloc*/
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
	"sfSound defines a big sound played using streaming, so usually what we call a Sound :)\n\n\
Constructor: Sound(Buffer, Loop = false, Pitch = 1., Volume = 100., X = 0., Y = 0., Z = 0.);\n\
    param Buffer : Sound buffer to play (NULL by default)\n\
    param Loop :   Loop flag (false by default)\n\
    param Pitch :  Value of the pitch (1 by default)\n\
    param Volume : Volume (100 by default)\n\
    param X :      X position (0 by default)\n\
    param Y :      Y position (0 by default)\n\
    param Z :      Z position (0 by default)",           /* tp_doc */
	0,		               /* tp_traverse */
	0,		               /* tp_clear */
	0,		               /* tp_richcompare */
	0,		               /* tp_weaklistoffset */
	0,		               /* tp_iter */
	0,		               /* tp_iternext */
	PySfSound_methods,             /* tp_methods */
	PySfSound_members,             /* tp_members */
	0,                         /* tp_getset */
	0,                         /* tp_base */
	0,                         /* tp_dict */
	0,                         /* tp_descr_get */
	0,                         /* tp_descr_set */
	0,                         /* tp_dictoffset */
	(initproc)PySfSound_init,      /* tp_init */
	0,                         /* tp_alloc */
	PySfSound_new,                 /* tp_new */
};

void
PySfSound_InitConst()
{
	PyObject *obj;
	obj = PyInt_FromLong(sf::Sound::Stopped);
	PyDict_SetItemString(PySfSoundType.tp_dict, "Stopped", obj);
	Py_DECREF(obj);
	obj = PyInt_FromLong(sf::Sound::Paused);
	PyDict_SetItemString(PySfSoundType.tp_dict, "Paused", obj);
	Py_DECREF(obj);
	obj = PyInt_FromLong(sf::Sound::Playing);
	PyDict_SetItemString(PySfSoundType.tp_dict, "Playing", obj);
	Py_DECREF(obj);
}
