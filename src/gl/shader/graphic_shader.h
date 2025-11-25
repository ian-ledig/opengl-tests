#pragma once

#include <memory>

#include "shader.h"

class GraphicShader : public Shader {
public:
    GraphicShader();
    GraphicShader(const std::string& vertex_filename, const std::string& fragment_filename);
    GraphicShader(const GraphicShader& shader);

    GraphicShader& operator=(GraphicShader&& shader) = default;

    std::string getVertexFileName();
    std::string getFragmentFileName();

    void set(const std::string& vertex_filename, const std::string& fragment_filename);
    void init();

private:
    std::unique_ptr<std::string> _vertex_filename;
    std::unique_ptr<std::string> _fragment_filename;
};
