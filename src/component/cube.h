#pragma once

#include "drawableComponent.h"
#include <glm/glm.hpp>
#include <memory>

class ColorWidget;

class Cube : public DrawableComponent {
public:
    Cube();
    Cube(const std::string& texturePath);
    ~Cube();

    void init() override;
    void draw(Shader* shader) override;

    void mousePressEvent(QMouseEvent *event) override;

protected:
    const float* getVertices() const override { return _vertices; }
    size_t getVertexCount() const override { return sizeof(_vertices) / (5 * sizeof(float)); }
    size_t getVertexStride() const override { return 5; }
    const GLuint* getIndices() const override { return _indices; }
    size_t getIndexCount() const override { return sizeof(_indices) / sizeof(_indices[0]); }

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