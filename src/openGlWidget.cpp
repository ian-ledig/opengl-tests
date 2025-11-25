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
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        std::cerr << "Could not initialize GLEW: "
                  << reinterpret_cast<const char*>(glewGetErrorString(err))
                  << std::endl;
    } else {
        std::cout << "Glew initialized" << std::endl;
    }

    GL(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));

    setupScene();
}

void OpenGLWidget::resizeGL(int w, int h)
{
    GL(glViewport(0, 0, w, h));

    for (const auto& component : _components) {
        component->resize(w, h);
    }
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

    for (const auto& component : _components) {
        component->draw(_shader.get());
    }
}

void OpenGLWidget::setupScene()
{
    _loadStart = std::chrono::high_resolution_clock::now();

    _components.clear();

    _shader = std::make_unique<GraphicShader>("shader/vertex_shader.glsl", "shader/fragment_shader.glsl");
    _shader->init();

    auto cube = std::make_unique<Cube>("texture/lava.jpg");
    cube->init();
    _components.push_back(std::move(cube));

    resizeGL(width(), height());

    _loadEnd = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(_loadEnd - _loadStart);
    _loadDuration = duration.count() / 1000.0;
}

void OpenGLWidget::teardownScene()
{
    _components.clear();
    _shader.reset();
}

void OpenGLWidget::reload()
{
    makeCurrent();
    teardownScene();
    setupScene();
    doneCurrent();
    update();
}

void OpenGLWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
        case Qt::Key_F5:
            reload();
            return;
        default:
            break;
    }

    for (const auto& component : _components) {
        component->keyPressEvent(event);
    }
}

void OpenGLWidget::mousePressEvent(QMouseEvent *event)
{
    for (const auto& component : _components) {
        component->mousePressEvent(event);
    }
    
    QOpenGLWidget::mousePressEvent(event);
}