#pragma once
#include <GL/glew.h>
#include "gl/gl_utils.h"
#include "gl/shader/graphic_shader.h"
#include "gl/shader/shader.h"
#include <QKeyEvent>
#include <QMouseEvent>

class Component {
public:
    Component();
    ~Component();

    virtual void resize(int w, int h);
    virtual void init();
    virtual void draw();
    virtual void setUniforms(Shader* shader);

    virtual void keyPressEvent(QKeyEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);

    virtual bool isPointInside(float x, float y) const;

    // Window size accessors
    int width() const { return _width; }
    int height() const { return _height; }

protected:
    int _width = 0;
    int _height = 0;
};