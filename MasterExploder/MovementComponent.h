#pragma once
#include "Component.h"
#include "PositionComponent.h"
#include <functional>

class MovementComponent : public Component
{
private:
	std::reference_wrapper<PositionComponent> m_positionComponent;
	unsigned int m_movementSpeed;
	int m_targetX = 0, m_targetY = 0;
	unsigned int m_millisecondsPerMove;
	unsigned int m_timeSinceLastMove = 0;
	bool m_active = false;
public:
	MovementComponent(EntityId entityId, std::reference_wrapper<PositionComponent> positionComponent, unsigned int movementSpeed);
	~MovementComponent();

	int GetTargetX() const { return m_targetX; }
	int GetTargetY() const { return m_targetY; }
	void SetTarget(int x, int y) { m_targetX = x; m_targetY = y; }

	unsigned int GetMillisecondsPerMove() const { return m_millisecondsPerMove; }
	unsigned int GetTimeSinceLastMove() const { return m_timeSinceLastMove; }
	void IncrementTimeSinceLastMove(unsigned int milliseconds) { m_timeSinceLastMove += milliseconds; }
	void DecrementTimeSinceLastMove() { m_timeSinceLastMove -= m_millisecondsPerMove; }
	void SetMovementSpeed(unsigned int movementSpeed)
	{
		m_movementSpeed = movementSpeed;
		m_millisecondsPerMove = DEFAULT_SPEED / m_movementSpeed;
	}

	bool IsActive() const { return m_active; }
	void Activate() { m_active = true; }
	void Deactivate() { m_active = false; }

	int GetX() const { return m_positionComponent.get().GetX(); }
	int GetY() const { return m_positionComponent.get().GetY(); }
	void SetPosition(int x, int y) const { m_positionComponent.get().SetPosition(x, y); }
};
