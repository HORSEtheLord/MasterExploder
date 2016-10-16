#pragma once

#include <d2d1.h>
#include <memory>
#include <vector>
#include <wincodec.h>

#include "Graphics.h"

class Terrain
{
private:
	ID2D1Bitmap *m_bmpFree = nullptr;
	ID2D1Bitmap *m_bmpBlocked = nullptr;
	size_t m_terrainWidth = 0, m_terrainHeight = 0;
	std::shared_ptr<std::vector<bool>> m_map = nullptr;
	bool m_drawMesh = false;
public:
	Terrain(size_t terrainWidth, size_t terrainHeight, bool drawMesh = false);
	Terrain(const Terrain &other) = delete;
	~Terrain();

	std::shared_ptr<std::vector<bool>> GetMap() const { return m_map; }

	bool Init(std::shared_ptr<Graphics> graphics);
	void Draw(std::shared_ptr<Graphics> graphics) const;
};
