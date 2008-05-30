#include "Event.hpp"


////////////////////////////////
// Text Events Parameters 
////////////////////////////////

PyMemberDef PySfEventText_members[] = {
	{"Unicode", T_USHORT, offsetof(PySfEventText, Unicode), 0, ""},
	{NULL}  /* Sentinel */
};

int
PySfEventText_init(PySfEventText *self, PyObject *args, PyObject *kwds)
{
	return 0;
}

void
PySfEventText_dealloc(PySfEventText* self)
{
	self->ob_type->tp_free((PyObject*)self);
}

PyTypeObject PySfEventTextType = {
	PyObject_HEAD_INIT(NULL)
	0,						/*ob_size*/
	"Event.Text",			/*tp_name*/
	sizeof(PySfEventText),	/*tp_basicsize*/
	0,						/*tp_itemsize*/
	(destructor)PySfEventText_dealloc, /*tp_dealloc*/
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
	Py_TPFLAGS_DEFAULT,		/*tp_flags*/
	"Text Events Parameters", /* tp_doc */
	0,						/* tp_traverse */
	0,						/* tp_clear */
	0,						/* tp_richcompare */
	0,						/* tp_weaklistoffset */
	0,						/* tp_iter */
	0,						/* tp_iternext */
	0,						/* tp_methods */
	PySfEventText_members,	/* tp_members */
	0,						/* tp_getset */
	0,						/* tp_base */
	0,						/* tp_dict */
	0,						/* tp_descr_get */
	0,						/* tp_descr_set */
	0,						/* tp_dictoffset */
	(initproc)PySfEventText_init, /* tp_init */
	0,						/* tp_alloc */
};



/////////////////////////////////////
// Keyboard Events Parameters
/////////////////////////////////////

int
PySfEventKey_init(PySfEventKey *self, PyObject *args, PyObject *kwds)
{
	return 0;
}

void
PySfEventKey_dealloc(PySfEventKey* self)
{
	self->ob_type->tp_free((PyObject*)self);
}

PyMemberDef PySfEventKey_members[] = {
	{"Alt", T_OBJECT, offsetof(PySfEventKey, Alt), 0, ""},
	{"Control", T_OBJECT, offsetof(PySfEventKey, Control), 0, ""},
	{"Shift", T_OBJECT, offsetof(PySfEventKey, Shift), 0, ""},
	{"Code", T_UINT, offsetof(PySfEventKey, Code), 0, ""},
	{NULL}  /* Sentinel */
};

PyTypeObject PySfEventKeyType = {
	PyObject_HEAD_INIT(NULL)
	0,						/*ob_size*/
	"Event.Key",			/*tp_name*/
	sizeof(PySfEventKey),	/*tp_basicsize*/
	0,						/*tp_itemsize*/
	(destructor)PySfEventKey_dealloc, /*tp_dealloc*/
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
	Py_TPFLAGS_DEFAULT,		/*tp_flags*/
	"Key Events Parameters", /* tp_doc */
	0,						/* tp_traverse */
	0,						/* tp_clear */
	0,						/* tp_richcompare */
	0,						/* tp_weaklistoffset */
	0,						/* tp_iter */
	0,						/* tp_iternext */
	0,						/* tp_methods */
	PySfEventKey_members,	/* tp_members */
	0,						/* tp_getset */
	0,						/* tp_base */
	0,						/* tp_dict */
	0,						/* tp_descr_get */
	0,						/* tp_descr_set */
	0,						/* tp_dictoffset */
	(initproc)PySfEventKey_init, /* tp_init */
	0,						/* tp_alloc */
};


////////////////////////////////////
// MouseMove Events Parameters
////////////////////////////////////

int
PySfEventMouseMove_init(PySfEventMouseMove *self, PyObject *args, PyObject *kwds)
{
	return 0;
}

void
PySfEventMouseMove_dealloc(PySfEventMouseMove *self)
{
	self->ob_type->tp_free((PyObject*)self);
}


PyMemberDef PySfEventMouseMove_members[] = {
	{"X", T_UINT, offsetof(PySfEventMouseMove, X), 0, ""},
	{"Y", T_UINT, offsetof(PySfEventMouseMove, Y), 0, ""},
	{NULL}  /* Sentinel */
};

PyTypeObject PySfEventMouseMoveType = {
	PyObject_HEAD_INIT(NULL)
	0,						/*ob_size*/
	"Event.MouseMove",		/*tp_name*/
	sizeof(PySfEventMouseMove), /*tp_basicsize*/
	0,						/*tp_itemsize*/
	(destructor)PySfEventMouseMove_dealloc, /*tp_dealloc*/
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
	Py_TPFLAGS_DEFAULT,		/*tp_flags*/
	"MouseMove Events Parameters", /* tp_doc */
	0,						/* tp_traverse */
	0,						/* tp_clear */
	0,						/* tp_richcompare */
	0,						/* tp_weaklistoffset */
	0,						/* tp_iter */
	0,						/* tp_iternext */
	0,						/* tp_methods */
	PySfEventMouseMove_members,	/* tp_members */
	0,						/* tp_getset */
	0,						/* tp_base */
	0,						/* tp_dict */
	0,						/* tp_descr_get */
	0,						/* tp_descr_set */
	0,						/* tp_dictoffset */
	(initproc)PySfEventMouseMove_init, /* tp_init */
	0,						/* tp_alloc */
};


////////////////////////////////////
// MouseButton Events Parameters
////////////////////////////////////

int
PySfEventMouseButton_init(PySfEventMouseButton *self, PyObject *args, PyObject *kwds)
{
	return 0;
}

void
PySfEventMouseButton_dealloc(PySfEventMouseButton* self)
{
	self->ob_type->tp_free((PyObject*)self);
}


PyMemberDef PySfEventMouseButton_members[] = {
	{"Button", T_UINT, offsetof(PySfEventMouseButton, Button), 0, ""},
	{NULL}  /* Sentinel */
};

PyTypeObject PySfEventMouseButtonType = {
	PyObject_HEAD_INIT(NULL)
	0,						/*ob_size*/
	"Event.MouseButton",	/*tp_name*/
	sizeof(PySfEventMouseButton), /*tp_basicsize*/
	0,						/*tp_itemsize*/
	(destructor)PySfEventMouseButton_dealloc, /*tp_dealloc*/
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
	Py_TPFLAGS_DEFAULT,		/*tp_flags*/
	"MouseButton Events Parameters", /* tp_doc */
	0,						/* tp_traverse */
	0,						/* tp_clear */
	0,						/* tp_richcompare */
	0,						/* tp_weaklistoffset */
	0,						/* tp_iter */
	0,						/* tp_iternext */
	0,						/* tp_methods */
	PySfEventMouseButton_members, /* tp_members */
	0,						/* tp_getset */
	0,						/* tp_base */
	0,						/* tp_dict */
	0,						/* tp_descr_get */
	0,						/* tp_descr_set */
	0,						/* tp_dictoffset */
	(initproc)PySfEventMouseButton_init, /* tp_init */
	0,						/* tp_alloc */
};


////////////////////////////////
// MouseWheel Events Parameters 
////////////////////////////////

PyMemberDef PySfEventMouseWheel_members[] = {
	{"Delta", T_INT, offsetof(PySfEventMouseWheel,Delta), 0, ""},
	{NULL}  /* Sentinel */
};

int
PySfEventMouseWheel_init(PySfEventMouseWheel *self, PyObject *args, PyObject *kwds)
{
	return 0;
}

void
PySfEventMouseWheel_dealloc(PySfEventMouseWheel* self)
{
	self->ob_type->tp_free((PyObject*)self);
}

PyTypeObject PySfEventMouseWheelType = {
	PyObject_HEAD_INIT(NULL)
	0,						/*ob_size*/
	"Event.MouseWheel",		/*tp_name*/
	sizeof(PySfEventMouseWheel), /*tp_basicsize*/
	0,						/*tp_itemsize*/
	(destructor)PySfEventMouseWheel_dealloc, /*tp_dealloc*/
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
	Py_TPFLAGS_DEFAULT,		/*tp_flags*/
	"MouseWheel Events Parameters", /* tp_doc */
	0,						/* tp_traverse */
	0,						/* tp_clear */
	0,						/* tp_richcompare */
	0,						/* tp_weaklistoffset */
	0,						/* tp_iter */
	0,						/* tp_iternext */
	0,						/* tp_methods */
	PySfEventMouseWheel_members, /* tp_members */
	0,						/* tp_getset */
	0,						/* tp_base */
	0,						/* tp_dict */
	0,						/* tp_descr_get */
	0,						/* tp_descr_set */
	0,						/* tp_dictoffset */
	(initproc)PySfEventMouseWheel_init,	/* tp_init */
	0,						/* tp_alloc */
};


////////////////////////////////////
// JoyMove Events Parameters
////////////////////////////////////

int
PySfEventJoyMove_init(PySfEventJoyMove *self, PyObject *args, PyObject *kwds)
{
	return 0;
}

void
PySfEventJoyMove_dealloc(PySfEventJoyMove* self)
{
	self->ob_type->tp_free((PyObject*)self);
}


PyMemberDef PySfEventJoyMove_members[] = {
	{"JoystickId", T_UINT, offsetof(PySfEventJoyMove,JoystickId), 0, ""},
	{"Axis", T_UINT, offsetof(PySfEventJoyMove,Axis), 0, ""},
	{"Position", T_FLOAT, offsetof(PySfEventJoyMove,Position), 0, ""},
	{NULL}  /* Sentinel */
};

PyTypeObject PySfEventJoyMoveType = {
	PyObject_HEAD_INIT(NULL)
	0,						/*ob_size*/
	"Event.JoyMove",		/*tp_name*/
	sizeof(PySfEventJoyMove), /*tp_basicsize*/
	0,						/*tp_itemsize*/
	(destructor)PySfEventJoyMove_dealloc, /*tp_dealloc*/
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
	Py_TPFLAGS_DEFAULT,		/*tp_flags*/
	"JoyMove Events Parameters", /* tp_doc */
	0,						/* tp_traverse */
	0,						/* tp_clear */
	0,						/* tp_richcompare */
	0,						/* tp_weaklistoffset */
	0,						/* tp_iter */
	0,						/* tp_iternext */
	0,						/* tp_methods */
	PySfEventJoyMove_members, /* tp_members */
	0,						/* tp_getset */
	0,						/* tp_base */
	0,						/* tp_dict */
	0,						/* tp_descr_get */
	0,						/* tp_descr_set */
	0,						/* tp_dictoffset */
	(initproc)PySfEventJoyMove_init, /* tp_init */
	0,						/* tp_alloc */
};


////////////////////////////////////
// JoyButton Events Parameters
////////////////////////////////////

int
PySfEventJoyButton_init(PySfEventJoyButton *self, PyObject *args, PyObject *kwds)
{
	return 0;
}

void
PySfEventJoyButton_dealloc(PySfEventJoyButton* self)
{
	self->ob_type->tp_free((PyObject*)self);
}


PyMemberDef PySfEventJoyButton_members[] = {
	{"JoystickId", T_UINT, offsetof(PySfEventJoyButton, JoystickId), 0, ""},
	{"Button", T_UINT, offsetof(PySfEventJoyButton, Button), 0, ""},
	{NULL}  /* Sentinel */
};

PyTypeObject PySfEventJoyButtonType = {
	PyObject_HEAD_INIT(NULL)
	0,						/*ob_size*/
	"Event.JoyButton",		/*tp_name*/
	sizeof(PySfEventJoyButton),	/*tp_basicsize*/
	0,						/*tp_itemsize*/
	(destructor)PySfEventJoyButton_dealloc, /*tp_dealloc*/
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
	Py_TPFLAGS_DEFAULT,		/*tp_flags*/
	"JoyButton Events Parameters", /* tp_doc */
	0,						/* tp_traverse */
	0,						/* tp_clear */
	0,						/* tp_richcompare */
	0,						/* tp_weaklistoffset */
	0,						/* tp_iter */
	0,						/* tp_iternext */
	0,						/* tp_methods */
	PySfEventJoyButton_members, /* tp_members */
	0,						/* tp_getset */
	0,						/* tp_base */
	0,						/* tp_dict */
	0,						/* tp_descr_get */
	0,						/* tp_descr_set */
	0,						/* tp_dictoffset */
	(initproc)PySfEventJoyButton_init, /* tp_init */
	0,						/* tp_alloc */
};


////////////////////////////////////
// Size Events Parameters
////////////////////////////////////

int
PySfEventSize_init(PySfEventSize *self, PyObject *args, PyObject *kwds)
{
	return 0;
}

void
PySfEventSize_dealloc(PySfEventSize* self)
{
	self->ob_type->tp_free((PyObject*)self);
}

PyMemberDef PySfEventSize_members[] = {
	{"Width", T_UINT, offsetof(PySfEventSize, Width), 0, ""},
	{"Height", T_UINT, offsetof(PySfEventSize, Height), 0, ""},
	{NULL}  /* Sentinel */
};

PyTypeObject PySfEventSizeType = {
	PyObject_HEAD_INIT(NULL)
	0,						/*ob_size*/
	"Event.Size",			/*tp_name*/
	sizeof(PySfEventSize),	/*tp_basicsize*/
	0,						/*tp_itemsize*/
	(destructor)PySfEventSize_dealloc, /*tp_dealloc*/
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
	Py_TPFLAGS_DEFAULT,		/*tp_flags*/
	"Size Events Parameters", /* tp_doc */
	0,						/* tp_traverse */
	0,						/* tp_clear */
	0,						/* tp_richcompare */
	0,						/* tp_weaklistoffset */
	0,						/* tp_iter */
	0,						/* tp_iternext */
	0,						/* tp_methods */
	PySfEventSize_members,	/* tp_members */
	0,						/* tp_getset */
	0,						/* tp_base */
	0,						/* tp_dict */
	0,						/* tp_descr_get */
	0,						/* tp_descr_set */
	0,						/* tp_dictoffset */
	(initproc)PySfEventSize_init, /* tp_init */
	0,						/* tp_alloc */
};






////////////////////////////////////
// sfEvent
////////////////////////////////////


static int
PySfEvent_init(PySfEvent *self, PyObject *args, PyObject *kwds)
{
	self->obj = new sf::Event();
	return 0;
}

static PyObject *
PySfEvent_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
	PySfEvent *self;

	self = (PySfEvent *)type->tp_alloc(type, 0);
	if (self != NULL)
	{
		self->Text = PyObject_New(PySfEventText, &PySfEventTextType);
		self->Key = PyObject_New(PySfEventKey, &PySfEventKeyType);
		// self->Key = (PySfEventKey*) PyType_GenericNew(&PySfEventKeyType, Py_None, Py_None);
		self->MouseMove = PyObject_New(PySfEventMouseMove, &PySfEventMouseMoveType);
		self->MouseButton = PyObject_New(PySfEventMouseButton, &PySfEventMouseButtonType);
		self->MouseWheel = PyObject_New(PySfEventMouseWheel, &PySfEventMouseWheelType);
		self->JoyMove = PyObject_New(PySfEventJoyMove, &PySfEventJoyMoveType);
		self->JoyButton = PyObject_New(PySfEventJoyButton, &PySfEventJoyButtonType);
		self->Size = PyObject_New(PySfEventSize, &PySfEventSizeType);
	}

	return (PyObject *)self;
}

static void
PySfEvent_dealloc(PySfEvent* self)
{
	Py_DECREF(self->Text);
	Py_DECREF(self->Key);
	Py_DECREF(self->MouseMove);
	Py_DECREF(self->MouseButton);
	Py_DECREF(self->MouseWheel);
	Py_DECREF(self->JoyMove);
	Py_DECREF(self->JoyButton);
	Py_DECREF(self->Size);
	delete self->obj;
	self->ob_type->tp_free((PyObject*)self);
}

static PyMemberDef PySfEvent_members[] = {
	{"Text", T_OBJECT, offsetof(PySfEvent, Text), RO, "Text Events Parameters"},
	{"Key", T_OBJECT, offsetof(PySfEvent, Key), RO, "Keyboard Events Parameters"},
	{"MouseMove", T_OBJECT, offsetof(PySfEvent, MouseMove), RO, "MouseMove Events Parameters"},
	{"MouseButton", T_OBJECT, offsetof(PySfEvent, MouseButton), RO, "MouseButton Events Parameters"},
	{"MouseWheel", T_OBJECT, offsetof(PySfEvent, MouseWheel), RO, "MouseWheel Events Parameters"},
	{"JoyMove", T_OBJECT, offsetof(PySfEvent, JoyMove), RO, "JoyMove Events Parameters"},
	{"JoyButton", T_OBJECT, offsetof(PySfEvent, JoyButton), RO, "JoyButton Events Parameters"},
	{"Size", T_OBJECT, offsetof(PySfEvent, Size), RO, "Size Events Parameters"},
	{"Type", T_UINT, offsetof(PySfEvent, Type), RO, "Type Events Parameters"},
	{NULL}  /* Sentinel */
};

static PyMethodDef PySfEvent_methods[] = {
	{NULL}  /* Sentinel */
};

PyTypeObject PySfEventType = {
	PyObject_HEAD_INIT(NULL)
	0,						/*ob_size*/
	"Event",				/*tp_name*/
	sizeof(PySfEvent),		/*tp_basicsize*/
	0,						/*tp_itemsize*/
	(destructor)PySfEvent_dealloc, /*tp_dealloc*/
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
	"sfEvent defines a system event and its parameters", /* tp_doc */
	0,						/* tp_traverse */
	0,						/* tp_clear */
	0,						/* tp_richcompare */
	0,						/* tp_weaklistoffset */
	0,						/* tp_iter */
	0,						/* tp_iternext */
	PySfEvent_methods,		/* tp_methods */
	PySfEvent_members,		/* tp_members */
	0,						/* tp_getset */
	0,						/* tp_base */
	0,						/* tp_dict */
	0,						/* tp_descr_get */
	0,						/* tp_descr_set */
	0,						/* tp_dictoffset */
	(initproc)PySfEvent_init, /* tp_init */
	0,						/* tp_alloc */
	PySfEvent_new,			/* tp_new */
};




void
initEvents(void)
{
	PySfEventTextType.tp_new = PyType_GenericNew;
	PySfEventKeyType.tp_new = PyType_GenericNew;
	PySfEventMouseMoveType.tp_new = PyType_GenericNew;
	PySfEventMouseButtonType.tp_new = PyType_GenericNew;
	PySfEventMouseWheelType.tp_new = PyType_GenericNew;
	PySfEventJoyMoveType.tp_new = PyType_GenericNew;
	PySfEventJoyButtonType.tp_new = PyType_GenericNew;
	PySfEventSizeType.tp_new = PyType_GenericNew;
}


void
PySfEvent_InitConst()
{
	PyObject *obj;
	obj = PyInt_FromLong(sf::Event::KeyReleased);
	PyDict_SetItemString(PySfEventType.tp_dict, "KeyReleased", obj);
	Py_DECREF(obj);
	obj = PyInt_FromLong(sf::Event::LostFocus);
	PyDict_SetItemString(PySfEventType.tp_dict, "LostFocus", obj);
	Py_DECREF(obj);
	obj = PyInt_FromLong(sf::Event::GainedFocus);
	PyDict_SetItemString(PySfEventType.tp_dict, "GainedFocus", obj);
	Py_DECREF(obj);
	obj = PyInt_FromLong(sf::Event::KeyPressed);
	PyDict_SetItemString(PySfEventType.tp_dict, "KeyPressed", obj);
	Py_DECREF(obj);
	obj = PyInt_FromLong(sf::Event::MouseWheelMoved);
	PyDict_SetItemString(PySfEventType.tp_dict, "MouseWheelMoved", obj);
	Py_DECREF(obj);
	obj = PyInt_FromLong(sf::Event::TextEntered);
	PyDict_SetItemString(PySfEventType.tp_dict, "TextEntered", obj);
	Py_DECREF(obj);
	obj = PyInt_FromLong(sf::Event::MouseMoved);
	PyDict_SetItemString(PySfEventType.tp_dict, "MouseMoved", obj);
	Py_DECREF(obj);
	obj = PyInt_FromLong(sf::Event::JoyButtonPressed);
	PyDict_SetItemString(PySfEventType.tp_dict, "JoyButtonPressed", obj);
	Py_DECREF(obj);
	obj = PyInt_FromLong(sf::Event::MouseButtonReleased);
	PyDict_SetItemString(PySfEventType.tp_dict, "MouseButtonReleased", obj);
	Py_DECREF(obj);
	obj = PyInt_FromLong(sf::Event::Closed);
	PyDict_SetItemString(PySfEventType.tp_dict, "Closed", obj);
	Py_DECREF(obj);
	obj = PyInt_FromLong(sf::Event::MouseButtonPressed);
	PyDict_SetItemString(PySfEventType.tp_dict, "MouseButtonPressed", obj);
	Py_DECREF(obj);
	obj = PyInt_FromLong(sf::Event::JoyMoved);
	PyDict_SetItemString(PySfEventType.tp_dict, "JoyMoved", obj);
	Py_DECREF(obj);
	obj = PyInt_FromLong(sf::Event::JoyButtonReleased);
	PyDict_SetItemString(PySfEventType.tp_dict, "JoyButtonReleased", obj);
	Py_DECREF(obj);
	obj = PyInt_FromLong(sf::Event::Resized);
	PyDict_SetItemString(PySfEventType.tp_dict, "Resized", obj);
	Py_DECREF(obj);
}

