#ifndef __PYINPUT_HPP
#define __PYINPUT_HPP

#include <SFML/Window/Input.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>

#include <Python.h>
#include <structmember.h>

typedef struct {
	PyObject_HEAD
	sf::Input *obj;
} PySfInput;

PySfInput *
GetNewPySfInput();

#endif
