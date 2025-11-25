#pragma once

#include <GL/glew.h>

namespace gl {

enum TextureType
{
    INT8_TEXTURE,
    INT16_TEXTURE,
    INT32_TEXTURE,
    UNSIGNED8_TEXTURE,
    UNSIGNED16_TEXTURE,
    UNSIGNED32_TEXTURE,
    NORM8_TEXTURE,
    NORM16_TEXTURE,
    NORM32_TEXTURE,
    FLOAT16_TEXTURE,
    FLOAT32_TEXTURE,
    DEPTH32_TEXTURE,
    DEPTH24_STENCIL8_TEXTURE
};

enum FilteringMode
{
    LINEAR_FILTERING,
    NEAREST_FILTERING
};

class Texture {
public:
    virtual ~Texture() = default;
    virtual GLenum getID() const = 0;
    virtual GLenum getTarget() const = 0;
    virtual GLenum getInternalFormat() const = 0;
    virtual GLenum getFormat() const = 0;
    virtual GLenum getType() const = 0;

    void bind();
    void release();
};

class TextureBase : public Texture {
public:
    TextureBase(GLenum target, int channel_count, int levels, TextureType type);
    TextureBase(GLenum target, int channel_count, int levels, TextureType type, FilteringMode min_filter, FilteringMode mag_filter);
    virtual ~TextureBase();

    void clear(unsigned int* data);
    void clear(float* data);

    GLenum getID() const override;
    GLenum getTarget() const override;
    GLenum getInternalFormat() const override;
    GLenum getFormat() const override;
    GLenum getType() const override;
    int getChannelCount() const;

private:
    GLenum _id;
    GLenum _target;
    int _channel_count;
    int _levels;
    GLenum _internal_format;
    GLenum _format;
    GLenum _type;
};

class TextureView : public Texture {
public:
    TextureView(const TextureBase& texture);

    GLenum getID() const override;
    GLenum getTarget() const override;
    GLenum getInternalFormat() const override;
    GLenum getFormat() const override;
    GLenum getType() const override;

private:
    GLuint _id;
    GLenum _target;
    GLenum _internal_format;
    GLenum _format;
    GLenum _type;
};

class Texture2D : public TextureBase {
public:
    Texture2D(int channel_count, TextureType type, int width, int height, int levels);
    Texture2D(int channel_count, TextureType type, int width, int height, int levels, FilteringMode min_filter, FilteringMode mag_filter);
    Texture2D(int channel_count, TextureType type, int width, int height, int levels, unsigned char* data);
    Texture2D(int channel_count,
              TextureType type,
              int width,
              int height,
              int levels,
              unsigned char* data,
              FilteringMode min_filter,
              FilteringMode mag_filter);
    ~Texture2D();

    void load(const unsigned char* data, int x_offset, int y_offset, int width, int height);
    void resize(int width, int height);

    int getWidth() const;
    int getHeight() const;

private:
    int _width;
    int _height;
};

class Texture2DImmutable : public TextureBase {
public:
    Texture2DImmutable(int channel_count, TextureType type, int width, int height, int levels);
    Texture2DImmutable(int channel_count, TextureType type, int width, int height, int levels, FilteringMode min_filter, FilteringMode mag_filter);
    Texture2DImmutable(int channel_count, TextureType type, int width, int height, int levels, unsigned char* data);
    Texture2DImmutable(int channel_count,
                       TextureType type,
                       int width,
                       int height,
                       int levels,
                       unsigned char* data,
                       FilteringMode min_filter,
                       FilteringMode mag_filter);
    ~Texture2DImmutable();

    void load(const unsigned char* data, int x_offset, int y_offset, int width, int height);

    int getWidth() const;
    int getHeight() const;

private:
    int _width;
    int _height;
};

class Texture3D : public TextureBase {
public:
    Texture3D(int channel_count, TextureType type, int width, int height, int depth, int levels);
    Texture3D(int channel_count, TextureType type, int width, int height, int depth, int levels, FilteringMode min_filter, FilteringMode mag_filter);

    int getWidth() const;
    int getHeight() const;
    int getDepth() const;

    void updateMipmaps();

    virtual void load(const unsigned char* data, int x_offset, int y_offset, int z_offset, int width, int height, int depth) = 0;

protected:
    int _width;
    int _height;
    int _depth;
};

class Texture3DMutable : public Texture3D {
public:
    Texture3DMutable(int channel_count, TextureType type, int width, int height, int depth, int levels);
    Texture3DMutable(int channel_count,
                     TextureType type,
                     int width,
                     int height,
                     int depth,
                     int levels,
                     FilteringMode min_filter,
                     FilteringMode mag_filter);
    Texture3DMutable(int channel_count, TextureType type, int width, int height, int depth, int levels, unsigned char* data);
    Texture3DMutable(int channel_count,
                     TextureType type,
                     int width,
                     int height,
                     int depth,
                     int levels,
                     unsigned char* data,
                     FilteringMode min_filter,
                     FilteringMode mag_filter);
    ~Texture3DMutable();

    void load(const unsigned char* data, int x_offset, int y_offset, int z_offset, int width, int height, int depth) override;
    void resize(int width, int height, int depth);
};

class Texture3DImmutable : public Texture3D {
public:
    Texture3DImmutable(int channel_count, TextureType type, int width, int height, int depth, int levels);
    Texture3DImmutable(int channel_count,
                       TextureType type,
                       int width,
                       int height,
                       int depth,
                       int levels,
                       FilteringMode min_filter,
                       FilteringMode mag_filter);
    Texture3DImmutable(int channel_count, TextureType type, int width, int height, int depth, int levels, const unsigned char* data);
    Texture3DImmutable(int channel_count,
                       TextureType type,
                       int width,
                       int height,
                       int depth,
                       int levels,
                       FilteringMode min_filter,
                       FilteringMode mag_filter,
                       const unsigned char* data);
    Texture3DImmutable(int channel_count, TextureType type, int width, int height, int depth, int levels, const float* data);
    Texture3DImmutable(int channel_count,
                       TextureType type,
                       int width,
                       int height,
                       int depth,
                       int levels,
                       FilteringMode min_filter,
                       FilteringMode mag_filter,
                       const float* data);
    ~Texture3DImmutable();

    void load(const unsigned char* data, int x_offset, int y_offset, int z_offset, int width, int height, int depth) override;
    void load(const float* data, int x_offset, int y_offset, int z_offset, int width, int height, int depth);
};

}
