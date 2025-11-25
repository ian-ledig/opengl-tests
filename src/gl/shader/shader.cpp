#include "shader.h"

#include <GL/glew.h>
#include <utils/logger.h>

#include <fstream>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <regex>
#include <sstream>

#include "../gl_utils.h"

#define INSERT_STR "#insert "

// TODO Separate the shader file parsing part and the OpenGL shader object creation part

std::string Shader::loadFile(const std::string& filename)
{
    std::ifstream t(filename, std::ios::in);

    if (!t.is_open()) {
        std::cerr << "Error: Cannot open \"" << filename << "\"" << std::endl;
    }

    std::stringstream buffer;
    buffer << t.rdbuf();

    return buffer.str();
}

std::string regex_replace(const std::string& input, const std::regex& regex, std::function<std::string(std::smatch const& match)> format)
{
    std::ostringstream output;
    std::sregex_iterator begin(input.begin(), input.end(), regex), end;

    if (begin == end) {
        return input;
    }

    for (; begin != end; begin++) {
        output << begin->prefix() << format(*begin);
    }

    output << input.substr(input.size() - begin->position());
    return output.str();
}

std::string Shader::loadFile(const std::string& filename, const int insert_depth)
{
    if (insert_depth < 0) {
        return loadFile(filename);
    } else if (insert_depth == 0) {
        Logger::logger().warn("Reached maximum insert depth with \"{}\"", filename);
        return loadFile(filename);
    } else {
        std::string code{""};
        std::ifstream t{filename, std::ios::in};

        if (!t.is_open()) {
            Logger::logger().error("Error: Cannot open \"{}\"", filename);
        }

        std::string line;
        while (std::getline(t, line)) {
            code += line + '\n';
        }
        t.close();
        return code;
    }
}

static std::string extractLine(const std::string& str, int line)
{
    int line_counter = 0;
    std::size_t current_line_begin = 0;

    while (current_line_begin < str.size()) {
        auto current_line_end = str.find('\n', current_line_begin);

        if (line_counter == line) {
            return str.substr(current_line_begin, current_line_end - current_line_begin);
        }

        if (current_line_end == std::string::npos) {
            throw std::string("Error: out of bounds");
        }

        current_line_begin = current_line_end + 1;
        line_counter++;
    }

    if (line == 0) {
        return "";
    }

    throw std::string("Error: out of bounds");
}

unsigned Shader::loadShader(unsigned int shaderType, const std::string& shader_name, const std::string& code)
{
    const char* codeStr = code.c_str();

    unsigned shaderId = 0;
    shaderId = GL(glCreateShader(shaderType));
    GL(glShaderSource(shaderId, 1, &codeStr, nullptr));
    GL(glCompileShader(shaderId));

    int success;
    GL(glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success));

    if (!success) {
        char infoLog[512];
        GL(glGetShaderInfoLog(shaderId, 512, nullptr, infoLog));

        std::string info_str(infoLog);
        std::regex line_nb_regex("0\\((.+)\\)");

        std::vector<int> line_nbs;
        auto words_begin = std::sregex_iterator(info_str.begin(), info_str.end(), line_nb_regex);
        auto words_end = std::sregex_iterator();

        for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
            auto match = *i;
            if (match.size() > 1) {
                std::istringstream iss(match[1].str());
                int line_nb;
                iss >> line_nb;
                line_nbs.push_back(line_nb);
            }
        }

        std::ostringstream error_stream;

        if (!line_nbs.empty()) {
            error_stream << "ERROR::SHADER::COMPILATION_FAILED - " << shader_name << std::endl << info_str;

            for (auto line_nb : line_nbs) {
                error_stream << "L" << line_nb << ": " << extractLine(code, line_nb - 1) << std::endl;
            }
            error_stream << std::endl;

        } else {
            error_stream << "line_nb == -1 && ERROR::SHADER::COMPILATION_FAILED - " << shader_name << std::endl << infoLog << std::endl;
        }

        Logger::logger().error(error_stream.str());

        return 0;
    }

    return shaderId;
}

void Shader::bind() const
{
    GL(glUseProgram(_program_id));
}

void Shader::unbind() const
{
    GL(glUseProgram(0));
}

template <>
void Shader::setUniformAttrib<bool>(const std::string& name, const bool& value) const
{
    GL(glUniform1i(glGetUniformLocation(_program_id, name.c_str()), int(value)));
}

template <>
void Shader::setUniformAttrib<int>(const std::string& name, const int& value) const
{
    GL(glUniform1i(glGetUniformLocation(_program_id, name.c_str()), value));
}

template <>
void Shader::setUniformAttrib<unsigned int>(const std::string& name, const unsigned int& value) const
{
    GL(glUniform1ui(glGetUniformLocation(_program_id, name.c_str()), value));
}

template <>
void Shader::setUniformAttrib<float>(const std::string& name, const float& value) const
{
    GL(glUniform1f(glGetUniformLocation(_program_id, name.c_str()), value));
}

template <>
void Shader::setUniformAttrib<double>(const std::string& name, const double& value) const
{
    GL(glUniform1d(glGetUniformLocation(_program_id, name.c_str()), value));
}

template <>
void Shader::setUniformAttrib<glm::vec2>(const std::string& name, const glm::vec2& vec) const
{
    GL(glUniform2f(glGetUniformLocation(_program_id, name.c_str()), vec.x, vec.y));
}

template <>
void Shader::setUniformAttrib<glm::vec3>(const std::string& name, const glm::vec3& vec) const
{
    GL(glUniform3f(glGetUniformLocation(_program_id, name.c_str()), vec.x, vec.y, vec.z));
}

template <>
void Shader::setUniformAttrib<glm::vec4>(const std::string& name, const glm::vec4& vec) const
{
    GL(glUniform4f(glGetUniformLocation(_program_id, name.c_str()), vec.x, vec.y, vec.z, vec.w));
}

template <>
void Shader::setUniformAttrib<glm::mat3>(const std::string& name, const glm::mat3& mat) const
{
    GL(glUniformMatrix3fv(glGetUniformLocation(_program_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat)));
}

template <>
void Shader::setUniformAttrib<glm::mat4>(const std::string& name, const glm::mat4& mat) const
{
    GL(glUniformMatrix4fv(glGetUniformLocation(_program_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat)));
}

template <>
void Shader::setUniformAttrib<int>(const std::string& name, const int* values, int count) const
{
    GL(glUniform1iv(glGetUniformLocation(_program_id, name.c_str()), count, values));
}

template <>
void Shader::setUniformAttrib<float>(const std::string& name, const float* values, int count) const
{
    GL(glUniform1fv(glGetUniformLocation(_program_id, name.c_str()), count, values));
}

template <>
void Shader::setUniformAttrib<double>(const std::string& name, const double* values, int count) const
{
    GL(glUniform1dv(glGetUniformLocation(_program_id, name.c_str()), count, values));
}

template <>
void Shader::setUniformAttrib<bool>(const std::string& name, const bool* values, int count) const
{
    GL(glUniform1iv(glGetUniformLocation(_program_id, name.c_str()), count, (int*)values));
}

template void Shader::setUniformAttrib<bool>(const std::string& name, const bool& value) const;
template void Shader::setUniformAttrib<int>(const std::string& name, const int& value) const;
template void Shader::setUniformAttrib<unsigned int>(const std::string& name, const unsigned int& value) const;
template void Shader::setUniformAttrib<float>(const std::string& name, const float& value) const;
template void Shader::setUniformAttrib<double>(const std::string& name, const double& value) const;
template void Shader::setUniformAttrib<glm::vec2>(const std::string& name, const glm::vec2& vec) const;
template void Shader::setUniformAttrib<glm::vec3>(const std::string& name, const glm::vec3& vec) const;
template void Shader::setUniformAttrib<glm::vec4>(const std::string& name, const glm::vec4& vec) const;
template void Shader::setUniformAttrib<glm::mat3>(const std::string& name, const glm::mat3& mat) const;
template void Shader::setUniformAttrib<glm::mat4>(const std::string& name, const glm::mat4& mat) const;
template void Shader::setUniformAttrib<int>(const std::string& name, const int* values, int count) const;
template void Shader::setUniformAttrib<float>(const std::string& name, const float* values, int count) const;
template void Shader::setUniformAttrib<double>(const std::string& name, const double* values, int count) const;
template void Shader::setUniformAttrib<bool>(const std::string& name, const bool* values, int count) const;