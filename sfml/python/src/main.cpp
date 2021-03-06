#include "main.hpp"

#include "Color.hpp"
#include "Key.hpp"
#include "Joy.hpp"
#include "Event.hpp"
#include "Mouse.hpp"
#include "WindowStyle.hpp"
#include "Blend.hpp"
#include "Sound.hpp"
#include "String.hpp"


extern PyTypeObject PySfClockType;

extern PyTypeObject PySfEventType;
extern PyTypeObject PySfEventTextType;
extern PyTypeObject PySfEventKeyType;
extern PyTypeObject PySfEventMouseMoveType;
extern PyTypeObject PySfEventMouseButtonType;
extern PyTypeObject PySfEventMouseWheelType;
extern PyTypeObject PySfEventJoyMoveType;
extern PyTypeObject PySfEventJoyButtonType;
extern PyTypeObject PySfEventSizeType;
extern PyTypeObject PySfKeyType;
extern PyTypeObject PySfJoyType;
extern PyTypeObject PySfMouseType;

extern PyTypeObject PySfVideoModeType;
extern PyTypeObject PySfWindowType;
extern PyTypeObject PySfWindowSettingsType;
extern PyTypeObject PySfStyleType;
extern PyTypeObject PySfRenderWindowType;
extern PyTypeObject PySfViewType;
extern PyTypeObject PySfInputType;

extern PyTypeObject PySfDrawableType;
extern PyTypeObject PySfBlendType;
extern PyTypeObject PySfSpriteType;
extern PyTypeObject PySfFontType;
extern PyTypeObject PySfStringType;
extern PyTypeObject PySfPostFXType;

extern PyTypeObject PySfImageType;

extern PyTypeObject PySfColorType;

extern PyTypeObject PySfShapeType;

extern PyTypeObject PySfIntRectType;
extern PyTypeObject PySfFloatRectType;

extern PyTypeObject PySfMusicType;
extern PyTypeObject PySfSoundType;
extern PyTypeObject PySfSoundBufferType;
extern PyTypeObject PySfSoundRecorderType;
extern PyTypeObject PySfSoundBufferRecorderType;
extern PyTypeObject PySfListenerType;


static PyMethodDef module_methods[] = {
	{"Sleep", (PyCFunction)PySFML_Sleep, METH_O, "Sleeps during the specified duration."},
	{NULL}  /* Sentinel */
};

#ifndef PyMODINIT_FUNC	/* declarations for DLL import/export */
#define PyMODINIT_FUNC void
#endif
PyMODINIT_FUNC
initsf(void) 
{
    PyObject *m;

	initEvents();

	if (PyType_Ready(&PySfClockType) < 0)
		return;

	if (PyType_Ready(&PySfWindowType) < 0)
		return;
	if (PyType_Ready(&PySfWindowSettingsType) < 0)
		return;
	if (PyType_Ready(&PySfStyleType) < 0)
		return;
	if (PyType_Ready(&PySfRenderWindowType) < 0)
		return;
	if (PyType_Ready(&PySfVideoModeType) < 0)
		return;
	if (PyType_Ready(&PySfViewType) < 0)
		return;
	if (PyType_Ready(&PySfInputType) < 0)
		return;

	if (PyType_Ready(&PySfEventType) < 0)
		return;
	if (PyType_Ready(&PySfEventTextType) < 0)
		return;
	if (PyType_Ready(&PySfEventKeyType) < 0)
		return;
	if (PyType_Ready(&PySfEventMouseMoveType) < 0)
		return;
	if (PyType_Ready(&PySfEventMouseButtonType) < 0)
		return;
	if (PyType_Ready(&PySfEventMouseWheelType) < 0)
		return;
	if (PyType_Ready(&PySfEventJoyMoveType) < 0)
		return;
	if (PyType_Ready(&PySfEventJoyButtonType) < 0)
		return;
	if (PyType_Ready(&PySfEventSizeType) < 0)
		return;
	if (PyType_Ready(&PySfKeyType) < 0)
		return;
	if (PyType_Ready(&PySfJoyType) < 0)
		return;
	if (PyType_Ready(&PySfMouseType) < 0)
		return;

	if (PyType_Ready(&PySfDrawableType) < 0)
		return;
	if (PyType_Ready(&PySfBlendType) < 0)
		return;
	if (PyType_Ready(&PySfSpriteType) < 0)
		return;
	if (PyType_Ready(&PySfFontType) < 0)
		return;
	if (PyType_Ready(&PySfStringType) < 0)
		return;
	if (PyType_Ready(&PySfPostFXType) < 0)
		return;

	if (PyType_Ready(&PySfImageType) < 0)
		return;

	if (PyType_Ready(&PySfShapeType) < 0)
		return;

	if (PyType_Ready(&PySfColorType) < 0)
		return;

	if (PyType_Ready(&PySfIntRectType) < 0)
		return;
	if (PyType_Ready(&PySfFloatRectType) < 0)
		return;

	if (PyType_Ready(&PySfMusicType) < 0)
		return;
	if (PyType_Ready(&PySfSoundType) < 0)
		return;
	if (PyType_Ready(&PySfSoundBufferType) < 0)
		return;
	if (PyType_Ready(&PySfSoundBufferRecorderType) < 0)
		return;
	if (PyType_Ready(&PySfSoundRecorderType) < 0)
		return;
	if (PyType_Ready(&PySfListenerType) < 0)
		return;

	m = Py_InitModule3("sf", module_methods, "Python binding for sfml (Simple Fast Media Library)");

	if (m == NULL)
		return;

	Py_INCREF(&PySfClockType);
	PyModule_AddObject(m, "Clock", (PyObject *)&PySfClockType);

	Py_INCREF(&PySfWindowType);
	PyModule_AddObject(m, "Window", (PyObject *)&PySfWindowType);
	Py_INCREF(&PySfWindowSettingsType);
	PyModule_AddObject(m, "WindowSettings", (PyObject *)&PySfWindowSettingsType);
	Py_INCREF(&PySfStyleType);
	PyModule_AddObject(m, "Style", (PyObject *)&PySfStyleType);
	Py_INCREF(&PySfRenderWindowType);
	PyModule_AddObject(m, "RenderWindow", (PyObject *)&PySfRenderWindowType);
	Py_INCREF(&PySfVideoModeType);
	PyModule_AddObject(m, "VideoMode", (PyObject *)&PySfVideoModeType);
	Py_INCREF(&PySfViewType);
	PyModule_AddObject(m, "View", (PyObject *)&PySfViewType);
	Py_INCREF(&PySfInputType);
	PyModule_AddObject(m, "Input", (PyObject *)&PySfInputType);

	Py_INCREF(&PySfDrawableType);
	PyModule_AddObject(m, "Drawable", (PyObject *)&PySfDrawableType);
	Py_INCREF(&PySfBlendType);
	PyModule_AddObject(m, "Blend", (PyObject *)&PySfBlendType);
	Py_INCREF(&PySfSpriteType);
	PyModule_AddObject(m, "Sprite", (PyObject *)&PySfSpriteType);
	Py_INCREF(&PySfFontType);
	PyModule_AddObject(m, "Font", (PyObject *)&PySfFontType);
	Py_INCREF(&PySfStringType);
	PyModule_AddObject(m, "String", (PyObject *)&PySfStringType);
	Py_INCREF(&PySfPostFXType);
	PyModule_AddObject(m, "PostFX", (PyObject *)&PySfPostFXType);

	Py_INCREF(&PySfEventType);
	PyModule_AddObject(m, "Event", (PyObject *)&PySfEventType);
	Py_INCREF(&PySfKeyType);
	PyModule_AddObject(m, "Key", (PyObject *)&PySfKeyType);
	Py_INCREF(&PySfJoyType);
	PyModule_AddObject(m, "Joy", (PyObject *)&PySfJoyType);
	Py_INCREF(&PySfMouseType);
	PyModule_AddObject(m, "Mouse", (PyObject *)&PySfMouseType);

	Py_INCREF(&PySfImageType);
	PyModule_AddObject(m, "Image", (PyObject *)&PySfImageType);

	Py_INCREF(&PySfColorType);
	PyModule_AddObject(m, "Color", (PyObject *)&PySfColorType);

	Py_INCREF(&PySfShapeType);
	PyModule_AddObject(m, "Shape", (PyObject *)&PySfShapeType);

	Py_INCREF(&PySfIntRectType);
	PyModule_AddObject(m, "IntRect", (PyObject *)&PySfIntRectType);
	Py_INCREF(&PySfFloatRectType);
	PyModule_AddObject(m, "FloatRect", (PyObject *)&PySfFloatRectType);

	Py_INCREF(&PySfMusicType);
	PyModule_AddObject(m, "Music", (PyObject *)&PySfMusicType);
	Py_INCREF(&PySfSoundType);
	PyModule_AddObject(m, "Sound", (PyObject *)&PySfSoundType);
	Py_INCREF(&PySfSoundBufferType);
	PyModule_AddObject(m, "SoundBuffer", (PyObject *)&PySfSoundBufferType);
	Py_INCREF(&PySfSoundRecorderType);
	PyModule_AddObject(m, "SoundRecorder", (PyObject *)&PySfSoundRecorderType);
	Py_INCREF(&PySfSoundBufferRecorderType);
	PyModule_AddObject(m, "SoundBufferRecorder", (PyObject *)&PySfSoundBufferRecorderType);
	Py_INCREF(&PySfListenerType);
	PyModule_AddObject(m, "Listener", (PyObject *)&PySfListenerType);


	PySfColor_InitConst();
	PySfKey_InitConst();
	PySfJoy_InitConst();
	PySfEvent_InitConst();
	PySfMouse_InitConst();
	PySfStyle_InitConst();
	PySfBlend_InitConst();
	PySfSound_InitConst();
	PySfString_InitConst();
}

