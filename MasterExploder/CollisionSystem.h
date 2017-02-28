#pragma once
#include <vector>
#include "CollisionComponent.h"

class CollisionSystem
{
private:
	std::vector<CollisionComponent> &m_components;
public:
	CollisionSystem(std::vector<CollisionComponent> &components);
	virtual ~CollisionSystem();

	bool Collide(int x, int y) const;
};