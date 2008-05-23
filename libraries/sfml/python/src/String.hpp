#ifndef __PYSTRING_HPP
#define __PYSTRING_HPP

#include <SFML/Graphics/String.hpp>
#include <iostream>

#include <Python.h>
#include <structmember.h>

typedef struct {
	PyObject_HEAD
	sf::String *obj;
} PySfString;

void PySfString_InitConst();

#endif
