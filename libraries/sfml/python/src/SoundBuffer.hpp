#ifndef __PYSOUNDBUFFER_HPP
#define __PYSOUNDBUFFER_HPP

#include <SFML/Audio/SoundBuffer.hpp>
#include <iostream>

#include <Python.h>
#include <structmember.h>

typedef struct {
	PyObject_HEAD
	sf::SoundBuffer *obj;
} PySfSoundBuffer;

PySfSoundBuffer *
GetNewPySfSoundBuffer();

#endif
