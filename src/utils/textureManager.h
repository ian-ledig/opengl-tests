#pragma once

#include <map>
#include <string>
#include <memory>
#include "gl/texture.h"

class TextureManager {
public:
    static void loadTexture(std::unique_ptr<gl::Texture2D>& texture,const std::string& texturePath);
};