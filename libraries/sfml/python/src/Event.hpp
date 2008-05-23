#ifndef __PYEVENT_HPP
#define __PYEVENT_HPP

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>

#include <Python.h>
#include <structmember.h>

typedef struct
{
	PyObject_HEAD
	unsigned int short Unicode;
} PySfEventText;

typedef struct
{
	PyObject_HEAD
	PyObject *Alt;
	PyObject *Control;
	PyObject *Shift;
	unsigned int Code;
} PySfEventKey;

typedef struct
{
	PyObject_HEAD
	unsigned int X;
	unsigned int Y;
} PySfEventMouseMove;

typedef struct
{
	PyObject_HEAD
	unsigned int Button;
} PySfEventMouseButton;

typedef struct
{
	PyObject_HEAD
	int Delta;
} PySfEventMouseWheel;

typedef struct {
	PyObject_HEAD
	unsigned int JoystickId;
	unsigned int Axis;
	float Position;
} PySfEventJoyMove;

typedef struct {
	PyObject_HEAD
	unsigned int JoystickId;
	unsigned int Button;
} PySfEventJoyButton;

typedef struct
{
	PyObject_HEAD
	unsigned int Width;
	unsigned int Height;
} PySfEventSize;

typedef struct {
	PyObject_HEAD
	PySfEventText *Text;
	PySfEventKey *Key;
	PySfEventMouseMove *MouseMove;
	PySfEventMouseButton *MouseButton;
	PySfEventMouseWheel *MouseWheel;
	PySfEventJoyMove *JoyMove;
	PySfEventJoyButton *JoyButton;
	PySfEventSize *Size;
	unsigned int Type;
	sf::Event *obj;
} PySfEvent;

void
initEvents(void);

void
PySfEvent_InitConst();

#endif
