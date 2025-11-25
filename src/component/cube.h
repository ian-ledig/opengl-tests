#pragma once

#include "component.h"
#include <glm/glm.hpp>
#include <memory>

class ColorWidget;

class Cube : public Component {
public:
    Cube();
    Cube(const std::string& texturePath);
    ~Cube();

    void init() override;
    void draw(Shader* shader) override;

    void mousePressEvent(QMouseEvent *event) override;

    bool isPointInside(float x, float y) const override;

private:
    GLuint _VAO = 0;
    GLuint _VBO = 0;
    GLuint _EBO = 0;
    float _vertices[20] = {
        // x,    y,    z,    u,   v
        0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
       -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
       -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
    };
    GLuint _indices[6] = {
        0, 1, 3,
        1, 2, 3
    };
    glm::vec4 _color = {1.0f, 0.0f, 0.0f, 1.0f};
    std::unique_ptr<ColorWidget> _colorWidget;
};