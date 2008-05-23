#ifndef __PYWINDOWSETTINGS_HPP
#define __PYWINDOWSETTINGS_HPP

#include <SFML/Window/WindowSettings.hpp>
#include <iostream>

#include <Python.h>
#include <structmember.h>

#include "offsetof.hpp"


typedef struct {
	PyObject_HEAD
	unsigned int DepthBits;
	unsigned int StencilBits;
	unsigned int AntialiasingLevel;
	sf::WindowSettings *obj;
} PySfWindowSettings;

void
PySfWindowSettingsUpdate(PySfWindowSettings *self);

PySfWindowSettings *
GetNewPySfWindowSettings();

#endif
