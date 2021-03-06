#include "View.hpp"

extern PyTypeObject PySfFloatRectType;

static PyMemberDef PySfView_members[] = {
	{NULL}  /* Sentinel */
};


static void
PySfView_dealloc(PySfView *self)
{
	delete self->obj;
	self->ob_type->tp_free((PyObject*)self);
}

static PyObject *
PySfView_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
	PySfView *self;

	self = (PySfView *)type->tp_alloc(type, 0);
	if (self != NULL)
	{
	}

	return (PyObject *)self;
}

static int
PySfView_init(PySfView *self, PyObject *args, PyObject *kwds)
{
	PySfFloatRect *Rect=NULL;
	if (! PyArg_ParseTuple(args, "|O!", &PySfFloatRectType, &Rect))
		return -1;

	if (Rect != NULL)
		self->obj = new sf::View( (const sf::FloatRect) *(Rect->obj));
	else
		self->obj = new sf::View();

	return 0;
}

static PyObject *
PySfView_GetCenter(PySfView* self)
{
	sf::Vector2f Vect = self->obj->GetCenter();
	return Py_BuildValue("ff", Vect.x, Vect.y);
}

static PyObject *
PySfView_GetHalfSize(PySfView* self)
{
	sf::Vector2f Vect = self->obj->GetHalfSize();
	return Py_BuildValue("ff", Vect.x, Vect.y);
}

static PyObject *
PySfView_GetRect(PySfView* self)
{
	PySfFloatRect *Rect = GetNewPySfFloatRect();
	Rect->obj = new sf::FloatRect(self->obj->GetRect());
	Rect->Left = Rect->obj->Left;
	Rect->Right = Rect->obj->Right;
	Rect->Top = Rect->obj->Top;
	Rect->Bottom = Rect->obj->Bottom;
	return (PyObject *)Rect;
}

static PyObject *
PySfView_Move(PySfView* self, PyObject *args)
{
	float x, y;
	if ( !PyArg_ParseTuple(args, "ff", &x, &y) )
		return NULL;
	self->obj->Move(x, y);
	Py_RETURN_NONE;
}

static PyObject *
PySfView_SetCenter(PySfView* self, PyObject *args)
{
	float x, y;
	if ( !PyArg_ParseTuple(args, "ff", &x, &y) )
		return NULL;
	self->obj->SetCenter(x, y);
	Py_RETURN_NONE;
}

static PyObject *
PySfView_SetHalfSize(PySfView* self, PyObject *args)
{
	float x, y;
	if ( !PyArg_ParseTuple(args, "ff", &x, &y) )
		return NULL;
	self->obj->SetHalfSize(x, y);
	Py_RETURN_NONE;
}

static PyObject *
PySfView_Zoom(PySfView* self, PyObject *args)
{
	self->obj->Zoom(PyFloat_AsDouble(args));
	Py_RETURN_NONE;
}

static PyMethodDef PySfView_methods[] = {
	{"GetCenter", (PyCFunction)PySfView_GetCenter, METH_NOARGS, "Get the center of the view."},
	{"GetHalfSize", (PyCFunction)PySfView_GetHalfSize, METH_NOARGS, "Get the half-size of the view."},
	{"GetRect", (PyCFunction)PySfView_GetRect, METH_NOARGS, "Get the bounding rectangle of the view."},
	{"Move", (PyCFunction)PySfView_Move, METH_VARARGS, "Move the view."},
	{"SetCenter", (PyCFunction)PySfView_SetCenter, METH_VARARGS, "Change the center of the view."},
	{"SetHalfSize", (PyCFunction)PySfView_SetHalfSize, METH_VARARGS, "Change the half-size of the view."},
	{"Zoom", (PyCFunction)PySfView_Zoom, METH_O, "Resize the view rectangle to simulate a zoom / unzoom effect."},
	{NULL}  /* Sentinel */
};

PyTypeObject PySfViewType = {
	PyObject_HEAD_INIT(NULL)
	0,					/*ob_size*/
	"View",				/*tp_name*/
	sizeof(PySfView),	/*tp_basicsize*/
	0,					/*tp_itemsize*/
	(destructor)PySfView_dealloc, /*tp_dealloc*/
	0,					/*tp_print*/
	0,					/*tp_getattr*/
	0,					/*tp_setattr*/
	0,					/*tp_compare*/
	0,					/*tp_repr*/
	0,					/*tp_as_number*/
	0,					/*tp_as_sequence*/
	0,					/*tp_as_mapping*/
	0,					/*tp_hash */
	0,					/*tp_call*/
	0,					/*tp_str*/
	0,					/*tp_getattro*/
	0,					/*tp_setattro*/
	0,					/*tp_as_buffer*/
	Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /*tp_flags*/
	"This class defines a view (position, size, etc.) ; you can consider it as a 2D camera.", /* tp_doc */
	0,					/* tp_traverse */
	0,					/* tp_clear */
	0,					/* tp_richcompare */
	0,					/* tp_weaklistoffset */
	0,					/* tp_iter */
	0,					/* tp_iternext */
	PySfView_methods,	/* tp_methods */
	PySfView_members,	/* tp_members */
	0,					/* tp_getset */
	0,					/* tp_base */
	0,					/* tp_dict */
	0,					/* tp_descr_get */
	0,					/* tp_descr_set */
	0,					/* tp_dictoffset */
	(initproc)PySfView_init, /* tp_init */
	0,					/* tp_alloc */
	PySfView_new,		/* tp_new */
};

PySfView *
GetNewPySfView()
{
	return PyObject_New(PySfView, &PySfViewType);
}

