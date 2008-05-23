#ifndef __PYSHAPE_HPP
#define __PYSHAPE_HPP

#include <SFML/Graphics/Shape.hpp>
#include <iostream>

#include <Python.h>
#include <structmember.h>

#include "offsetof.hpp"


typedef struct {
	PyObject_HEAD
	sf::Shape *obj;
} PySfShape;

PySfShape *
GetNewPySfShape();

#endif
