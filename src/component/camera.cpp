#include "camera.h"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera() : 
    Component()
    , _fov(60.0f)
    , _near(0.1f)
    , _far(100.0f)
    , _lookAt(0.0f, 0.0f, 0.0f)
    , _up(0.0f, 1.0f, 0.0f)
{
    setPosition(glm::vec3(0.0f, 0.0f, 3.0f));
}

Camera::Camera(float fov, float near, float far) : 
    Component()
    , _fov(fov)
    , _near(near)
    , _far(far)
    , _lookAt(0.0f, 0.0f, 0.0f)
    , _up(0.0f, 1.0f, 0.0f)
{
    setPosition(glm::vec3(0.0f, 0.0f, 3.0f));
}

Camera::~Camera()
{
}

glm::mat4 Camera::getProjection() const
{
    return glm::perspective(glm::radians(_fov), float(getWidth()) / float(getHeight()), _near, _far);
}

glm::mat4 Camera::getView() const
{
    return glm::lookAt(_position, _lookAt, _up);
}