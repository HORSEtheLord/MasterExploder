#include <ctime>
#include <random>

#include "Terrain.h"
#include "Logger.h"
#include "Utils.h"
#include "ImageLoader.h"
#include "SpriteManager.h"

Terrain::Terrain(size_t terrainWidth, size_t terrainHeight, bool drawMesh)
	: m_terrainWidth(terrainWidth), m_terrainHeight(terrainHeight), m_drawMesh(drawMesh)
{
	m_bitmaps[TerrainType::Empty] = 1;

	m_map = std::make_shared<std::vector<TerrainType>>();
	m_map->reserve(terrainWidth * terrainHeight);

	for (int i = 0; i < terrainWidth * terrainHeight; ++i)
	{
		m_map->push_back(TerrainType::Empty);
	}
}

Terrain::~Terrain()
{
}

void Terrain::Draw(const Graphics &graphics) const
{
	int windowWidth = graphics.GetRenderTarget()->GetSize().width;
	int windowHeight = graphics.GetRenderTarget()->GetSize().height;

	int tileWidth = TILE_WIDTH;
	int tileHeight = TILE_HEIGHT;

	int x, y;

	ID2D1Bitmap *bmp;

	for (int i = 0; i < m_terrainWidth; ++i)
	{
		for (int j = 0; j < m_terrainHeight; ++j)
		{
			TerrainType terrainType = (*m_map)[i * m_terrainHeight + j];
			SpriteId spriteId = m_bitmaps.at(terrainType);
			bmp = SpriteManager::GetInstance().GetSprite(spriteId);

			x = i * tileWidth;
			y = j * tileHeight;
			graphics.GetRenderTarget()->DrawBitmap(
				bmp,
				D2D1::RectF(x, y, x + tileWidth, y + tileHeight),
				1.0f,
				D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
				D2D1::RectF(0.0f, 0.0f, bmp->GetSize().width, bmp->GetSize().height));
		}
	}

	if (m_drawMesh)
	{
		ID2D1SolidColorBrush *brush = nullptr;
		HRESULT res = graphics.GetRenderTarget()->CreateSolidColorBrush(D2D1::ColorF(0, 0, 0, 0.2f), &brush);
		if (res != S_OK)
		{
			Logger::Log(L"ID2D1SolidColorBrush creation failed.");
			return;
		}

		for (float i = tileWidth; i < windowWidth; i += tileWidth)
		{
			graphics.GetRenderTarget()->DrawLine(
				D2D1::Point2F(i, 0),
				D2D1::Point2F(i, windowHeight),
				brush);
		}

		for (float j = tileHeight; j < windowHeight; j += tileHeight)
		{
			graphics.GetRenderTarget()->DrawLine(
				D2D1::Point2F(0, j),
				D2D1::Point2F(windowWidth, j),
				brush);
		}

		brush->Release();
	}
}