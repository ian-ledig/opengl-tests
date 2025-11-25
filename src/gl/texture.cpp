#include "texture.h"

#include <cmath>
#include <exception>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>

#include "gl_utils.h"

namespace gl {

class InvalidVolumeFormat : public std::exception {
public:
    const char* what() const noexcept override
    {
        return "Invalid volume format provided";
    }
};

static GLenum getGLInternalFormat(int channels, TextureType type)
{
    switch (channels) {
        case 1: {
            switch (type) {
                case TextureType::INT8_TEXTURE:
                    return GL_R8I;
                case TextureType::INT16_TEXTURE:
                    return GL_R16I;
                case TextureType::INT32_TEXTURE:
                    return GL_R32I;
                case TextureType::UNSIGNED8_TEXTURE:
                    return GL_R8UI;
                case TextureType::UNSIGNED16_TEXTURE:
                    return GL_R16UI;
                case TextureType::UNSIGNED32_TEXTURE:
                    return GL_R32UI;
                case TextureType::NORM8_TEXTURE:
                    return GL_R8;
                case TextureType::NORM16_TEXTURE:
                    return GL_R16;
                case TextureType::NORM32_TEXTURE:
                    return GL_R;
                case TextureType::FLOAT16_TEXTURE:
                    return GL_R16F;
                case TextureType::FLOAT32_TEXTURE:
                    return GL_R32F;
                case TextureType::DEPTH32_TEXTURE:
                    return GL_DEPTH_COMPONENT;
                case TextureType::DEPTH24_STENCIL8_TEXTURE:
                    return GL_DEPTH24_STENCIL8;
                default: {
                    throw InvalidVolumeFormat();
                }
            }
        }
        case 2: {
            switch (type) {
                case TextureType::INT8_TEXTURE:
                    return GL_RG8I;
                case TextureType::INT16_TEXTURE:
                    return GL_RG16I;
                case TextureType::INT32_TEXTURE:
                    return GL_RG32I;
                case TextureType::UNSIGNED8_TEXTURE:
                    return GL_RG8UI;
                case TextureType::UNSIGNED16_TEXTURE:
                    return GL_RG16UI;
                case TextureType::UNSIGNED32_TEXTURE:
                    return GL_RG32UI;
                case TextureType::NORM8_TEXTURE:
                    return GL_RG8;
                case TextureType::NORM16_TEXTURE:
                    return GL_RG16;
                case TextureType::NORM32_TEXTURE:
                    return GL_RG;
                case TextureType::FLOAT16_TEXTURE:
                    return GL_RG16F;
                case TextureType::FLOAT32_TEXTURE:
                    return GL_RG32F;
                default: {
                    throw InvalidVolumeFormat();
                }
            }
        }
        case 3: {
            switch (type) {
                case TextureType::INT8_TEXTURE:
                    return GL_RGB8I;
                case TextureType::INT16_TEXTURE:
                    return GL_RGB16I;
                case TextureType::INT32_TEXTURE:
                    return GL_RGB32I;
                case TextureType::UNSIGNED8_TEXTURE:
                    return GL_RGB8UI;
                case TextureType::UNSIGNED16_TEXTURE:
                    return GL_RGB16UI;
                case TextureType::UNSIGNED32_TEXTURE:
                    return GL_RGB32UI;
                case TextureType::NORM8_TEXTURE:
                    return GL_RGB8;
                case TextureType::NORM16_TEXTURE:
                    return GL_RGB16;
                case TextureType::NORM32_TEXTURE:
                    return GL_RGB;
                case TextureType::FLOAT16_TEXTURE:
                    return GL_RGB16F;
                case TextureType::FLOAT32_TEXTURE:
                    return GL_RGB32F;
                default: {
                    throw InvalidVolumeFormat();
                }
            }
        }
        case 4: {
            switch (type) {
                case TextureType::INT8_TEXTURE:
                    return GL_RGBA8I;
                case TextureType::INT16_TEXTURE:
                    return GL_RGBA16I;
                case TextureType::INT32_TEXTURE:
                    return GL_RGBA32I;
                case TextureType::UNSIGNED8_TEXTURE:
                    return GL_RGBA8UI;
                case TextureType::UNSIGNED16_TEXTURE:
                    return GL_RGBA16UI;
                case TextureType::UNSIGNED32_TEXTURE:
                    return GL_RGBA32UI;
                case TextureType::NORM8_TEXTURE:
                    return GL_RGBA8;
                case TextureType::NORM16_TEXTURE:
                    return GL_RGBA16;
                case TextureType::NORM32_TEXTURE:
                    return GL_RGBA;
                case TextureType::FLOAT16_TEXTURE:
                    return GL_RGBA16F;
                case TextureType::FLOAT32_TEXTURE:
                    return GL_RGBA32F;
                default: {
                    throw InvalidVolumeFormat();
                }
            }
        }
        default: {
            throw InvalidVolumeFormat();
        }
    }
}

static GLenum getGLFormat(int channels, TextureType type)
{
    switch (channels) {
        case 1: {
            switch (type) {
                case TextureType::INT8_TEXTURE:
                    return GL_RED_INTEGER;
                case TextureType::INT16_TEXTURE:
                    return GL_RED_INTEGER;
                case TextureType::INT32_TEXTURE:
                    return GL_RED_INTEGER;
                case TextureType::UNSIGNED8_TEXTURE:
                    return GL_RED_INTEGER;
                case TextureType::UNSIGNED16_TEXTURE:
                    return GL_RED_INTEGER;
                case TextureType::UNSIGNED32_TEXTURE:
                    return GL_RED_INTEGER;
                case TextureType::NORM8_TEXTURE:
                    return GL_RED;
                case TextureType::NORM16_TEXTURE:
                    return GL_RED;
                case TextureType::NORM32_TEXTURE:
                    return GL_RED;
                case TextureType::FLOAT16_TEXTURE:
                    return GL_RED;
                case TextureType::FLOAT32_TEXTURE:
                    return GL_RED;
                case TextureType::DEPTH32_TEXTURE:
                    return GL_DEPTH_COMPONENT;
                case TextureType::DEPTH24_STENCIL8_TEXTURE:
                    return GL_DEPTH_STENCIL;
                default: {
                    throw InvalidVolumeFormat();
                }
            }
        }
        case 2: {
            switch (type) {
                case TextureType::INT8_TEXTURE:
                    return GL_RG_INTEGER;
                case TextureType::INT16_TEXTURE:
                    return GL_RG_INTEGER;
                case TextureType::INT32_TEXTURE:
                    return GL_RG_INTEGER;
                case TextureType::UNSIGNED8_TEXTURE:
                    return GL_RG_INTEGER;
                case TextureType::UNSIGNED16_TEXTURE:
                    return GL_RG_INTEGER;
                case TextureType::UNSIGNED32_TEXTURE:
                    return GL_RG_INTEGER;
                case TextureType::NORM8_TEXTURE:
                    return GL_RG;
                case TextureType::NORM16_TEXTURE:
                    return GL_RG;
                case TextureType::NORM32_TEXTURE:
                    return GL_RG;
                case TextureType::FLOAT16_TEXTURE:
                    return GL_RG;
                case TextureType::FLOAT32_TEXTURE:
                    return GL_RG;
                default: {
                    throw InvalidVolumeFormat();
                }
            }
        }
        case 3: {
            switch (type) {
                case TextureType::INT8_TEXTURE:
                    return GL_RGB_INTEGER;
                case TextureType::INT16_TEXTURE:
                    return GL_RGB_INTEGER;
                case TextureType::INT32_TEXTURE:
                    return GL_RGB_INTEGER;
                case TextureType::UNSIGNED8_TEXTURE:
                    return GL_RGB_INTEGER;
                case TextureType::UNSIGNED16_TEXTURE:
                    return GL_RGB_INTEGER;
                case TextureType::UNSIGNED32_TEXTURE:
                    return GL_RGB_INTEGER;
                case TextureType::NORM8_TEXTURE:
                    return GL_RGB;
                case TextureType::NORM16_TEXTURE:
                    return GL_RGB;
                case TextureType::NORM32_TEXTURE:
                    return GL_RGB;
                case TextureType::FLOAT16_TEXTURE:
                    return GL_RGB;
                case TextureType::FLOAT32_TEXTURE:
                    return GL_RGB;
                default: {
                    throw InvalidVolumeFormat();
                }
            }
        }
        case 4: {
            switch (type) {
                case TextureType::INT8_TEXTURE:
                    return GL_RGBA_INTEGER;
                case TextureType::INT16_TEXTURE:
                    return GL_RGBA_INTEGER;
                case TextureType::INT32_TEXTURE:
                    return GL_RGBA_INTEGER;
                case TextureType::UNSIGNED8_TEXTURE:
                    return GL_RGBA_INTEGER;
                case TextureType::UNSIGNED16_TEXTURE:
                    return GL_RGBA_INTEGER;
                case TextureType::UNSIGNED32_TEXTURE:
                    return GL_RGBA_INTEGER;
                case TextureType::NORM8_TEXTURE:
                    return GL_RGBA;
                case TextureType::NORM16_TEXTURE:
                    return GL_RGBA;
                case TextureType::NORM32_TEXTURE:
                    return GL_RGBA;
                case TextureType::FLOAT16_TEXTURE:
                    return GL_RGBA;
                case TextureType::FLOAT32_TEXTURE:
                    return GL_RGBA;
                default: {
                    throw InvalidVolumeFormat();
                }
            }
        }
        default: {
            throw InvalidVolumeFormat();
        }
    }
}

static GLenum getGLType(TextureType type)
{
    switch (type) {
        case TextureType::INT8_TEXTURE:
            return GL_BYTE;
        case TextureType::INT16_TEXTURE:
            return GL_SHORT;
        case TextureType::INT32_TEXTURE:
            return GL_INT;
        case TextureType::UNSIGNED8_TEXTURE:
            return GL_UNSIGNED_BYTE;
        case TextureType::UNSIGNED16_TEXTURE:
            return GL_UNSIGNED_SHORT;
        case TextureType::UNSIGNED32_TEXTURE:
            return GL_UNSIGNED_INT;
        case TextureType::NORM8_TEXTURE:
            return GL_UNSIGNED_BYTE;
        case TextureType::NORM16_TEXTURE:
            return GL_UNSIGNED_SHORT;
        case TextureType::NORM32_TEXTURE:
            return GL_UNSIGNED_INT;
        case TextureType::FLOAT16_TEXTURE:
            return GL_HALF_FLOAT;
        case TextureType::FLOAT32_TEXTURE:
            return GL_FLOAT;
        case TextureType::DEPTH32_TEXTURE:
            return GL_FLOAT;
        case TextureType::DEPTH24_STENCIL8_TEXTURE:
            return GL_UNSIGNED_INT_24_8;
        default: {
            throw InvalidVolumeFormat();
        }
    }
}

static GLenum getGLFilteringMode(FilteringMode mode)
{
    switch (mode) {
        case FilteringMode::LINEAR_FILTERING:
            return GL_LINEAR;
        case FilteringMode::NEAREST_FILTERING:
            return GL_NEAREST;
        default: {
            throw InvalidVolumeFormat();
        }
    }
}

void Texture::bind()
{
    GL(glBindTexture(getTarget(), getID()));
}

void Texture::release()
{
    GL(glBindTexture(getTarget(), 0));
}

TextureBase::TextureBase(GLenum target, int channel_count, int levels, TextureType type) :
    _target(target),
    _channel_count(channel_count),
    _levels(levels),
    _internal_format(getGLInternalFormat(channel_count, type)),
    _format(getGLFormat(channel_count, type)),
    _type(getGLType(type))
{
    GL(glGenTextures(1, &_id));
}

TextureBase::TextureBase(GLenum target, int channel_count, int levels, TextureType type, FilteringMode min_filter, FilteringMode mag_filter) :
    TextureBase(target, channel_count, levels, type)
{
    bind();
    {
        GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, getGLFilteringMode(min_filter)));
        GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, getGLFilteringMode(mag_filter)));
    }
    release();
}

TextureBase::~TextureBase()
{
    release();
    GL(glDeleteTextures(1, &_id));
}

GLenum TextureBase::getID() const
{
    return _id;
}

GLenum TextureBase::getTarget() const
{
    return _target;
}

GLenum TextureBase::getInternalFormat() const
{
    return _internal_format;
}

GLenum TextureBase::getFormat() const
{
    return _format;
}

GLenum TextureBase::getType() const
{
    return _type;
}

int TextureBase::getChannelCount() const
{
    return _channel_count;
}

void TextureBase::clear(unsigned int* data)
{
    bind();
    {
        for (int l = 0; l < _levels; ++l) {
            GL(glClearTexImage(getID(), l, getFormat(), GL_UNSIGNED_INT, data));
        }
    }
    release();
}

void TextureBase::clear(float* data)
{
    bind();
    {
        for (int l = 0; l < _levels; ++l) {
            GL(glClearTexImage(getID(), l, getFormat(), GL_FLOAT, data));
        }
    }
    release();
}

TextureView::TextureView(const TextureBase& texture) :
    _target(texture.getTarget()),
    _internal_format(texture.getInternalFormat()),
    _format(texture.getFormat()),
    _type(texture.getType())
{
    GL(glGenTextures(1, &_id));

    GL(glTextureView(_id, _target, texture.getID(), texture.getInternalFormat(), 0, 1, 0, 1));
    bind();
    {
        GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
        GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
    }
    release();
}

GLenum TextureView::getID() const
{
    return _id;
}

GLenum TextureView::getTarget() const
{
    return _target;
}

GLenum TextureView::getInternalFormat() const
{
    return _internal_format;
}

GLenum TextureView::getFormat() const
{
    return _format;
}

GLenum TextureView::getType() const
{
    return _type;
}

Texture2D::Texture2D(int channel_count, TextureType type, int width, int height, int levels) :
    TextureBase(GL_TEXTURE_2D, channel_count, levels, type),
    _width(width),
    _height(height)
{
    bind();
    {
        GL(glTexImage2D(GL_TEXTURE_2D, 0, getInternalFormat(), width, height, 0, getFormat(), getType(), nullptr));
        GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
        GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    }
    release();
}

Texture2D::Texture2D(int channel_count, TextureType type, int width, int height, int levels, FilteringMode min_filter, FilteringMode mag_filter) :
    TextureBase(GL_TEXTURE_2D, channel_count, levels, type, min_filter, mag_filter),
    _width(width),
    _height(height)
{
    bind();
    {
        GL(glTexImage2D(GL_TEXTURE_2D, 0, getInternalFormat(), width, height, 0, getFormat(), getType(), nullptr));
    }
    release();
}

Texture2D::Texture2D(int channel_count, TextureType type, int width, int height, int levels, unsigned char* data) :
    TextureBase(GL_TEXTURE_2D, channel_count, levels, type),
    _width(width),
    _height(height)
{
    bind();
    {
        GL(glTexImage2D(GL_TEXTURE_2D, 0, getInternalFormat(), width, height, 0, getFormat(), getType(), data));
        GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
        GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    }
    release();
}

Texture2D::Texture2D(int channel_count,
                     TextureType type,
                     int width,
                     int height,
                     int levels,
                     unsigned char* data,
                     FilteringMode min_filter,
                     FilteringMode mag_filter) :
    TextureBase(GL_TEXTURE_2D, channel_count, levels, type, min_filter, mag_filter),
    _width(width),
    _height(height)
{
    bind();
    {
        GL(glTexImage2D(GL_TEXTURE_2D, 0, getInternalFormat(), width, height, 0, getFormat(), getType(), data));
    }
    release();
}

Texture2D::~Texture2D()
{
}

void Texture2D::load(const unsigned char* data, int x_offset, int y_offset, int width, int height)
{
    bind();
    {
        GL(glTexSubImage2D(GL_TEXTURE_2D, 0, x_offset, y_offset, width, height, getFormat(), getType(), data));
    }
    release();
}

void Texture2D::resize(int width, int height)
{
    _width = width;
    _height = height;

    bind();
    {
        GL(glTexImage2D(GL_TEXTURE_2D, 0, getInternalFormat(), width, height, 0, getFormat(), getType(), nullptr));
    }
    release();
}

int Texture2D::getWidth() const
{
    return _width;
}

int Texture2D::getHeight() const
{
    return _height;
}

Texture2DImmutable::Texture2DImmutable(int channel_count, TextureType type, int width, int height, int levels) :
    TextureBase(GL_TEXTURE_2D, channel_count, levels, type),
    _width(width),
    _height(height)
{
    bind();
    {
        GL(glTexStorage2D(GL_TEXTURE_2D, 1, getInternalFormat(), width, height));

        GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
        GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    }
    release();
}

Texture2DImmutable::Texture2DImmutable(int channel_count,
                                       TextureType type,
                                       int width,
                                       int height,
                                       int levels,
                                       FilteringMode min_filter,
                                       FilteringMode mag_filter) :
    TextureBase(GL_TEXTURE_2D, channel_count, levels, type, min_filter, mag_filter),
    _width(width),
    _height(height)
{
    bind();
    {
        GL(glTexStorage2D(GL_TEXTURE_2D, 1, getInternalFormat(), width, height));
    }
    release();
}

Texture2DImmutable::Texture2DImmutable(int channel_count, TextureType type, int width, int height, int levels, unsigned char* data) :
    TextureBase(GL_TEXTURE_2D, channel_count, levels, type),
    _width(width),
    _height(height)
{
    bind();
    {
        GL(glTexStorage2D(GL_TEXTURE_2D, 1, getInternalFormat(), width, height));
        load(data, 0, 0, width, height);

        GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
        GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    }
    release();
}

Texture2DImmutable::Texture2DImmutable(int channel_count,
                                       TextureType type,
                                       int width,
                                       int height,
                                       int levels,
                                       unsigned char* data,
                                       FilteringMode min_filter,
                                       FilteringMode mag_filter) :
    TextureBase(GL_TEXTURE_2D, channel_count, levels, type, min_filter, mag_filter),
    _width(width),
    _height(height)
{
    bind();
    {
        GL(glTexImage2D(GL_TEXTURE_2D, 0, getInternalFormat(), width, height, 0, getFormat(), getType(), data));
        load(data, 0, 0, width, height);
    }
    release();
}

Texture2DImmutable::~Texture2DImmutable()
{
}

void Texture2DImmutable::load(const unsigned char* data, int x_offset, int y_offset, int width, int height)
{
    bind();
    {
        GL(glTexSubImage2D(GL_TEXTURE_2D, 0, x_offset, y_offset, width, height, getFormat(), getType(), data));
    }
    release();
}

int Texture2DImmutable::getWidth() const
{
    return _width;
}

int Texture2DImmutable::getHeight() const
{
    return _height;
}

Texture3D::Texture3D(int channel_count, TextureType type, int width, int height, int depth, int levels) :
    TextureBase(GL_TEXTURE_3D, channel_count, levels, type),
    _width(width),
    _height(height),
    _depth(depth)
{
}

Texture3D::Texture3D(int channel_count,
                     TextureType type,
                     int width,
                     int height,
                     int depth,
                     int levels,
                     FilteringMode min_filter,
                     FilteringMode mag_filter) :
    TextureBase(GL_TEXTURE_3D, channel_count, levels, type, min_filter, mag_filter),
    _width(width),
    _height(height),
    _depth(depth)
{
}

int Texture3D::getWidth() const
{
    return _width;
}

int Texture3D::getHeight() const
{
    return _height;
}

int Texture3D::getDepth() const
{
    return _depth;
}

void Texture3D::updateMipmaps()
{
    bind();
    GL(glGenerateMipmap(getTarget()));
}

Texture3DMutable::Texture3DMutable(int channel_count, TextureType type, int width, int height, int depth, int levels) :
    Texture3D(channel_count, type, width, height, depth, levels)
{
    bind();
    {
        GL(glTexImage3D(GL_TEXTURE_3D, 0, getInternalFormat(), width, height, depth, 0, getFormat(), getType(), nullptr));

        GL(glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
        GL(glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    }
    release();
}

Texture3DMutable::Texture3DMutable(int channel_count,
                                   TextureType type,
                                   int width,
                                   int height,
                                   int depth,
                                   int levels,
                                   FilteringMode min_filter,
                                   FilteringMode mag_filter) :
    Texture3D(channel_count, type, width, height, depth, levels, min_filter, mag_filter)
{
    bind();
    {
        GL(glTexImage3D(GL_TEXTURE_3D, 0, getInternalFormat(), width, height, depth, 0, getFormat(), getType(), nullptr));
    }
    release();
}

Texture3DMutable::Texture3DMutable(int channel_count, TextureType type, int width, int height, int depth, int levels, unsigned char* data) :
    Texture3D(channel_count, type, width, height, depth, levels)
{
    bind();
    {
        GL(glTexImage3D(GL_TEXTURE_3D, 0, getInternalFormat(), width, height, depth, 0, getFormat(), getType(), data));

        GL(glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
        GL(glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    }
    release();
}

Texture3DMutable::Texture3DMutable(int channel_count,
                                   TextureType type,
                                   int width,
                                   int height,
                                   int depth,
                                   int levels,
                                   unsigned char* data,
                                   FilteringMode min_filter,
                                   FilteringMode mag_filter) :
    Texture3D(channel_count, type, width, height, depth, levels, min_filter, mag_filter)
{
    bind();
    {
        GL(glTexImage3D(GL_TEXTURE_3D, 0, getInternalFormat(), width, height, depth, 0, getFormat(), getType(), data));
    }
    release();
}

Texture3DMutable::~Texture3DMutable()
{
}

void Texture3DMutable::load(const unsigned char* data, int x_offset, int y_offset, int z_offset, int width, int height, int depth)
{
    bind();
    {
        GL(glTexSubImage3D(GL_TEXTURE_3D, 0, x_offset, y_offset, z_offset, width, height, depth, getFormat(), getType(), data));
    }
    release();
}

void Texture3DMutable::resize(int width, int height, int depth)
{
    _width = width;
    _height = height;
    _depth = depth;

    bind();
    {
        GL(glTexImage3D(GL_TEXTURE_3D, 0, getInternalFormat(), width, height, depth, 0, getFormat(), getType(), nullptr));
    }
    release();
}

Texture3DImmutable::Texture3DImmutable(int channel_count, TextureType type, int width, int height, int depth, int levels) :
    Texture3D(channel_count, type, width, height, depth, levels)
{
    bind();
    {
        GL(glTexStorage3D(GL_TEXTURE_3D, levels, getInternalFormat(), width, height, depth));

        GL(glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
        GL(glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    }
    release();
}

Texture3DImmutable::Texture3DImmutable(int channel_count,
                                       TextureType type,
                                       int width,
                                       int height,
                                       int depth,
                                       int levels,
                                       FilteringMode min_filter,
                                       FilteringMode mag_filter) :
    Texture3D(channel_count, type, width, height, depth, levels, min_filter, mag_filter)
{
    bind();
    {
        GL(glTexStorage3D(GL_TEXTURE_3D, levels, getInternalFormat(), width, height, depth));
    }
    release();
}

Texture3DImmutable::Texture3DImmutable(int channel_count,
                                       TextureType type,
                                       int width,
                                       int height,
                                       int depth,
                                       int levels,
                                       const unsigned char* data) :
    Texture3D(channel_count, type, width, height, depth, levels)
{
    bind();
    {
        GL(glTexStorage3D(GL_TEXTURE_3D, levels, getInternalFormat(), width, height, depth));

        GL(glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
        GL(glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

        load(data, 0, 0, 0, width, height, depth);
    }
    release();
}

Texture3DImmutable::Texture3DImmutable(int channel_count,
                                       TextureType type,
                                       int width,
                                       int height,
                                       int depth,
                                       int levels,
                                       FilteringMode min_filter,
                                       FilteringMode mag_filter,
                                       const unsigned char* data) :
    Texture3D(channel_count, type, width, height, depth, levels, min_filter, mag_filter)
{
    bind();
    {
        GL(glTexStorage3D(GL_TEXTURE_3D, levels, getInternalFormat(), width, height, depth));

        load(data, 0, 0, 0, width, height, depth);
    }
    release();
}

Texture3DImmutable::Texture3DImmutable(int channel_count,
                                       TextureType type,
                                       int width,
                                       int height,
                                       int depth,
                                       int levels,
                                       const float* data) :
    Texture3D(channel_count, type, width, height, depth, levels)
{
    bind();
    {
        GL(glTexStorage3D(GL_TEXTURE_3D, levels, getInternalFormat(), width, height, depth));

        GL(glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
        GL(glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

        load(data, 0, 0, 0, width, height, depth);
    }
    release();
}

Texture3DImmutable::Texture3DImmutable(int channel_count,
                                       TextureType type,
                                       int width,
                                       int height,
                                       int depth,
                                       int levels,
                                       FilteringMode min_filter,
                                       FilteringMode mag_filter,
                                       const float* data) :
    Texture3D(channel_count, type, width, height, depth, levels, min_filter, mag_filter)
{
    bind();
    {
        GL(glTexStorage3D(GL_TEXTURE_3D, levels, getInternalFormat(), width, height, depth));

        load(data, 0, 0, 0, width, height, depth);
    }
    release();
}

Texture3DImmutable::~Texture3DImmutable()
{
}

void Texture3DImmutable::load(const unsigned char* data, int x_offset, int y_offset, int z_offset, int width, int height, int depth)
{
    bind();
    {
        GL(glTexSubImage3D(GL_TEXTURE_3D, 0, x_offset, y_offset, z_offset, width, height, depth, getFormat(), getType(), data));
    }
    release();
}

void Texture3DImmutable::load(const float* data, int x_offset, int y_offset, int z_offset, int width, int height, int depth)
{
    bind();
    {
        GL(glTexSubImage3D(GL_TEXTURE_3D, 0, x_offset, y_offset, z_offset, width, height, depth, getFormat(), GL_FLOAT, data));
    }
    release();
}

}