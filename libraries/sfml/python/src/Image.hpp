#ifndef __PYIMAGE_HPP
#define __PYIMAGE_HPP

#include <SFML/Graphics/Image.hpp>
#include <iostream>

#include <Python.h>
#include <structmember.h>

#include "Color.hpp"
#include "Rect.hpp"

#include "offsetof.hpp"


typedef struct {
	PyObject_HEAD
	sf::Image *obj;
} PySfImage;

PySfImage *
GetNewPySfImage();

#endif

