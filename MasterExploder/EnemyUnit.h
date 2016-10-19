#pragma once

#include <d2d1.h>
#include <memory>
#include <wincodec.h>

#include "Building.h"
#include "Graphics.h"
#include "AttackableGameObject.h"

class EnemyUnit : public AttackableGameObject
{
private:
	bool m_isDead = false;

	ID2D1Bitmap *m_bmp = nullptr;
	ID2D1Bitmap *m_bmpDead = nullptr;
public:
	EnemyUnit(int locationX, int locationY, unsigned int hp);
	EnemyUnit(const EnemyUnit &other) = delete;
	virtual ~EnemyUnit();

	void operator=(const EnemyUnit &other) = delete;

	bool ReceiveDamage(int damage) override;

	bool Init(std::shared_ptr<Graphics> graphics) override;
	void Update() override;
	void Draw(std::shared_ptr<Graphics> graphics) const override;
};