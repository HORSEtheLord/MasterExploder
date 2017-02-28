#include "CollisionComponent.h"

CollisionComponent::CollisionComponent(EntityId entityId, std::reference_wrapper<PositionComponent> positionComponent)
	: Component(entityId), m_positionComponent(positionComponent)
{
}

CollisionComponent::~CollisionComponent()
{
}