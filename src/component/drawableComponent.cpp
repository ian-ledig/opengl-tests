#include "drawableComponent.h"
#include "utils/textureManager.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

DrawableComponent::DrawableComponent()
    : Component()
{
    updateModelMatrix();
}

DrawableComponent::DrawableComponent(const std::string& texturePath)
{
    TextureManager::loadTexture(_texture, texturePath);
    updateModelMatrix();
}

DrawableComponent::~DrawableComponent()
{
}

void DrawableComponent::draw(Shader* shader)
{
    Component::draw(shader);
    
    shader->setUniformAttrib("model", _modelMatrix);
}

bool DrawableComponent::isPointInside(float x, float y) const
{
    const float* vertices = getVertices();
    const GLuint* indices = getIndices();
    const size_t vertexCount = getVertexCount();
    const size_t indexCount = getIndexCount();
    const size_t stride = getVertexStride();

    if (!vertices || !indices || vertexCount == 0 || indexCount == 0) {
        return false;
    }

    const glm::mat4 mvp = _projection * _view * _modelMatrix;

    auto vertexAtNDC = [vertices, stride, mvp](size_t index) -> std::pair<glm::vec2, bool> {
        const size_t base = index * stride;
        glm::vec4 pos(vertices[base], vertices[base + 1], vertices[base + 2], 1.0f);
        pos = mvp * pos;
        bool visible = pos.w > 0.0f;
        if (std::abs(pos.w) > 1e-6f) {
            pos.x /= pos.w;
            pos.y /= pos.w;
            pos.z /= pos.w;
            visible = visible && pos.z >= -1.0f && pos.z <= 1.0f;
        }
        return std::make_pair(glm::vec2{pos.x, pos.y}, visible);
    };

    auto pointInTriangle = [](const glm::vec2& p,
                              const glm::vec2& a,
                              const glm::vec2& b,
                              const glm::vec2& c) {
        const glm::vec2 v0 = c - a;
        const glm::vec2 v1 = b - a;
        const glm::vec2 v2 = p - a;

        const float dot00 = glm::dot(v0, v0);
        const float dot01 = glm::dot(v0, v1);
        const float dot02 = glm::dot(v0, v2);
        const float dot11 = glm::dot(v1, v1);
        const float dot12 = glm::dot(v1, v2);

        const float denom = dot00 * dot11 - dot01 * dot01;
        if (std::abs(denom) < 1e-6f) {
            return false;
        }

        const float invDenom = 1.0f / denom;
        const float u = (dot11 * dot02 - dot01 * dot12) * invDenom;
        const float v = (dot00 * dot12 - dot01 * dot02) * invDenom;

        return (u >= 0.0f) && (v >= 0.0f) && (u + v <= 1.0f);
    };

    const glm::vec2 point{x, y};

    for (size_t i = 0; i < indexCount; i += 3) {
        if (i + 2 >= indexCount) {
            break;
        }
        const GLuint idxA = indices[i];
        const GLuint idxB = indices[i + 1];
        const GLuint idxC = indices[i + 2];
        
        if (idxA >= vertexCount || idxB >= vertexCount || idxC >= vertexCount) {
            continue;
        }
        
        auto [a, aVisible] = vertexAtNDC(idxA);
        auto [b, bVisible] = vertexAtNDC(idxB);
        auto [c, cVisible] = vertexAtNDC(idxC);
        
        if (!aVisible || !bVisible || !cVisible) {
            continue;
        }
        
        if (pointInTriangle(point, a, b, c)) {
            return true;
        }
    }

    return false;
}

void DrawableComponent::updateModelMatrix()
{
    _modelMatrix = glm::mat4(1.0f);
    
    _modelMatrix = glm::translate(_modelMatrix, _position);
    
    _modelMatrix = glm::rotate(_modelMatrix, glm::radians(_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    _modelMatrix = glm::rotate(_modelMatrix, glm::radians(_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    _modelMatrix = glm::rotate(_modelMatrix, glm::radians(_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    
    _modelMatrix = glm::scale(_modelMatrix, _scale);
}