#pragma once

#include <GL/glew.h>

#include <memory>

#include "gl/mesh.h"

inline Mesh buildQuad()
{
    Mesh mesh(4 * 4,
              6,
              Mesh::Format{{2U, sizeof(float) * 4U, 0U},
                           {2U, sizeof(float) * 4U, 2U}},
              GL_STATIC_DRAW);

    mesh.set(
        {
            -1.0f, -1.0f, 0.0f, 0.0f,
            1.0f, -1.0f, 1.0f, 0.0f,
            1.0f, 1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, 0.0f, 1.0f,
        },
        {
            3, 0, 1,
            3, 1, 2
        });

    return mesh;
}