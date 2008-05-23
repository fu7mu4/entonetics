#ifndef __PYRECT_HPP
#define __PYRECT_HPP


#include <SFML/Graphics/Rect.hpp>
#include <iostream>

#include <Python.h>
#include <structmember.h>

#include "offsetof.hpp"

typedef struct {
	PyObject_HEAD
	int Left;
	int Right;
	int Top;
	int Bottom;
	sf::IntRect *obj;
} PySfIntRect;

typedef struct {
	PyObject_HEAD
	float Left;
	float Right;
	float Top;
	float Bottom;
	sf::FloatRect *obj;
} PySfFloatRect;

PySfIntRect *
GetNewPySfIntRect();

PySfFloatRect *
GetNewPySfFloatRect();

void
PySfIntRectUpdate(PySfIntRect *self);

void
PySfFloatRectUpdate(PySfFloatRect *self);


#endif
