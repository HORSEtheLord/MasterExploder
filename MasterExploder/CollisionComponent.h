#pragma once
#include "Component.h"
#include"PositionComponent.h"
#include <functional>

class CollisionComponent : public Component
{
private:
	std::reference_wrapper<PositionComponent> m_positionComponent;
public:
	CollisionComponent(EntityId entityId, std::reference_wrapper<PositionComponent> positionComponent);
	~CollisionComponent();

	int GetX() const { return m_positionComponent.get().GetX(); }
	int GetY() const { return m_positionComponent.get().GetY(); }
};