#pragma once

#include <wincodec.h>

#define TILE_WIDTH 40
#define TILE_HEIGHT 40

void safeReleaseResources(IWICImagingFactory *wicFactory,
	IWICBitmapDecoder *wicDecoder,
	IWICBitmapFrameDecode *wicFrame,
	IWICFormatConverter *wicConverter);
