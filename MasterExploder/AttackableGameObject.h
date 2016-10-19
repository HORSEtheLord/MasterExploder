#pragma once
#include <memory>
#include <string>

#include "Graphics.h"
#include "GameObject.h"

class AttackableGameObject : public GameObject
{
private:

protected:
	unsigned int m_maxHitPoints, m_currentHitPoints;
	bool m_isDead = false;

	AttackableGameObject(const std::wstring &name, int locationX, int locationY, unsigned int maxHitPoints, unsigned int currentHitPoints);

public:
	virtual ~AttackableGameObject() {}

	bool ReceiveDamage(int damage);

	const unsigned int& GetMaxHp() const { return m_maxHitPoints; }
	const unsigned int& GetCurrentHp() const { return m_currentHitPoints; }
};
