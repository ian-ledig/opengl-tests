#pragma once

#include <memory>

#include "shader.h"

class ComputeShader : public Shader {
public:
    ComputeShader();
    ComputeShader(const std::string& compute_filename);
    ComputeShader(const ComputeShader& shader);

    ComputeShader& operator=(ComputeShader&& shader) = default;

    void set(const std::string& compute_filename);
    void init();
    void dispatch(int x, int y, int z) const;

private:
    std::unique_ptr<std::string> _compute_filename;
    int _group_count[3];
    int _group_size[3];
};
