#include "component.h"
#include <glm/glm.hpp>

Component::Component()
{
}

Component::~Component() = default;

void Component::resize(int w, int h)
{
    _width = w;
    _height = h;
}

void Component::init()
{
}

void Component::draw(Shader* shader)
{
    if (!shader) return;
}

void Component::keyPressEvent(QKeyEvent *event)
{
}

void Component::mousePressEvent(QMouseEvent *event)
{
}