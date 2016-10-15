#pragma once

#include <d2d1.h>
#include <memory>
#include <wincodec.h>

#include "Graphics.h"

class ImageLoader
{
public:
	static bool LoadSprite(std::shared_ptr<Graphics> graphics, wchar_t *filename, ID2D1Bitmap **bmp);
};