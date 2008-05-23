#ifndef __PYWINDOW_HPP
#define __PYWINDOW_HPP

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>

#include <Python.h>
#include <structmember.h>

#include "Event.hpp"
#include "VideoMode.hpp"
#include "Input.hpp"
#include "WindowSettings.hpp"


typedef struct {
	PyObject_HEAD
	PySfWindowSettings *Settings;
	sf::Window *obj;
} PySfWindow;


#endif
