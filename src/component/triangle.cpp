#include "triangle.h"

Triangle::Triangle() = default;

Triangle::~Triangle() = default;

void Triangle::init()
{
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    GL(glGenVertexArrays(1, &_VAO));
    GL(glBindVertexArray(_VAO));

    GLuint VBO;
    GL(glGenBuffers(1, &VBO));
    GL(glBindBuffer(GL_ARRAY_BUFFER, VBO));
    GL(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));

    GL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0));
    GL(glEnableVertexAttribArray(0));

    GL(glBindVertexArray(0));
}

void Triangle::draw()
{
    GL(glBindVertexArray(_VAO));
    GL(glDrawArrays(GL_TRIANGLES, 0, 3));
}