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

std::shared_ptr<std::vector<bool>> CollisionChecker::GetCollisionMap() const
{
	std::shared_ptr<std::vector<bool>> collisionMap = std::make_shared<std::vector<bool>>(m_width * m_height, false);

	for (auto it = m_gameObjects->cbegin(); it != m_gameObjects->cend(); ++it)
	{
		(*collisionMap)[CALCULATE_KEY((*it)->GetLocationX(), (*it)->GetLocationY())] = true;
	}

	return collisionMap;
}