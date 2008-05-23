#ifndef __PYPOSTFX_HPP
#define __PYPOSTFX_HPP

#include <SFML/Graphics/PostFX.hpp>
#include <iostream>

#include <Python.h>
#include <structmember.h>

#include "Drawable.hpp"
#include "Image.hpp"

typedef struct {
	PyObject_HEAD
	sf::PostFX *obj;
} PySfPostFX;

#endif
