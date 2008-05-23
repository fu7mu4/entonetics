#ifndef __PYDRAWABLE_H
#define __PYDRAWABLE_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <Python.h>
#include <structmember.h>

#include "Color.hpp"
#include "RenderWindow.hpp"


class CustomDrawable : public sf::Drawable
{
protected :
	virtual void Render(const sf::RenderWindow& Window) const;
public :
	PySfRenderWindow *RenderWindow;
	PyObject *RenderFunction;
};


typedef struct {
	PyObject_HEAD
	CustomDrawable *obj;
} PySfDrawable;

#endif

