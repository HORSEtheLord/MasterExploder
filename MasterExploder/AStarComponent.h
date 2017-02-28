#pragma once
#include "Component.h"
#include "MovementComponent.h"
#include <functional>
#include <vector>

class AStarComponent : public Component
{
private:
	std::reference_wrapper<PositionComponent> m_positionComponent;
	std::reference_wrapper<MovementComponent> m_movementComponent;
	bool m_active = false;
	std::vector<int> m_path;
public:
	AStarComponent(EntityId entityId, std::reference_wrapper<PositionComponent> positionComponent, std::reference_wrapper<MovementComponent> movementComponent);
	~AStarComponent();

	bool IsActive() const { return m_active; }
	void Activate(int x, int y);
	void Deactivate() { m_active = false; }
	int GetNextPosition();
	bool HasNextPosition() const { return !m_path.empty(); }
	std::reference_wrapper<MovementComponent> GetMovementComponent() const { return m_movementComponent; }
};
