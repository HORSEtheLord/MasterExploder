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

	GetInstance().m_gameObjectsMap = std::vector<std::shared_ptr<GameObject>>(width * height, nullptr);

	return true;
}

bool CollisionChecker::CheckAdjacency(int x1, int y1, int x2, int y2)
{
	return (abs(x1 - x2) + abs(y1 - y2)) == 1;
}

void CollisionChecker::Update()
{
	fill(m_gameObjectsMap.begin(), m_gameObjectsMap.end(), nullptr);
	for (auto it = m_gameObjects->cbegin(); it != m_gameObjects->cend(); ++it)
	{
		m_gameObjectsMap[CALCULATE_KEY((*it)->GetLocationX(), (*it)->GetLocationY())] = *it;
	}
}

void CollisionChecker::Unload()
{
	m_gameObjectsMap.clear();
}

bool CollisionChecker::IsNodeOccupied(int locationX, int locationY) const
{
	return IsNodeOccupied(CALCULATE_KEY(locationX, locationY));
}

bool CollisionChecker::IsNodeOccupied(int node) const
{
	return m_gameObjectsMap.at(node) != nullptr;
}

std::shared_ptr<GameObject> CollisionChecker::At(int locationX, int locationY) const
{
	return m_gameObjectsMap.at(CALCULATE_KEY(locationX, locationY));
}