#include "CollisionChecker.h"
#include "Utils.h"

CollisionChecker::CollisionChecker()
{
}

CollisionChecker::~CollisionChecker()
{
}

bool CollisionChecker::Init(size_t width, size_t height, std::shared_ptr<std::vector<std::shared_ptr<GameObject>>> gameObjects)
{
	GetInstance().m_width = width;
	GetInstance().m_height = height;
	GetInstance().m_gameObjects = gameObjects;
	return true;
}

bool CollisionChecker::CheckAdjacency(int x1, int y1, int x2, int y2)
{
	return (abs(x1 - x2) + abs(y1 - y2)) == 1;
}

std::shared_ptr<std::vector<bool>> CollisionChecker::GetCollisionMap() const
{
	std::shared_ptr<std::vector<bool>> collisionMap = std::make_shared<std::vector<bool>>(m_width * m_height, false);

	for (auto it = m_gameObjects->cbegin(); it != m_gameObjects->cend(); ++it)
	{
		(*collisionMap)[CALCULATE_KEY((*it)->GetLocationX(), (*it)->GetLocationY())] = true;
	}

	return collisionMap;
}