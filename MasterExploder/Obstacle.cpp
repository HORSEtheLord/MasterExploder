#include "Obstacle.h"
#include "ImageLoader.h"
#include "Logger.h"
#include "Utils.h"

Obstacle::Obstacle(int locationX, int locationY)
	: GameObject(L"Obstacle", locationX, locationY)
{
}

Obstacle::~Obstacle()
{
	if (m_bmp)
		m_bmp->Release();
}

bool Obstacle::Init(std::shared_ptr<Graphics> graphics)
{
	/*wchar_t *filename = L"tile2.png";

	if (!ImageLoader::LoadSprite(graphics, filename, &m_bmp))
	{
		Logger::Log(GetName() + L" sprite loading failed. File: " + std::wstring(filename));
		return false;
	}*/

	return true;
}

void Obstacle::Update()
{
}

void Obstacle::Draw(std::shared_ptr<Graphics> graphics) const
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
		D2D1::RectF(0.0f, 0.0f, m_bmp->GetSize().width, m_bmp->GetSize().height));
}