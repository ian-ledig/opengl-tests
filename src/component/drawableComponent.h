#pragma once

#include "component.h"
#include "gl/texture.h"
#include <GL/glew.h>
#include <cstddef>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class DrawableComponent : public Component {
public:
    DrawableComponent();
    DrawableComponent(const std::string& texturePath);
    ~DrawableComponent();

    void draw(Shader* shader) override;

    bool isPointInside(float x, float y) const;
    
    void setProjectionMatrix(const glm::mat4& projection) { _projection = projection; }
    void setViewMatrix(const glm::mat4& view) { _view = view; }

    gl::Texture2D* getTexture() const { return _texture.get(); }

    void setPosition(const glm::vec3& position) override { Component::setPosition(position); updateModelMatrix(); }
    void setRotation(const glm::vec3& rotation) override { Component::setRotation(rotation); updateModelMatrix(); }
    void setScale(const glm::vec3& scale) override { Component::setScale(scale); updateModelMatrix(); }
    
    glm::mat4 getModelMatrix() const { return _modelMatrix; }

protected:
    virtual const float* getVertices() const = 0;
    virtual size_t getVertexCount() const = 0;
    virtual size_t getVertexStride() const = 0;
    
    virtual const GLuint* getIndices() const = 0;
    virtual size_t getIndexCount() const = 0;

private:
    void updateModelMatrix();
    
    std::unique_ptr<gl::Texture2D> _texture;
    glm::mat4 _modelMatrix = glm::mat4(1.0f);
    glm::mat4 _projection = glm::mat4(1.0f);
    glm::mat4 _view = glm::mat4(1.0f);
};