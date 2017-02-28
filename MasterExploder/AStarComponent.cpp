#include "AStarComponent.h"
#include "AStarAlgorithm.h"

AStarComponent::AStarComponent(EntityId entityId, std::reference_wrapper<PositionComponent> positionComponent, std::reference_wrapper<MovementComponent> movementComponent)
	: Component(entityId), m_positionComponent(positionComponent), m_movementComponent(movementComponent)
{
}

AStarComponent::~AStarComponent()
{
}

void AStarComponent::Activate(int x, int y)
{
	m_active = true;
	std::vector<int> path = AStarAlgorithm::GetInstance().FindPath(
		CALCULATE_KEY(m_positionComponent.get().GetX(), m_positionComponent.get().GetY()),
		CALCULATE_KEY(x, y));

	if (!path.empty())
		m_path = path;
}

int AStarComponent::GetNextPosition()
{
	int node = *m_path.begin();
	m_path.erase(m_path.begin());
	return node;
}