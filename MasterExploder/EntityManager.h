#pragma once
#include "ComponentManager.h"
#include "RenderComponent.h"
#include "AStarComponent.h"
#include "CollisionComponent.h"

class EntityManager
{
private:
	static EntityId m_nextFreeId;
public:
	ComponentManager<PositionComponent> m_positionComponents;
	ComponentManager<MovementComponent> m_movementComponents;
	ComponentManager<RenderComponent> m_renderComponents;
	ComponentManager<AStarComponent> m_aStarComponents;
	ComponentManager<CollisionComponent> m_collisionComponents;

	static EntityId GenerateEntityId()
	{
		return m_nextFreeId++;
	}
};
