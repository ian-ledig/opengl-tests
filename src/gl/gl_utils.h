#pragma once

void glCheckError_(const char *file, int line);

#define GL(inst) \
    inst;        \
    glCheckError_(__FILE__, __LINE__)

void GL_SYNC();

void printGLFramebufferStatus(unsigned status);

void glEnableDebugCallback();