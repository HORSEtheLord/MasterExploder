#pragma once

#include <d2d1.h>
#include <memory>
#include <wincodec.h>

#include "AStarAlgorithm.h"
#include "Graphics.h"

class Unit
{
private:
	ID2D1Bitmap *m_bmp = nullptr;
	int m_locationX, m_locationY;
	std::vector<int> m_path;
	int m_timeSinceLastMove = 0;

	int m_damage;
	//zuka:
	//max speed is one tile per tick (MAX_MOVEMENT_SPEED = 20 tiles/sec),
	//default movement speed is 1 tile per second
	unsigned int m_movementSpeed;
public:
	Unit(int locationX, int locationY, int damage, unsigned int movementSpeed);
	Unit(int locationX, int locationY, int damage);
	Unit(const Unit &other) = delete;
	~Unit();

	bool Init(std::shared_ptr<Graphics> graphics);
	void Update();
	void Draw(std::shared_ptr<Graphics> graphics) const;

	void Move(int locationX, int locationY);
	void Attack(int locationX, int locationY);
};
