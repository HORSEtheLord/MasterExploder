#pragma once

#include <d2d1.h>
#include <memory>

#include "AStarAlgorithm.h"
#include "Building.h"
#include "Graphics.h"
#include "EnemyUnit.h"

class Unit : public GameObject
{
private:
	ID2D1Bitmap *m_bmp = nullptr;
	int m_locationX, m_locationY;
	std::vector<int> m_path;

	int m_damage;
	//zuka:
	//max speed is one tile per tick (MAX_MOVEMENT_SPEED = (1000 / MS_PER_UPDATE) tiles/sec),
	//default movement speed is 1 tile per second
	unsigned int m_movementSpeed, m_attackSpeed;
	unsigned int m_millisecondsPerMove, m_millisecondsPerAttack;
	unsigned int m_timeSinceLastMove = 0, m_timeSinceLastAttack = 0;
	/*std::shared_ptr<Building> m_attackTarget = nullptr;*/
	std::shared_ptr<EnemyUnit> m_attackTarget = nullptr;
public:
	Unit(int locationX, int locationY, int damage, unsigned int movementSpeed = 1, unsigned int attackSpeed = 1);
	Unit(const Unit &other) = delete;
	virtual ~Unit();

	void operator = (const Unit&) = delete;

	bool Init(std::shared_ptr<Graphics> graphics) override;
	void Update() override;
	void Draw(std::shared_ptr<Graphics> graphics) const override;

	void Move(int locationX, int locationY);
	/*void Attack(std::shared_ptr<Building> attackTarget);*/
	void Attack(std::shared_ptr<EnemyUnit> attackTarget);
};
