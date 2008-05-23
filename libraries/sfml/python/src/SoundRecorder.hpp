#ifndef __PYSOUNDRECORDER_HPP
#define __PYSOUNDRECORDER_HPP

#include <SFML/Audio/SoundRecorder.hpp>
#include <iostream>

#include <Python.h>
#include <structmember.h>

#include "offsetof.hpp"


typedef struct {
	PyObject_HEAD
	sf::SoundRecorder *obj;
	PyObject *Callback;
	PyObject *UserData;
} PySfSoundRecorder;

#endif
