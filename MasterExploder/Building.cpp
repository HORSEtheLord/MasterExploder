#include "Building.h"
#include "ImageLoader.h"
#include "Logger.h"
#include "Utils.h"

Building::Building(int locationX, int locationY, int hp)
	: m_locationX(locationX), m_locationY(locationY), m_maxHitPoints(hp), m_currentHitPoints(hp)
{
}

Building::~Building()
{
	if (m_bmp)
		m_bmp->Release();
}

bool Building::ReceiveDamage(int damage)
{
	if (damage >= m_currentHitPoints)
	{
		m_currentHitPoints = 0;
		m_isDestroyed = true;
	}
	else
	{
		m_currentHitPoints -= damage;
	}

	return m_isDestroyed;
}

bool Building::Init(std::shared_ptr<Graphics> graphics)
{
	wchar_t *filename = L"building1.png";

	if (!ImageLoader::LoadSprite(graphics, filename, &m_bmp))
	{
		Logger::Log(L"Building sprite loading failed. File: " + std::wstring(filename));
		return false;
	}

	wchar_t *filenameDestroyed = L"building1_destroyed.png";

	if (!ImageLoader::LoadSprite(graphics, filenameDestroyed, &m_bmpDestroyed))
	{
		Logger::Log(L"Building sprite loading failed. File: " + std::wstring(filenameDestroyed));
		return false;
	}

	return true;
}

void Building::Draw(std::shared_ptr<Graphics> graphics) const
{
	int width = TILE_WIDTH;
	int height = TILE_HEIGHT;

	int locationX = m_locationX * width;
	int locationY = m_locationY * height;

	ID2D1Bitmap *bmp = m_isDestroyed ? m_bmpDestroyed : m_bmp;

	graphics->GetRenderTarget()->DrawBitmap(
		bmp,
		D2D1::RectF(locationX, locationY, locationX + width, locationY + height),
		1.0f,
		D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
		D2D1::RectF(0.0f, 0.0f, bmp->GetSize().width, bmp->GetSize().height));
}
