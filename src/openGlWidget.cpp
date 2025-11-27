#include "openGlWidget.h"
#include "component/drawableComponent.h"
#include <iostream>
#include <chrono>
#include <iomanip>
#include "quad.h"

OpenGLWidget::OpenGLWidget() : _historyCount(0), _historyIndex(0), _camera(nullptr)
{
    setFocusPolicy(Qt::StrongFocus);
    setFocus();
    setMouseTracking(true);

    for (int i = 0; i < LOAD_DURATION_HISTORY_SIZE; ++i) {
        _loadDurationHistory[i] = 0.0f;
    }
}

OpenGLWidget::~OpenGLWidget() = default;

void OpenGLWidget::initializeGL()
{
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        std::cerr << "Could not initialize GLEW: "
                  << reinterpret_cast<const char*>(glewGetErrorString(err))
                  << std::endl;
    } else {
        std::cout << "Glew initialized" << std::endl;
    }

    setupScene();
}

void OpenGLWidget::setupScene()
{
    _loadStart = std::chrono::high_resolution_clock::now();

    GL(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
    GL(glEnable(GL_DEPTH_TEST));
    GL(glEnable(GL_BLEND));
    GL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    _shader = std::make_unique<GraphicShader>("shader/vertex_shader.glsl", "shader/fragment_shader.glsl");
    _shader->init();

    _screenShader = std::make_unique<GraphicShader>("shader/screen_vertex.glsl", "shader/screen_fragment.glsl");
    _screenShader->init();

    _blurComputeShaderX = std::make_unique<ComputeShader>("shader/blur_compute_x.glsl");
    _blurComputeShaderY = std::make_unique<ComputeShader>("shader/blur_compute_y.glsl");
    _blurComputeShaderX->init();
    _blurComputeShaderY->init();

    _framebuffer.init(width(), height());

    if (_blurTextureX == 0) {
      GL(glGenTextures(1, &_blurTextureX));
    }
    if (_blurTextureY == 0) {
      GL(glGenTextures(1, &_blurTextureY));
    }

    GL(glBindTexture(GL_TEXTURE_2D, _blurTextureX));
    GL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width(), height(), 0, GL_RGBA,
                    GL_UNSIGNED_BYTE, nullptr));
    GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

    GL(glBindTexture(GL_TEXTURE_2D, _blurTextureY));
    GL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width(), height(), 0, GL_RGBA,
                    GL_UNSIGNED_BYTE, nullptr));
    GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GL(glBindTexture(GL_TEXTURE_2D, 0));

    _quad = std::make_unique<Mesh>(buildQuad());
    _quad->init();

	// Create components
    auto camera = std::make_unique<Camera>();
    _camera = camera.get();
    _components.push_back(std::move(camera));

    auto cube = std::make_unique<Cube>("texture/gold.jpg");
    cube->init();
    _components.push_back(std::move(cube));

    _lightPos = glm::vec3(0.0f, 1.5f, 2.0f);

    resizeGL(width(), height());

    _loadEnd = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(_loadEnd - _loadStart);
    _loadDuration = duration.count() / 1000.0;

    // Add to history array
    _loadDurationHistory[_historyIndex] = static_cast<float>(_loadDuration);
    _historyIndex = (_historyIndex + 1) % LOAD_DURATION_HISTORY_SIZE;
    if (_historyCount < LOAD_DURATION_HISTORY_SIZE) {
        _historyCount++;
    }
}

void OpenGLWidget::resizeGL(int w, int h)
{
    GL(glViewport(0, 0, w, h));

    _framebuffer.init(w, h);

    for (const auto& component : _components) {
        component->resize(w, h);
    }

    if(_camera) {
        _projection = _camera->getProjection();    
    }

    if (_blurTextureX != 0) {
      GL(glBindTexture(GL_TEXTURE_2D, _blurTextureX));
      GL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_RGBA,
                      GL_UNSIGNED_BYTE, nullptr));
    }
    if (_blurTextureY != 0) {
      GL(glBindTexture(GL_TEXTURE_2D, _blurTextureY));
      GL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_RGBA,
                      GL_UNSIGNED_BYTE, nullptr));
    }
    GL(glBindTexture(GL_TEXTURE_2D, 0));
}

void OpenGLWidget::paintGL()
{
    if (_labelMs) {
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(2) << _loadDuration << " ms";
        _labelMs->setText(QString::fromStdString(oss.str()));
    }

    if (_labelMsAver && _historyCount > 0) {
        float sum = 0.0f;
        for (int i = 0; i < _historyCount; ++i) {
            sum += _loadDurationHistory[i];
        }
        float average = sum / _historyCount;
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(2) << average << " ms (avg)";
        _labelMsAver->setText(QString::fromStdString(oss.str()));
    }

    if (_labelReload) {
        std::ostringstream oss;
        oss << "(x" << _historyCount << ")";
        _labelReload->setText(QString::fromStdString(oss.str()));
    }

    _framebuffer.bind();

    GL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL(glEnable(GL_DEPTH_TEST));

    _shader->bind();

    glm::mat4 view = glm::mat4(1.0f);
    if(_camera) {
        view = _camera->getView();
        _shader->setUniformAttrib("projection", _projection);
        _shader->setUniformAttrib("view", view);
    }
    _shader->setUniformAttrib("lightPos", _lightPos);
    _shader->setUniformAttrib("material.ambient", glm::vec3(0.24725f, 0.1995f, 0.0745f));

    for (const auto& component : _components) {
        if (auto* drawable = dynamic_cast<DrawableComponent*>(component.get())) {
            drawable->setProjectionMatrix(_projection);
            drawable->setViewMatrix(view);
        }
        component->draw(_shader.get());
    }

	_shader->unbind();
	_screenShader->bind();
	_screenShader->setUniformAttrib("grayscale", _grayscale);
	_screenShader->unbind();

    _framebuffer.unbind();

    GLuint finalTexture = _framebuffer.getTexture();

    if (_blur) {
        const int groupSizeX = 16;
        const int groupSizeY = 16;
        int groupsX = (width() + groupSizeX - 1) / groupSizeX;
        int groupsY = (height() + groupSizeY - 1) / groupSizeY;

        // Horizontal
        _blurComputeShaderX->bind();
        _blurComputeShaderX->setUniformAttrib("resolution", glm::vec2(width(), height()));

        GL(glActiveTexture(GL_TEXTURE0));
        GL(glBindTexture(GL_TEXTURE_2D, _framebuffer.getTexture()));
        _blurComputeShaderX->setUniformAttrib("inputImage", 0);

        GL(glBindImageTexture(1, _blurTextureY, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA8));

        _blurComputeShaderX->dispatch(groupsX, groupsY, 1);

		GL(glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT | GL_TEXTURE_FETCH_BARRIER_BIT));

        // Vertical
        _blurComputeShaderY->bind();
        _blurComputeShaderY->setUniformAttrib("resolution", glm::vec2(width(), height()));

        GL(glActiveTexture(GL_TEXTURE0));
        GL(glBindTexture(GL_TEXTURE_2D, _blurTextureY));
        _blurComputeShaderY->setUniformAttrib("inputImage", 0);

        GL(glBindImageTexture(1, _blurTextureX, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA8));

        _blurComputeShaderY->dispatch(groupsX, groupsY, 1);

		GL(glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT));

        finalTexture = _blurTextureX;
    }

	GL(glBindFramebuffer(GL_FRAMEBUFFER, defaultFramebufferObject()));
    GL(glDisable(GL_DEPTH_TEST));
    GL(glClear(GL_COLOR_BUFFER_BIT));

	_screenShader->bind();
    GL(glActiveTexture(GL_TEXTURE0));
    GL(glBindTexture(GL_TEXTURE_2D, finalTexture));
    _screenShader->setUniformAttrib("screenTexture", 0);
    _quad->bind();
    _quad->draw(GL_TRIANGLES);
}

void OpenGLWidget::teardownScene()
{
    _components.clear();
    _camera = nullptr;
    _shader.reset();
    _screenShader.reset();
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
		case Qt::Key_G:
			_grayscale = !_grayscale;
			update();
			break;
		case Qt::Key_B:
			_blur = !_blur;
			update();
			break;
        case Qt::Key_Left:
            _lightPos.x -= 1.0f;
            if (_labelLightPos) {
                std::ostringstream oss;
                oss << std::fixed << std::setprecision(2) << _lightPos.x;
                _labelLightPos->setText(QString::fromStdString(oss.str()));
            }
            update();
            break;
        case Qt::Key_Right:
            _lightPos.x += 1.0f;
            if (_labelLightPos) {
                std::ostringstream oss;
                oss << std::fixed << std::setprecision(2) << _lightPos.x;
                _labelLightPos->setText(QString::fromStdString(oss.str()));
            }
            update();
            break;
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