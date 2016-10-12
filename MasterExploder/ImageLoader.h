#pragma once

#include <d2d1.h>
#include <wincodec.h>

#include "Graphics.h"

class ImageLoader
{
public:
	static bool LoadSprite(Graphics *graphics, wchar_t *filename, ID2D1Bitmap **bmp);
};