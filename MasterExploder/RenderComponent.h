#pragma once
#include "Component.h"
#include "PositionComponent.h"
#include <functional>

class RenderComponent : public Component
{
private:
	std::reference_wrapper<PositionComponent> m_positionComponent;
	SpriteId m_spriteId;
public:
	RenderComponent(EntityId entityId, std::reference_wrapper<PositionComponent> positionComponent, SpriteId spriteId);
	~RenderComponent();

	//RenderComponent(const RenderComponent&) = delete;

	/*RenderComponent(RenderComponent &&other) noexcept
		: Component(other.GetEntityId()), m_positionComponent(other.m_positionComponent), m_spriteId(other.m_spriteId)
	{
	}

	RenderComponent& operator=(RenderComponent &&other) noexcept
	{
		if (this != &other)
		{
			m_entityId = other.GetEntityId();
			m_positionComponent = other.m_positionComponent;
		}

		return *this;
	}*/

	SpriteId GetSpriteId() const { return m_spriteId; }
	void SetSpriteId(SpriteId spriteId) { m_spriteId = spriteId; }

	int GetX() const { return m_positionComponent.get().GetX(); }
	int GetY() const { return m_positionComponent.get().GetY(); }
};
