#ifndef __PYSOUNDBUFFERRECORDER_HPP
#define __PYSOUNDBUFFERRECORDER_HPP

#include <SFML/Audio/SoundBufferRecorder.hpp>
#include <iostream>

#include <Python.h>
#include <structmember.h>

#include "offsetof.hpp"

typedef struct {
	PyObject_HEAD
	sf::SoundBufferRecorder *obj;
} PySfSoundBufferRecorder;

#endif
