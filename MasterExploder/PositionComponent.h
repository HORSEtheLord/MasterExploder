#pragma once
#include "Component.h"

class PositionComponent : public Component
{
private:
	int m_x, m_y;
public:
	PositionComponent(EntityId entityId, int x, int y);
	~PositionComponent();

	int GetX() const { return m_x; }
	int GetY() const { return m_y; }

	void SetPosition(int x, int y) { m_x = x; m_y = y; }
};
