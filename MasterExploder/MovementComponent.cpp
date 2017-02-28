#include "MovementComponent.h"
#include <functional>

MovementComponent::MovementComponent(EntityId entityId, std::reference_wrapper<PositionComponent> positionComponent, unsigned int movementSpeed)
	: Component(entityId), m_positionComponent(positionComponent), m_movementSpeed(movementSpeed)
{
	m_millisecondsPerMove = DEFAULT_SPEED / m_movementSpeed;
}

MovementComponent::~MovementComponent()
{
}