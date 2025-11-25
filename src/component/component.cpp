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

void Component::draw()
{
}

void Component::setUniforms(Shader* shader)
{
    if (shader) {
        shader->setUniformAttrib("color", glm::vec4(1.0f, 0.0f, 1.0f, 1.0f));
    }
}

void Component::keyPressEvent(QKeyEvent *event)
{
}

void Component::mousePressEvent(QMouseEvent *event)
{
}

bool Component::isPointInside(float x, float y) const
{
    return false;
}