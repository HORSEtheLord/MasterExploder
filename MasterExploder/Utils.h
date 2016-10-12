#pragma once

#include <wincodec.h>

#define TILE_WIDTH 40
#define TILE_HEIGHT 40
#define MS_PER_UPDATE 50

void safeReleaseResources(IWICImagingFactory *wicFactory,
	IWICBitmapDecoder *wicDecoder,
	IWICBitmapFrameDecode *wicFrame,
	IWICFormatConverter *wicConverter);
