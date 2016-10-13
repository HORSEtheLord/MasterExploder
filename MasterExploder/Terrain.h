#pragma once

#include <d2d1.h>
#include <wincodec.h>

#include "Graphics.h"

class Terrain
{
private:
	ID2D1Bitmap *m_bmpFree = nullptr;
	ID2D1Bitmap *m_bmpBlocked = nullptr;
	int m_terrainWidth = 0, m_terrainHeight = 0;
	bool *m_map = nullptr;
	bool m_drawMesh = false;
public:
	Terrain(int terrainWidth, int terrainHeight, bool drawMesh = false);
	~Terrain();

	bool* GetMap() { return m_map; }

	bool Init(Graphics *graphics);
	void Draw(Graphics *graphics) const;
};
