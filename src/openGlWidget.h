#pragma once

#include <GL/glew.h>
#include <QOpenGLWidget>
#include "gl/gl_utils.h"
#include <QLabel>
#include <QKeyEvent>
#include <QMouseEvent>
#include "gl/shader/graphic_shader.h"
#include "component/cube.h"
#include "component/camera.h"
#include "utils/logger.h"
#include <glm/glm.hpp>
#include <memory>
#include <vector>

#define LOAD_DURATION_HISTORY_SIZE 200

class OpenGLWidget : public QOpenGLWidget {
public:
    QLabel* _labelMs;
    QLabel* _labelMsAver;
    QLabel* _labelLightPos;
    QLabel* _labelReload;

    OpenGLWidget();
    ~OpenGLWidget();

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

private:
    std::chrono::high_resolution_clock::time_point _loadStart;
    std::chrono::high_resolution_clock::time_point _loadEnd;

    double _loadDuration;

    float _loadDurationHistory[LOAD_DURATION_HISTORY_SIZE];
    int _historyCount;
    int _historyIndex;

    std::vector<std::unique_ptr<Component>> _components;

    std::unique_ptr<GraphicShader> _shader;

    Camera* _camera;
    glm::mat4 _projection;
    glm::vec3 _lightPos;

    void setupScene();
    void teardownScene();
    void reload();
    
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
};