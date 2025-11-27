#include "compute_shader.h"

#include <GL/glew.h>

#include <iostream>

#include "../gl_utils.h"

#define MAX_INSERT_DEPTH 4

ComputeShader::ComputeShader() = default;

ComputeShader::ComputeShader(const std::string& compute_filename)
{
    set(compute_filename);
}

ComputeShader::ComputeShader(const ComputeShader& shader)
{
    set(*shader._compute_filename);
}

static unsigned loadComputeShaderProgram(GLenum computeShader, const std::string& shader_name)
{
    unsigned int shaderProgram;
    shaderProgram = GL(glCreateProgram());

    GL(glAttachShader(shaderProgram, computeShader));
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

void ComputeShader::set(const std::string& compute_filename)
{
    _compute_filename = std::make_unique<std::string>(compute_filename);
}

void ComputeShader::init()
{
    std::string compute_shader_code = loadFile(*_compute_filename, MAX_INSERT_DEPTH);

    unsigned compute_shader_id = loadShader(GL_COMPUTE_SHADER, *_compute_filename, compute_shader_code);

    if (compute_shader_id == 0) {
        std::cout << "Error while compiling compute shader" << std::endl;
    }

    // std::cout << *_compute_filename << std::endl;

    _program_id = loadComputeShaderProgram(compute_shader_id, *_compute_filename);

    GL(glDeleteShader(compute_shader_id));
    _compute_filename = nullptr;

    GL(glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 0, &_group_count[0]));
    GL(glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 1, &_group_count[1]));
    GL(glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 2, &_group_count[2]));

    // std::cout << "Max work group count: (" << _group_count[0] << ", " << _group_count[1] << ", " << _group_count[2] << ")" << std::endl;

    GL(glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 0, &_group_size[0]));
    GL(glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 1, &_group_size[1]));
    GL(glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 2, &_group_size[2]));

    // std::cout << "Max work group size: (" << _group_size[0] << ", " << _group_size[1] << ", " << _group_size[2] << ")" << std::endl;
}

void ComputeShader::dispatch(int x, int y, int z) const
{
    GL(glDispatchCompute(x, y, z));
}