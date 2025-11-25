#include "component.h"
#include <glm/glm.hpp>
#include <iostream>
#include <QImage>

Component::Component()
{
}

Component::Component(const std::string& texturePath)
{
    loadTexture(texturePath);
}

Component::~Component() = default;

void Component::resize(int w, int h)
{
    _width = w;
    _height = h;
}

void Component::init()
{
}

void Component::draw(Shader* shader)
{
    if (shader) {
        shader->setUniformAttrib("color", glm::vec4(1.0f, 0.0f, 1.0f, 1.0f));
    }
}

void Component::keyPressEvent(QKeyEvent *event)
{
}

void Component::mousePressEvent(QMouseEvent *event)
{
}

void Component::loadTexture(const std::string& texturePath)
{
    if(texturePath.empty()) {
        return;
    }

    QImage image(texturePath.c_str());
    if (image.isNull()) {
        std::cerr << "Failed to load texture: " << texturePath.c_str() << std::endl;
        image = QImage(256, 256, QImage::Format_RGB888);
        image.fill(QColor(100, 150, 200));
    }
    
    bool hasAlpha = image.hasAlphaChannel();
    QImage convertedImage = hasAlpha ? image.convertToFormat(QImage::Format_RGBA8888) : image.convertToFormat(QImage::Format_RGB888);
    int width = convertedImage.width();
    int height = convertedImage.height();
    int channels = hasAlpha ? 4 : 3;
    
    const unsigned char* imageData = convertedImage.constBits();
    std::vector<unsigned char> textureData(imageData, imageData + width * height * channels);
    
    _texture = std::make_unique<gl::Texture2D>(
        channels,
        gl::TextureType::NORM8_TEXTURE,
        width,
        height,
        1,
        textureData.data(),
        gl::FilteringMode::LINEAR_FILTERING,
        gl::FilteringMode::LINEAR_FILTERING
    );
}

bool Component::isPointInside(float x, float y) const
{
    return false;
}