#include "ImageLoader.h"
#include "Logger.h"

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

bool ImageLoader::LoadSprite(Graphics *graphics, wchar_t *filename, ID2D1Bitmap **bmp)
{
	HRESULT res;

	IWICImagingFactory *wicFactory = nullptr;
	IWICBitmapDecoder *wicDecoder = nullptr;
	IWICBitmapFrameDecode *wicFrame = nullptr;
	IWICFormatConverter *wicConverter = nullptr;

	//MKOS: musi byæ po ShowWindow (main)
	//nie wiem dlaczego
	res = CoCreateInstance(
		CLSID_WICImagingFactory,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_IWICImagingFactory,
		(LPVOID*)&wicFactory);

	if (res != S_OK)
	{
		Logger::Log(L"IWICImagingFactory creation failed.");
		safeReleaseResources(wicFactory, wicDecoder, wicFrame, wicConverter);
		return false;
	}

	res = wicFactory->CreateDecoderFromFilename(
		filename,
		NULL,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&wicDecoder);

	if (res != S_OK)
	{
		Logger::Log(L"IWICBitmapDecoder creation failed. File: " + std::wstring(filename));
		safeReleaseResources(wicFactory, wicDecoder, wicFrame, wicConverter);
		return false;
	}

	res = wicDecoder->GetFrame(0, &wicFrame);

	if (res != S_OK)
	{
		Logger::Log(L"Failed to get IWICBitmapFrameDecode.");
		safeReleaseResources(wicFactory, wicDecoder, wicFrame, wicConverter);
		return false;
	}

	res = wicFactory->CreateFormatConverter(&wicConverter);

	if (res != S_OK)
	{
		Logger::Log(L"IWICFormatConverter creation failed.");
		safeReleaseResources(wicFactory, wicDecoder, wicFrame, wicConverter);
		return false;
	}

	res = wicConverter->Initialize(
		wicFrame,
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		NULL,
		0.0,
		WICBitmapPaletteTypeCustom);

	if (res != S_OK)
	{
		Logger::Log(L"IWICFormatConverter initialization failed.");
		safeReleaseResources(wicFactory, wicDecoder, wicFrame, wicConverter);
		return false;
	}

	res = graphics->GetRenderTarget()->CreateBitmapFromWicBitmap(
		wicConverter,
		NULL,
		bmp);

	if (res != S_OK)
	{
		Logger::Log(L"ID2D1Bitmap creation failed.");
		safeReleaseResources(wicFactory, wicDecoder, wicFrame, wicConverter);
		return false;
	}

	safeReleaseResources(wicFactory, wicDecoder, wicFrame, wicConverter);
	return true;
}