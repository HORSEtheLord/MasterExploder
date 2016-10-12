#include "Utils.h"

void safeReleaseResources(IWICImagingFactory *wicFactory,
	IWICBitmapDecoder *wicDecoder,
	IWICBitmapFrameDecode *wicFrame,
	IWICFormatConverter *wicConverter)
{
	if (wicFactory) wicFactory->Release();
	if (wicDecoder) wicDecoder->Release();
	if (wicFrame) wicFrame->Release();
	if (wicConverter) wicConverter->Release();
}