#ifndef __PYSPRITE_HPP
#define __PYSPRITE_HPP

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Image.hpp>
#include <iostream>

#include <Python.h>
#include <structmember.h>

#include "Drawable.hpp"
#include "Image.hpp"
#include "Rect.hpp"

typedef struct {
	PyObject_HEAD
	sf::Sprite *obj;
	PySfImage *Image;
} PySfSprite;

#endif
