#pragma once
#include <GL/glew.h>
#include "gl/gl_utils.h"

class Component {
public:
    Component();
    ~Component();

    virtual void init();
    virtual void draw();
};