#include "triangle.h"
#include "widget/widgetColor.h"
#include <cmath>
#include <QMouseEvent>
#include <QObject>

Triangle::Triangle() :
    _vertices{
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    },
    _color(1.0f, 0.0f, 0.0f, 1.0f)
{
}

Triangle::~Triangle() = default;

void Triangle::init()
{
    GL(glGenVertexArrays(1, &_VAO));
    GL(glBindVertexArray(_VAO));

    GLuint VBO;
    GL(glGenBuffers(1, &VBO));
    GL(glBindBuffer(GL_ARRAY_BUFFER, VBO));
    GL(glBufferData(GL_ARRAY_BUFFER, sizeof(_vertices), _vertices, GL_STATIC_DRAW));

    GL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0));
    GL(glEnableVertexAttribArray(0));

    GL(glBindVertexArray(0));
}

void Triangle::draw()
{
    GL(glBindVertexArray(_VAO));
    GL(glDrawArrays(GL_TRIANGLES, 0, 3));
}

void Triangle::setUniforms(Shader* shader)
{
    if (shader) {
        shader->setUniformAttrib("color", _color);
    }
}

void Triangle::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton) {
        float mouseX = event->position().x();
        float mouseY = event->position().y();
        
        float ndcX = (2.0f * mouseX / this->width()) - 1.0f;
        float ndcY = 1.0f - (2.0f * mouseY / this->height());
        
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

bool Triangle::isPointInside(float x, float y) const
{
    float v0x = _vertices[0], v0y = _vertices[1];
    float v1x = _vertices[3], v1y = _vertices[4];
    float v2x = _vertices[6], v2y = _vertices[7];

    float v0v1x = v1x - v0x, v0v1y = v1y - v0y;
    float v0v2x = v2x - v0x, v0v2y = v2y - v0y;
    float v0px = x - v0x, v0py = y - v0y;

    float dot00 = v0v2x * v0v2x + v0v2y * v0v2y;
    float dot01 = v0v2x * v0v1x + v0v2y * v0v1y;
    float dot02 = v0v2x * v0px + v0v2y * v0py;
    float dot11 = v0v1x * v0v1x + v0v1y * v0v1y;
    float dot12 = v0v1x * v0px + v0v1y * v0py;

    float invDenom = 1.0f / (dot00 * dot11 - dot01 * dot01);
    float u = (dot11 * dot02 - dot01 * dot12) * invDenom;
    float v = (dot00 * dot12 - dot01 * dot02) * invDenom;

    return (u >= 0.0f) && (v >= 0.0f) && (u + v <= 1.0f);
}