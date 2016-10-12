#include "Graphics.h"
#include "Logger.h"

Graphics::Graphics()
{
}

Graphics::~Graphics()
{
	if (factory)
		factory->Release();
	if (renderTarget)
		renderTarget->Release();
}

bool Graphics::Init(HWND windowHandle)
{
	HRESULT res = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory);
	if (res != S_OK)
	{
		Logger::Log(L"D2D1Factory creation failed.");
		return false;
	}

	RECT rect;
	GetClientRect(windowHandle, &rect);

	res = factory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(windowHandle, D2D1::SizeU(rect.right, rect.bottom)),
		&renderTarget);

	if (res != S_OK)
	{
		Logger::Log(L"D2D1RenderTarget creation failed.");
		return false;
	}

	return true;
}

void Graphics::ClearScreen(float r, float g, float b) const
{
	renderTarget->Clear(D2D1::ColorF(r, g, b));
}