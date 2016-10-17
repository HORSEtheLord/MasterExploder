#pragma once
#include <d2d1.h>
#include <memory>

#include "Graphics.h"

class Building
{
private:
	int m_locationX, m_locationY;
	unsigned int m_maxHitPoints, m_currentHitPoints;
	bool m_isDestroyed = false;

	ID2D1Bitmap *m_bmp = nullptr;
	ID2D1Bitmap *m_bmpDestroyed = nullptr;
public:
	Building(int locationX, int locationY, int hp);
	Building(const Building &other) = delete;
	~Building();

	void operator=(const Building &other) = delete;

	bool ReceiveDamage(int damage);

	bool Init(std::shared_ptr<Graphics> graphics);
	void Draw(std::shared_ptr<Graphics> graphics) const;

	int GetLocationX() const { return m_locationX; }
	int GetLocationY() const { return m_locationY; }
};
