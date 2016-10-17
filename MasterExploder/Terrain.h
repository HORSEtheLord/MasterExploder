#pragma once

#include <d2d1.h>
#include <memory>
#include <unordered_map>
#include <vector>
#include <wincodec.h>

#include "Graphics.h"
#include "Utils.h"

class Terrain
{
public:
	enum class TerrainType
	{
		Empty,
		Rock
	};

private:
	size_t m_terrainWidth = 0, m_terrainHeight = 0;
	std::shared_ptr<std::vector<TerrainType>> m_map = nullptr;
	std::shared_ptr<std::vector<bool>> m_collisionMap = nullptr;

	std::unordered_map<TerrainType, ID2D1Bitmap**, EnumClassHash> m_bitmaps;

	bool m_drawMesh = false;
public:
	Terrain(size_t terrainWidth, size_t terrainHeight, bool drawMesh = false);
	Terrain(const Terrain &other) = delete;
	~Terrain();

	void operator=(const Terrain &other) = delete;

	std::shared_ptr<std::vector<bool>> GetCollisionMap() const { return m_collisionMap; }

	bool Init(std::shared_ptr<Graphics> graphics);
	void Draw(std::shared_ptr<Graphics> graphics) const;
};
