#include "Terrain.h"
#include "Logger.h"
#include "Utils.h"
#include "ImageLoader.h"

Terrain::Terrain(int terrainWidth, int terrainHeight, bool drawMesh)
	: m_terrainWidth(terrainWidth), m_terrainHeight(terrainHeight), m_drawMesh(drawMesh)
{
}

Terrain::~Terrain()
{
	if (m_bmp)
		m_bmp->Release();
}

bool Terrain::Init(Graphics *graphics)
{
	return ImageLoader::LoadSprite(graphics, L"tile1.png", &m_bmp);
}


void Terrain::Draw(Graphics *graphics) const
{
	D2D1_RECT_F sourceRect = D2D1::RectF(0.0f, 0.0f, m_bmp->GetSize().width, m_bmp->GetSize().height);

	int windowWidth = graphics->GetRenderTarget()->GetSize().width;
	int windowHeight = graphics->GetRenderTarget()->GetSize().height;

	int tileWidth = TILE_WIDTH;
	int tileHeight = TILE_HEIGHT;

	int x = 0, y = 0;

	for (int i = 0; i < m_terrainWidth; ++i)
	{
		for (int j = 0; j < m_terrainHeight; ++j)
		{
			x = i * tileWidth;
			y = j * tileHeight;
			graphics->GetRenderTarget()->DrawBitmap(
				m_bmp,
				D2D1::RectF(x, y, x + tileWidth, y + tileHeight),
				1.0f,
				D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
				sourceRect);
		}
	}

	if (m_drawMesh)
	{
		ID2D1SolidColorBrush *brush = nullptr;
		HRESULT res = graphics->GetRenderTarget()->CreateSolidColorBrush(D2D1::ColorF(0, 0, 0, 0.2f), &brush);
		if (res != S_OK)
		{
			Logger::Log(L"ID2D1SolidColorBrush creation failed.");
			return;
		}

		for (float i = tileWidth; i < windowWidth; i += tileWidth)
		{
			graphics->GetRenderTarget()->DrawLine(
				D2D1::Point2F(i, 0),
				D2D1::Point2F(i, windowHeight),
				brush);
		}

		for (float j = tileHeight; j < windowHeight; j += tileHeight)
		{
			graphics->GetRenderTarget()->DrawLine(
				D2D1::Point2F(0, j),
				D2D1::Point2F(windowWidth, j),
				brush);
		}

		brush->Release();
	}
}