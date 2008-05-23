#include "Sleep.hpp"

PyObject *
PySFML_Sleep (PyObject *self, PyObject *args)
{
	sf::Sleep(PyFloat_AsDouble(args));
	Py_RETURN_NONE;
}

