#include "graphic_shader.h"

#include <GL/glew.h>

#include <iostream>

#include "../gl_utils.h"

#define MAX_INSERT_DEPTH 4

static unsigned loadGraphicsShaderProgram(GLenum vertexShader, GLenum fragmentShader, const std::string& shader_name)
{
    unsigned int shaderProgram;
    shaderProgram = GL(glCreateProgram());

    GL(glAttachShader(shaderProgram, vertexShader));
    GL(glAttachShader(shaderProgram, fragmentShader));
    GL(glLinkProgram(shaderProgram));

    int success;
    char infoLog[512];
    GL(glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success));

    if (!success) {
        GL(glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog));
        std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED - " << shader_name << std::endl << infoLog << std::endl;
        exit(1);
    }

    return shaderProgram;
}

GraphicShader::GraphicShader() = default;

GraphicShader::GraphicShader(const std::string& vertex_filename, const std::string& fragment_filename)
{
    set(vertex_filename, fragment_filename);
}

GraphicShader::GraphicShader(const GraphicShader& shader)
{
    set(*shader._vertex_filename, *shader._fragment_filename);
}

void GraphicShader::set(const std::string& vertex_filename, const std::string& fragment_filename)
{
    _vertex_filename = std::make_unique<std::string>(vertex_filename);
    _fragment_filename = std::make_unique<std::string>(fragment_filename);
}

void GraphicShader::init()
{
    if (_vertex_filename == nullptr || _fragment_filename == nullptr) {
        throw std::string("Could not init shaders");
    }

    std::string vertexShaderCode = loadFile(*_vertex_filename, MAX_INSERT_DEPTH);
    std::string fragmentShaderCode = loadFile(*_fragment_filename, MAX_INSERT_DEPTH);

    // std::cout << *_vertex_filename << " / " << *_fragment_filename << std::endl;

    unsigned vertexShaderId = loadShader(GL_VERTEX_SHADER, *_vertex_filename, vertexShaderCode);
    unsigned fragmentShaderId = loadShader(GL_FRAGMENT_SHADER, *_fragment_filename, fragmentShaderCode);

    if (vertexShaderId == 0) {
        std::cout << "Error while compiling vertex shader" << std::endl;
    }

    if (fragmentShaderId == 0) {
        std::cout << "Error while compiling fragment shader" << std::endl;
    }

    _program_id = loadGraphicsShaderProgram(vertexShaderId, fragmentShaderId, "(" + *_vertex_filename + ", " + *_fragment_filename + ")");

    GL(glDeleteShader(vertexShaderId));
    GL(glDeleteShader(fragmentShaderId));
    /* _vertex_filename = nullptr;
    _fragment_filename = nullptr; */
}

std::string GraphicShader::getVertexFileName()
{
    std::string result;
    result.assign(*_vertex_filename.get());
    // std::cout << "reloading vertex " << result << std::endl;
    return result;
}

std::string GraphicShader::getFragmentFileName()
{
    std::string result;
    result.assign(*_fragment_filename.get());
    // std::cout << "reloading fragment " << result << std::endl;
    return result;
}