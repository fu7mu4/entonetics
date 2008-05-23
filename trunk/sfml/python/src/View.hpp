#ifndef __PYVIEW_HPP
#define __PYVIEW_HPP

#include <SFML/Graphics/View.hpp>
#include <iostream>

#include "Rect.hpp"

#include <Python.h>
#include <structmember.h>

#include "offsetof.hpp"

typedef struct {
	PyObject_HEAD
	sf::View *obj;
} PySfView;

PySfView *
GetNewPySfView();

#endif
