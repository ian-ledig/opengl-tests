#pragma once

#include <glm/glm.hpp>
#include <string>

class Shader {
public:
    Shader& operator=(const Shader& shader) = default;

    void bind() const;
    void unbind() const;

    template <class T>
    void setUniformAttrib(const std::string& name, const T& value) const;

    template <class T>
    void setUniformAttrib(const std::string& name, const T* values, int count) const;

protected:
    std::string loadFile(const std::string& filename);
    std::string loadFile(const std::string& filename, const int insert_depth);
    unsigned loadShader(unsigned int shaderType, const std::string& shader_name, const std::string& code);

protected:
    unsigned _program_id = 0U;
};
