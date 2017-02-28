#include "MovementSystem.h"

MovementSystem::MovementSystem(std::vector<MovementComponent> &components)
	: m_components(components)
{
}

MovementSystem::~MovementSystem()
{
}

void MovementSystem::Update()
{
	for (MovementComponent &component : m_components)
	{
		component.IncrementTimeSinceLastMove(MS_PER_UPDATE);
		if (component.GetTimeSinceLastMove() >= component.GetMillisecondsPerMove())
		{
			component.DecrementTimeSinceLastMove();
			if (component.IsActive())
			{
				component.SetPosition(component.GetTargetX(), component.GetTargetY());
				component.Deactivate();
			}
		}
	}
}
