#ifndef __PYMUSIC_HPP
#define __PYMUSIC_HPP

#include <SFML/Audio/Music.hpp>
#include <iostream>

#include <Python.h>
#include <structmember.h>



typedef struct {
	PyObject_HEAD
	sf::Music *obj;
} PySfMusic;

#endif
