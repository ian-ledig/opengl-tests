#pragma once

#include "component.h"
#include <glm/glm.hpp>

class Camera : public Component {
public:
    Camera();
    Camera(float fov, float near, float far);
    ~Camera();

    glm::mat4 getProjection() const;
    glm::mat4 getView() const;

    void setLookAt(const glm::vec3& lookAt) { _lookAt = lookAt; }
    void setUpVector(const glm::vec3& up) { _up = up; }
    
    glm::vec3 getLookAt() const { return _lookAt; }
    glm::vec3 getUpVector() const { return _up; }

private:
    float _fov;
    float _near;
    float _far;
    
    glm::vec3 _lookAt;
    glm::vec3 _up;
};