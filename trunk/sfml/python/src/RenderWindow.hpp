#ifndef __PYRENDERWINDOW_HPP
#define __PYRENDERWINDOW_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

#include <Python.h>
#include <structmember.h>

#include "WindowSettings.hpp"

typedef struct {
	PyObject_HEAD
	PySfWindowSettings *Settings;
	sf::RenderWindow *obj;
} PySfRenderWindow;


#endif
