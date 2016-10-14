#pragma once

#include <d2d1.h>
#include <wincodec.h>

#include "AStarAlgorithm.h"
#include "Graphics.h"

class Unit
{
private:
	ID2D1Bitmap *m_bmp = nullptr;
	int m_locationX, m_locationY;
	std::vector<std::shared_ptr<AStarNode>> m_path;
	int m_timeSinceLastMove = 0;
public:
	Unit(int locationX, int locationY);
	~Unit();

	bool Init(Graphics *graphics);
	void Update();
	void Draw(Graphics *graphics) const;

	void Move(int locationX, int locationY);
};
