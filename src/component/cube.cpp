#include "cube.h"
#include "widget/widgetColor.h"
#include <cmath>
#include <QMouseEvent>
#include <QObject>

Cube::Cube()
    : DrawableComponent()
{
}

Cube::Cube(const std::string& texturePath) : DrawableComponent(texturePath)
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
    DrawableComponent::draw(shader);

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
