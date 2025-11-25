#include "cube.h"
#include "widget/widgetColor.h"
#include <cmath>
#include <QMouseEvent>
#include <QObject>

Cube::Cube()
{
}

Cube::Cube(const std::string& texturePath) : Component(texturePath)
{
}

Cube::~Cube()
{
    if (_VAO != 0) {
        GL(glDeleteVertexArrays(1, &_VAO));
        _VAO = 0;
    }
    if (_VBO != 0) {
        GL(glDeleteBuffers(1, &_VBO));
        _VBO = 0;
    }
    if (_EBO != 0) {
        GL(glDeleteBuffers(1, &_EBO));
        _EBO = 0;
    }
}

void Cube::init()
{
    GL(glGenVertexArrays(1, &_VAO));
    GL(glBindVertexArray(_VAO));

    GL(glGenBuffers(1, &_VBO));
    GL(glBindBuffer(GL_ARRAY_BUFFER, _VBO));
    GL(glBufferData(GL_ARRAY_BUFFER, sizeof(_vertices), _vertices, GL_STATIC_DRAW));

    GL(glGenBuffers(1, &_EBO));
    GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO));
    GL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_indices), _indices, GL_STATIC_DRAW));

    GL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0));
    GL(glEnableVertexAttribArray(0));
    GL(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float))));
    GL(glEnableVertexAttribArray(1));
}

void Cube::draw(Shader* shader)
{
    if (!shader) {
        return;
    }

    shader->setUniformAttrib("color", _color);

    const auto texture = getTexture();
    const bool hasTexture = texture != nullptr;
    if (hasTexture) {
        GL(glActiveTexture(GL_TEXTURE0));
        texture->bind();
        shader->setUniformAttrib("textureSampler", 0);
    }
    shader->setUniformAttrib("useTexture", hasTexture);

    GL(glBindVertexArray(_VAO));
    GL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));
    GL(glBindVertexArray(0));
}

void Cube::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton) {
        float mouseX = event->position().x();
        float mouseY = event->position().y();
        
        float ndcX = (2.0f * mouseX / this->getWidth()) - 1.0f;
        float ndcY = 1.0f - (2.0f * mouseY / this->getHeight());
        
        if (isPointInside(ndcX, ndcY)) {
            if (!_colorWidget) {
                _colorWidget = std::make_unique<ColorWidget>();
                QObject::connect(_colorWidget.get(), &ColorWidget::colorChanged, 
                        [this](const glm::vec4& color) { _color = color; });
            }
            _colorWidget->setColor(_color);
            _colorWidget->show();
            _colorWidget->raise();
            _colorWidget->activateWindow();
        }
    }
}

bool Cube::isPointInside(float x, float y) const
{
    auto vertexAt = [this](GLuint index) {
        const size_t base = static_cast<size_t>(index) * 3;
        return glm::vec2{_vertices[base], _vertices[base + 1]};
    };

    auto pointInTriangle = [](const glm::vec2& p,
                              const glm::vec2& a,
                              const glm::vec2& b,
                              const glm::vec2& c) {
        const glm::vec2 v0 = c - a;
        const glm::vec2 v1 = b - a;
        const glm::vec2 v2 = p - a;

        const float dot00 = glm::dot(v0, v0);
        const float dot01 = glm::dot(v0, v1);
        const float dot02 = glm::dot(v0, v2);
        const float dot11 = glm::dot(v1, v1);
        const float dot12 = glm::dot(v1, v2);

        const float denom = dot00 * dot11 - dot01 * dot01;
        if (denom == 0.0f) {
            return false;
        }

        const float invDenom = 1.0f / denom;
        const float u = (dot11 * dot02 - dot01 * dot12) * invDenom;
        const float v = (dot00 * dot12 - dot01 * dot02) * invDenom;

        return (u >= 0.0f) && (v >= 0.0f) && (u + v <= 1.0f);
    };

    const glm::vec2 point{x, y};

    const size_t indexCount = sizeof(_indices) / sizeof(_indices[0]);
    for (size_t i = 0; i < indexCount; i += 3) {
        const glm::vec2 a = vertexAt(_indices[i]);
        const glm::vec2 b = vertexAt(_indices[i + 1]);
        const glm::vec2 c = vertexAt(_indices[i + 2]);
        if (pointInTriangle(point, a, b, c)) {
            return true;
        }
    }

    return false;
}