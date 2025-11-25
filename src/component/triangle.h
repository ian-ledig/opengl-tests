#pragma once

#include "component.h"
#include <glm/glm.hpp>
#include <memory>

class ColorWidget;

class Triangle : public Component {
public:
    Triangle();
    ~Triangle();

    void init() override;
    void draw() override;
    void setUniforms(Shader* shader) override;
    
    void mousePressEvent(QMouseEvent *event) override;

    bool isPointInside(float x, float y) const override;

private:    
    GLuint _VAO;
    float _vertices[9];
    
    glm::vec4 _color;
    std::unique_ptr<ColorWidget> _colorWidget;
};