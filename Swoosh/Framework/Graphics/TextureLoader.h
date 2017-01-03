#pragma once

#include <memory>
#include "Framework/Graphics/Texture.h"

// Load texture
static std::shared_ptr<Texture> loadTexture(std::string filePath)
{
	Bitmap bmp = Bitmap::bitmapFromFile(filePath);
	bmp.flipVertically();
	return std::make_shared<Texture>(Texture(bmp));
}