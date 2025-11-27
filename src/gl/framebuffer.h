#pragma once

#include <GL/glew.h>

namespace gl {
    class Framebuffer
    {
    public:
        Framebuffer();
        ~Framebuffer();

        void init(int width, int height);

        void bind() const;
        static void unbind();

        GLuint getTexture() const { return _texture; }
        int width()  const { return _width; }
        int height() const { return _height; }

    private:
    void destroy();
        void createColorAttachment(int width, int height);
        void createDepthAttachment(int width, int height);

        GLuint _framebuffer = 0;
        GLuint _texture = 0;
        GLuint _depthRbo = 0;
        int _width = 0;
        int _height = 0;
    };
}