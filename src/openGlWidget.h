#pragma once

#include <GL/glew.h>
#include <QOpenGLWidget>
#include "gl/gl_utils.h"
#include "gl/mesh.h"
#include <QLabel>
#include <QKeyEvent>
#include <QMouseEvent>
#include "gl/shader/graphic_shader.h"
#include "gl/shader/compute_shader.h"
#include "component/cube.h"
#include "component/camera.h"
#include "gl/framebuffer.h"
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

	bool _grayscale = false;
	bool _blur = false;

    float _loadDurationHistory[LOAD_DURATION_HISTORY_SIZE];
    int _historyCount;
    int _historyIndex;

    gl::Framebuffer _framebuffer;

    std::vector<std::unique_ptr<Component>> _components;

    std::unique_ptr<GraphicShader> _shader;
    std::unique_ptr<GraphicShader> _screenShader;
	std::unique_ptr<ComputeShader> _blurComputeShaderX;
	std::unique_ptr<ComputeShader> _blurComputeShaderY;

	GLuint _blurTextureX = 0;
    GLuint _blurTextureY = 0;

    std::unique_ptr<Mesh> _quad;

    Camera* _camera;
    glm::mat4 _projection;
    glm::vec3 _lightPos;

    void setupScene();
    void teardownScene();
    void reload();
    
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
};