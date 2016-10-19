#pragma once
#include <d2d1.h>
#include <memory>

#include "GameObject.h"
#include "Graphics.h"
#include "AttackableGameObject.h"

class Building : public AttackableGameObject
{
private:
	bool m_isDestroyed = false;

	ID2D1Bitmap *m_bmp = nullptr;
	ID2D1Bitmap *m_bmpDestroyed = nullptr;
public:
	Building(int locationX, int locationY, unsigned int hp);
	Building(const Building &other) = delete;
	virtual ~Building();

	void operator=(const Building &other) = delete;

	bool ReceiveDamage(int damage) override;

	bool Init(std::shared_ptr<Graphics> graphics) override;
	void Update() override;
	void Draw(std::shared_ptr<Graphics> graphics) const override;
};
