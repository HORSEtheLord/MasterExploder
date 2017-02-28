#pragma once
#include <array>
#include <d2d1.h>
#include "Graphics.h"
#include "PositionComponent.h"

class SpriteManager
{
private:
	std::array<ID2D1Bitmap*, 10> m_bitmaps;
	SpriteManager();
public:
	SpriteManager(const SpriteManager&) = delete;
	~SpriteManager();

	void operator=(const SpriteManager&) = delete;

	bool Load(const Graphics &graphics);
	void Unload();
	static SpriteManager& GetInstance()
	{
		static SpriteManager instance;
		return instance;
	}

	ID2D1Bitmap* GetSprite(SpriteId spriteId);
};
