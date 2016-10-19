#include "AttackableGameObject.h"

AttackableGameObject::AttackableGameObject(const std::wstring& name, int locationX, int locationY, unsigned int maxHitPoints, unsigned int currentHitPoints)
	: GameObject(name, locationX, locationY),  m_maxHitPoints(maxHitPoints), m_currentHitPoints(currentHitPoints)
{
}

void AttackableGameObject::SetCurrentHp(unsigned int hp)
{
	m_currentHitPoints = hp;
}
