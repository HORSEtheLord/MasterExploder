#pragma once

#include <Windows.h>
#include <d2d1.h>

class Graphics
{
private:
	ID2D1Factory *factory = nullptr;
	ID2D1HwndRenderTarget *renderTarget = nullptr;
public:
	Graphics();
	Graphics(const Graphics &other) = delete;
	~Graphics();

	void operator=(const Graphics&) = delete;

	bool Init(HWND windowHandle);

	ID2D1RenderTarget *GetRenderTarget() const
	{
		return renderTarget;
	}

	void BeginDraw() const { renderTarget->BeginDraw(); }
	void EndDraw() const { renderTarget->EndDraw(); }

	void ClearScreen(float r, float g, float b) const;
};