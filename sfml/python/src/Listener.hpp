#ifndef __PYLISTENER_HPP
#define __PYLISTENER_HPP

#include <SFML/Audio/Listener.hpp>
#include <iostream>

#include <Python.h>
#include <structmember.h>

#include "offsetof.hpp"


typedef struct {
	PyObject_HEAD
} PySfListener;

#endif
