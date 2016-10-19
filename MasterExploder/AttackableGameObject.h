#pragma once
#include <memory>
#include <string>

#include "Graphics.h"
#include "GameObject.h"

class AttackableGameObject : public GameObject
{
private:
	unsigned int m_maxHitPoints, m_currentHitPoints;

protected:
	AttackableGameObject(const std::wstring &name, int locationX, int locationY, unsigned int maxHitPoints, unsigned int currentHitPoints);

public:
	virtual ~AttackableGameObject() {}

	virtual bool ReceiveDamage(int damage) = 0;

	const unsigned int& GetMaxHp() const { return m_maxHitPoints; }
	const unsigned int& GetCurrentHp() const { return m_currentHitPoints; }

	void SetCurrentHp(unsigned int hp);
};
