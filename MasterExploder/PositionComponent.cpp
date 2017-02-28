#include "PositionComponent.h"

PositionComponent::PositionComponent(EntityId entityId, int x, int y)
	: Component(entityId), m_x(x), m_y(y)
{
}

PositionComponent::~PositionComponent()
{
}