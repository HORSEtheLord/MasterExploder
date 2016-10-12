#include "Unit.h"
#include "Logger.h"
#include "Utils.h"

Unit::Unit(int locationX, int locationY)
	: m_locationX(locationX), m_locationY(locationY)
{
}

Unit::~Unit()
{
	if (m_bmp)
		m_bmp->Release();
}

bool Unit::Init(Graphics *graphics)
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

	wchar_t *filename = L"unit1.png";

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
		&m_bmp);

	if (res != S_OK)
	{
		Logger::Log(L"ID2D1Bitmap creation failed.");
		safeReleaseResources(wicFactory, wicDecoder, wicFrame, wicConverter);
		return false;
	}

	safeReleaseResources(wicFactory, wicDecoder, wicFrame, wicConverter);
	return true;
}

void Unit::Draw(Graphics *graphics) const
{
	int width = TILE_WIDTH;
	int height = TILE_HEIGHT;

	int locationX = m_locationX * width;
	int locationY = m_locationY * height;

	graphics->GetRenderTarget()->DrawBitmap(
		m_bmp,
		D2D1::RectF(locationX, locationY, locationX + width, locationY + height),
		1.0f,
		D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
		D2D1::RectF(0.0f, 0.0f, m_bmp->GetSize().width, height = m_bmp->GetSize().height));
}

void Unit::Move(int locationX, int locationY)
{
	m_locationX = locationX;
	m_locationY = locationY;
}