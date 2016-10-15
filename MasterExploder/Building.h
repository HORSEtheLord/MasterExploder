#pragma once
#include <d2d1.h>
#include <memory>

#include "Graphics.h"

class Building
{
private:
	ID2D1Bitmap *m_bmp = nullptr;
	int m_locationX, m_locationY;
	unsigned int m_maxHitPoints, m_currentHitPoints;
	bool m_isDestroyed = false;
public:
	Building(int locationX, int locationY, int hp);
	Building(const Building &other) = delete;
	~Building();

	bool ReceiveDamage(int damage);

	bool Init(std::shared_ptr<Graphics> graphics);
	void Draw(std::shared_ptr<Graphics> graphics) const;

	int GetLocationX() const { return m_locationX; }
	int GetLocationY() const { return m_locationY; }
};
