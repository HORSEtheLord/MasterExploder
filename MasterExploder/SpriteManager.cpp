#include "SpriteManager.h"
#include <vector>
#include "ImageLoader.h"
#include "Logger.h"

SpriteManager::SpriteManager()
{
}

SpriteManager::~SpriteManager()
{
}

bool SpriteManager::Load(const Graphics &graphics)
{
	std::vector<wchar_t*> filenames
	{ 
		L"unit1.png",
		L"tile1.png",
		L"tile2.png"
	};

	std::fill(m_bitmaps.begin(), m_bitmaps.end(), nullptr);

	int counter = 0;
	for (auto it = filenames.cbegin(); it != filenames.cend(); ++it)
	{
		if (!ImageLoader::LoadSprite(graphics, *it, &m_bitmaps[counter]))
		{
			Logger::Log(L"Sprite loading failed. File: " + std::wstring(*it));
			return false;
		}

		++counter;
	}

	return true;
}

void SpriteManager::Unload()
{
	for (ID2D1Bitmap *bitmap : m_bitmaps)
	{
		if (bitmap)
			bitmap->Release();
	}
}

ID2D1Bitmap* SpriteManager::GetSprite(SpriteId spriteId)
{
	return m_bitmaps[spriteId];
}
