#pragma once
#include <GL/glew.h>
#include "gl/gl_utils.h"
#include "gl/shader/graphic_shader.h"
#include "gl/shader/shader.h"
#include <QKeyEvent>
#include <QMouseEvent>
#include "gl/texture.h"

class Component {
public:
    Component();
    Component(const std::string& texturePath);
    ~Component();

    virtual void resize(int w, int h);
    virtual void init();
    virtual void draw(Shader* shader);

    virtual void keyPressEvent(QKeyEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);

    virtual bool isPointInside(float x, float y) const;

    int getWidth() const { return _width; }
    int getHeight() const { return _height; }
    gl::Texture2D* getTexture() const { return _texture.get(); }

private:
    int _width = 0;
    int _height = 0;

    std::unique_ptr<gl::Texture2D> _texture;

    void loadTexture(const std::string& texturePath);
};