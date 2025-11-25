#include "openGlWidget.h"
#include <iostream>
#include <chrono>
#include <iomanip>


OpenGLWidget::OpenGLWidget()
{
    setFocusPolicy(Qt::StrongFocus);
    setFocus();
    setMouseTracking(true);
}

OpenGLWidget::~OpenGLWidget() = default;

void OpenGLWidget::initializeGL()
{
    _loadStart = std::chrono::high_resolution_clock::now();

    GLenum err = glewInit();
    if (err != GLEW_OK) {
        std::cerr << "Could not initialize GLEW: "
                  << reinterpret_cast<const char*>(glewGetErrorString(err))
                  << std::endl;
    } else {
        std::cout << "Glew initialized" << std::endl;
    }

    // Shader
    _shader = std::make_unique<GraphicShader>("shader/vertex_shader.glsl", "shader/fragment_shader.glsl");
    _shader->init();

    // Triangle
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    GLuint VBO;
    GL(glGenBuffers(1, &VBO));
    GL(glBindBuffer(GL_ARRAY_BUFFER, VBO));
    GL(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));

    GL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0));
    GL(glEnableVertexAttribArray(0));

    GL(glGenVertexArrays(1, &_VAO));
    GL(glBindVertexArray(_VAO));
    GL(glBindBuffer(GL_ARRAY_BUFFER, VBO));
    GL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0));
    GL(glEnableVertexAttribArray(0));

    _loadEnd = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(_loadEnd - _loadStart);
    _loadDuration = duration.count() / 1000.0;
}

void OpenGLWidget::resizeGL(int w, int h)
{
    GL(glViewport(0, 0, w, h));
}

void OpenGLWidget::paintGL()
{
    if (_labelMs) {
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(2) << _loadDuration << " ms";
        _labelMs->setText(QString::fromStdString(oss.str()));
    }

    GL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

    _shader->bind();
    GL(glBindVertexArray(_VAO));
    GL(glDrawArrays(GL_TRIANGLES, 0, 3));
}

void OpenGLWidget::reload()
{
    initializeGL();
    repaint();
}

void OpenGLWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
        case Qt::Key_F5:
            reload();
            break;
        default:
            break;
    }
}