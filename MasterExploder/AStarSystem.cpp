#include "AStarSystem.h"

AStarSystem::AStarSystem(std::vector<AStarComponent>& components)
	: m_components(components)
{
}

AStarSystem::~AStarSystem()
{
}

void AStarSystem::Update()
{
	for (AStarComponent &component : m_components)
	{
		if (component.IsActive())
		{
			std::reference_wrapper<MovementComponent> movementComponent = component.GetMovementComponent();
			if (!movementComponent.get().IsActive())
			{
				if (component.HasNextPosition())
				{
					int nextPosition = component.GetNextPosition();
					movementComponent.get().SetTarget(CALCULATE_X(nextPosition), CALCULATE_Y(nextPosition));
					movementComponent.get().Activate();
				}
				else
				{
					component.Deactivate();
				}
			}
		}
	}
}