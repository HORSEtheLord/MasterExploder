#include "CollisionSystem.h"

CollisionSystem::CollisionSystem(std::vector<CollisionComponent>& components)
	: m_components(components)
{
}

CollisionSystem::~CollisionSystem()
{
}

bool CollisionSystem::Collide(int x, int y) const
{
	for(CollisionComponent &component : m_components)
	{
		if (component.GetX() == x && component.GetY() == y)
			return true;
	}

	return false;
}
