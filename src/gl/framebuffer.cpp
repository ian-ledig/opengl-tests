#include "framebuffer.h"

#include "gl_utils.h"
#include "utils/logger.h"

namespace gl {
    Framebuffer::Framebuffer()
    {
    }

    Framebuffer::~Framebuffer()
    {
        destroy();
    }

    void Framebuffer::init(int width, int height)
    {
        destroy();

        _width  = width;
        _height = height;

        GL(glGenFramebuffers(1, &_framebuffer));
        bind();

        createColorAttachment(width, height);
        createDepthAttachment(width, height);

        GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
        if (status == GL_FRAMEBUFFER_COMPLETE) {
            Logger::logger().info("Framebuffer is complete ({}x{})", width, height);
        } else {
            Logger::logger().error("Framebuffer is NOT complete (status = 0x{:X})", static_cast<unsigned int>(status));
        }

        unbind();
    }

    void Framebuffer::bind() const
    {
        GL(glBindFramebuffer(GL_FRAMEBUFFER, _framebuffer));
    }

    void Framebuffer::unbind()
    {
        GL(glBindFramebuffer(GL_FRAMEBUFFER, 0));
    }

    void Framebuffer::destroy()
    {
        if (_depthRbo != 0) {
            GL(glDeleteRenderbuffers(1, &_depthRbo));
            _depthRbo = 0;
        }
    
        if (_texture != 0) {
            GL(glDeleteTextures(1, &_texture));
            _texture = 0;
        }
    
        if (_framebuffer != 0) {
            GL(glDeleteFramebuffers(1, &_framebuffer));
            _framebuffer = 0;
        }
    
        _width  = 0;
        _height = 0;
    }

    void Framebuffer::createColorAttachment(int width, int height)
    {
        GL(glGenTextures(1, &_texture));
        GL(glBindTexture(GL_TEXTURE_2D, _texture));
        GL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr));
        GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
        GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
        GL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _texture, 0));
        GL(glBindTexture(GL_TEXTURE_2D, 0));
    }

    void Framebuffer::createDepthAttachment(int width, int height)
    {
        GL(glGenRenderbuffers(1, &_depthRbo));
        GL(glBindRenderbuffer(GL_RENDERBUFFER, _depthRbo));
        
		GL(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height));
		GL(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, _depthRbo));

        GL(glBindRenderbuffer(GL_RENDERBUFFER, 0));
    }
}