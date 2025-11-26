#pragma once
#include <GL/glew.h>
#include "gl/gl_utils.h"
#include "gl/shader/graphic_shader.h"
#include "gl/shader/shader.h"
#include <QKeyEvent>
#include <QMouseEvent>
#include <glm/glm.hpp>

class Component {
public:
    Component();
    ~Component();

    virtual void resize(int w, int h);
    virtual void init();
    virtual void draw(Shader* shader);

    virtual void keyPressEvent(QKeyEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);

    int getWidth() const { return _width; }
    int getHeight() const { return _height; }

    virtual void setPosition(const glm::vec3& position) { _position = position; }
    virtual void setRotation(const glm::vec3& rotation) { _rotation = rotation; }
    virtual void setScale(const glm::vec3& scale) { _scale = scale; }
    
    glm::vec3 getPosition() const { return _position; }
    glm::vec3 getRotation() const { return _rotation; }
    glm::vec3 getScale() const { return _scale; }

protected:
    glm::vec3 _position = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 _rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 _scale = glm::vec3(1.0f, 1.0f, 1.0f);

private:
    int _width = 0;
    int _height = 0;
};