#include <ctime>
#include <random>

#include "Terrain.h"
#include "Logger.h"
#include "Utils.h"
#include "ImageLoader.h"

Terrain::Terrain(size_t terrainWidth, size_t terrainHeight, bool drawMesh)
	: GameObject(L"Terrain"), m_terrainWidth(terrainWidth), m_terrainHeight(terrainHeight), m_drawMesh(drawMesh)
{
	m_map = std::make_shared<std::vector<TerrainType>>();
	m_map->reserve(terrainWidth * terrainHeight);

	m_collisionMap = std::make_shared<std::vector<bool>>();
	m_collisionMap->reserve(terrainWidth * terrainHeight);

	std::default_random_engine engine(time(0));
	std::uniform_int_distribution<unsigned> distribution(0, 4);

	m_map->push_back(TerrainType::Empty);
	m_collisionMap->push_back(false);

	bool empty;

	for (int i = 1; i + 1 < terrainWidth * terrainHeight; ++i)
	{
		empty = distribution(engine);

		m_map->push_back(empty ? TerrainType::Empty : TerrainType::Rock);
		m_collisionMap->push_back(!empty);
	}

	m_map->push_back(TerrainType::Empty);
	m_collisionMap->push_back(true);
}

Terrain::~Terrain()
{
	for (auto it = m_bitmaps.cbegin(); it != m_bitmaps.cend(); ++it)
	{
		if (*(it->second))
			(*(it->second))->Release();
	}
}

bool Terrain::Init(std::shared_ptr<Graphics> graphics)
{
	wchar_t *filenameFree = L"tile1.png";

	m_bitmaps[TerrainType::Empty] = new ID2D1Bitmap*;

	if (!ImageLoader::LoadSprite(graphics, filenameFree, m_bitmaps[TerrainType::Empty]))
	{
		Logger::Log(L"Sprite loading failed. File: " + std::wstring(filenameFree));
		return false;
	}

	wchar_t *filenameBlocked = L"tile2.png";

	m_bitmaps[TerrainType::Rock] = new ID2D1Bitmap*;

	if (!ImageLoader::LoadSprite(graphics, filenameBlocked, m_bitmaps[TerrainType::Rock]))
	{
		Logger::Log(L"Sprite loading failed. File: " + std::wstring(filenameBlocked));
		return false;
	}

	return true;
}

void Terrain::Update()
{
}

void Terrain::Draw(std::shared_ptr<Graphics> graphics) const
{
	int windowWidth = graphics->GetRenderTarget()->GetSize().width;
	int windowHeight = graphics->GetRenderTarget()->GetSize().height;

	int tileWidth = TILE_WIDTH;
	int tileHeight = TILE_HEIGHT;

	int x = 0, y = 0;

	ID2D1Bitmap *bmp = nullptr;

	for (int i = 0; i < m_terrainWidth; ++i)
	{
		for (int j = 0; j < m_terrainHeight; ++j)
		{
			TerrainType terrainType = (*m_map)[i * m_terrainHeight + j];
			bmp = *m_bitmaps.at(terrainType);

			x = i * tileWidth;
			y = j * tileHeight;
			graphics->GetRenderTarget()->DrawBitmap(
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