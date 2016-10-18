#include "AttackableGameObject.h"

AttackableGameObject::AttackableGameObject(const std::wstring& name, unsigned int maxHitPoints, unsigned int currentHitPoints)
	: GameObject(name),  m_maxHitPoints(maxHitPoints), m_currentHitPoints(currentHitPoints)
{
}

void AttackableGameObject::SetCurrentHp(unsigned int hp)
{
	m_currentHitPoints = hp;
}
