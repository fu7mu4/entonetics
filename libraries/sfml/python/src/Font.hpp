#ifndef __PYFONT_HPP
#define __PYFONT_HPP

#include <SFML/Graphics/Font.hpp>
#include <iostream>

#include <Python.h>
#include <structmember.h>

#include "offsetof.hpp"


typedef struct {
	PyObject_HEAD
	sf::Font *obj;
} PySfFont;

PySfFont *
GetNewPySfFont();

#endif
