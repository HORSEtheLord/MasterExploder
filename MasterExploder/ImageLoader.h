#pragma once

#include <d2d1.h>

#include "Graphics.h"

class ImageLoader
{
public:
	static bool LoadSprite(const Graphics &graphics, wchar_t *filename, ID2D1Bitmap **bmp);
};