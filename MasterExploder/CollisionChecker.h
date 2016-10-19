#pragma once
#include <memory>
#include <vector>

#include "GameObject.h"

class CollisionChecker
{
private:
	size_t m_width = 0, m_height = 0;
	std::shared_ptr<std::vector<std::shared_ptr<GameObject>>> m_gameObjects;
	std::vector<std::shared_ptr<GameObject>> m_gameObjectsMap;

	CollisionChecker();
public:
	CollisionChecker(const CollisionChecker&) = delete;
	~CollisionChecker();

	void operator=(const CollisionChecker&) = delete;

	static bool Init(size_t width, size_t height, std::shared_ptr<std::vector<std::shared_ptr<GameObject>>> gameObjects);
	static CollisionChecker& GetInstance()
	{
		static CollisionChecker instance;
		return instance;
	}

	static bool CheckAdjacency(int x1, int y1, int x2, int y2);

	void Update();

	void Unload();

	bool IsNodeOccupied(int locationX, int locationY) const;
	bool IsNodeOccupied(int node) const;
	std::shared_ptr<GameObject> At(int locationX, int locationY) const;
};
