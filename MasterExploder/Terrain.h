#pragma once

#include <d2d1.h>
#include <wincodec.h>

#include "Graphics.h"

class Terrain
{
private:
	ID2D1Bitmap *m_bmp = nullptr;
	int m_terrainWidth = 0, m_terrainHeight = 0;
	bool m_drawMesh = false;
public:
	Terrain(int terrainWidth, int terrainHeight, bool drawMesh = false);
	~Terrain();

	bool Init(Graphics *graphics);
	void Draw(Graphics *graphics) const;
};
