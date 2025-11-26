#include "textureManager.h"
#include <iostream>
#include <QImage>

void TextureManager::loadTexture(std::unique_ptr<gl::Texture2D>& texture, const std::string& texturePath)
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
    
    texture = std::make_unique<gl::Texture2D>(
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