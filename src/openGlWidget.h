#pragma once

#include <GL/glew.h>
#include <QOpenGLWidget>
#include "gl/gl_utils.h"
#include <QLabel>
#include <QKeyEvent>
#include <QMouseEvent>
#include "gl/shader/graphic_shader.h"
#include "component/triangle.h"
#include "utils/logger.h"

class OpenGLWidget : public QOpenGLWidget {
public:
    QLabel* _labelMs;

    OpenGLWidget();
    ~OpenGLWidget();

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

private:
    std::chrono::high_resolution_clock::time_point _loadStart;
    std::chrono::high_resolution_clock::time_point _loadEnd;

    double _loadDuration;

    std::vector<std::unique_ptr<Component>> _components;

    std::unique_ptr<GraphicShader> _shader;
    std::unique_ptr<Triangle> _triangle;

    void reload();
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
};