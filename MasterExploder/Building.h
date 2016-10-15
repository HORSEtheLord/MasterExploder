#pragma once
#include <d2d1.h>
#include "Graphics.h"

class Graphics;

class Building
{
private:
	ID2D1Bitmap *m_bmp = nullptr;
	int m_locationX, m_locationY;
	unsigned int m_maxHitPoints, m_currentHitPoints;
	bool m_isDestroyed = false;
public:
	Building(int locationX, int locationY, int hp);
	~Building();

	bool ReceiveDamage(int damage);

	bool Init(Graphics *graphics);
	void Draw(Graphics *graphics) const;
};
