#pragma once

#include <d2d1.h>
#include <memory>
#include <wincodec.h>

#include "Graphics.h"
#include "AttackableGameObject.h"
#include "Unit.h"
#include "CollisionChecker.h"

class EnemyUnit : public AttackableGameObject
{
private:
	ID2D1Bitmap *m_bmp = nullptr;
	ID2D1Bitmap *m_bmpDead = nullptr;

	int m_damage;
	unsigned int m_attackSpeed;
	unsigned int m_millisecondsPerAttack;
	unsigned int m_timeSinceLastAttack = 0;
	std::shared_ptr<AttackableGameObject> m_attackTarget = nullptr;
public:
	EnemyUnit(int locationX, int locationY, int damage, unsigned int hp, unsigned int attackSpeed = 1);
	EnemyUnit(const EnemyUnit &other) = delete;
	virtual ~EnemyUnit();

	void operator=(const EnemyUnit &other) = delete;

	bool Init(std::shared_ptr<Graphics> graphics) override;
	void Update() override;
	void Draw(std::shared_ptr<Graphics> graphics) const override;

	void Attack(std::shared_ptr<AttackableGameObject> attackTarget);
};
