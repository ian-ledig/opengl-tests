#pragma once

#include <GL/glew.h>
#include <QOpenGLWidget>
#include "gl/gl_utils.h"
#include <QLabel>
#include <QKeyEvent>
#include "gl/shader/graphic_shader.h"

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
    std::unique_ptr<GraphicShader> _shader;
    GLuint _VAO;

    void reload();
    virtual void keyPressEvent(QKeyEvent *event) override;
};