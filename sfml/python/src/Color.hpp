#ifndef __PYCOLOR_HPP
#define __PYCOLOR_HPP

#include <SFML/Graphics/Color.hpp>
#include <iostream>

#include <Python.h>
#include <structmember.h>

#include "offsetof.hpp"


typedef struct {
	PyObject_HEAD
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
	sf::Color *obj;
} PySfColor;

PySfColor *
GetNewPySfColor();

void
PySfColorUpdate(PySfColor *self);

void
PySfColor_InitConst();

#endif
