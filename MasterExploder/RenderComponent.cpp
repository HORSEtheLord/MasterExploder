#include "RenderComponent.h"

RenderComponent::RenderComponent(EntityId entityId, std::reference_wrapper<PositionComponent> positionComponent, SpriteId spriteId)
	: Component(entityId), m_positionComponent(positionComponent), m_spriteId(spriteId)
{
}

RenderComponent::~RenderComponent()
{
}