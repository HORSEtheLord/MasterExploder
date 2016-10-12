#pragma once

#include <d2d1.h>
#include <wincodec.h>

#include "Graphics.h"

class Unit
{
private:
	ID2D1Bitmap *m_bmp = nullptr;
	int m_locationX, m_locationY;
public:
	Unit(int locationX, int locationY);
	~Unit();

	bool Init(Graphics *graphics);
	void Draw(Graphics *graphics) const;

	void Move(int locationX, int locationY);
};
