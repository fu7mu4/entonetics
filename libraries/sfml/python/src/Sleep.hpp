#ifndef __PYSLEEP_HPP
#define __PYSLEEP_HPP

#include <SFML/System/Sleep.hpp>
#include <iostream>

#include <Python.h>
#include <structmember.h>

PyObject *
PySFML_Sleep (PyObject *self, PyObject *args);

#endif
