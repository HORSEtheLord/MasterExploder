#include "AttackableGameObject.h"

AttackableGameObject::AttackableGameObject(const std::wstring& name, int locationX, int locationY, unsigned int maxHitPoints, unsigned int currentHitPoints)
	: GameObject(name, locationX, locationY),  m_maxHitPoints(maxHitPoints), m_currentHitPoints(currentHitPoints)
{
}

bool AttackableGameObject::ReceiveDamage(int damage)
{
	if (damage >= GetCurrentHp())
	{
		m_currentHitPoints = 0;
		m_isDead = true;
	}
	else
	{
		m_currentHitPoints -= damage;
	}

	return m_isDead;
}