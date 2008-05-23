#ifndef __PYVIDEOMODE_HPP
#define __PYVIDEOMODE_HPP

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>

#include <Python.h>
#include <structmember.h>

#include "offsetof.hpp"


typedef struct {
	PyObject_HEAD
	unsigned int Width;
	unsigned int Height;
	unsigned int BitsPerPixel;
	sf::VideoMode *obj;
} PySfVideoMode;

void
PySfVideoModeUpdate(PySfVideoMode *self);

PySfVideoMode *
GetNewPySfVideoMode();

#endif
