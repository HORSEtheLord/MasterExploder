#pragma once
#include <memory>
#include <vector>

#include "GameObject.h"

class CollisionChecker
{
private:
	size_t m_width = 0, m_height = 0;
	std::shared_ptr<std::vector<std::shared_ptr<GameObject>>> m_gameObjects;

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

	std::shared_ptr<std::vector<bool>> GetCollisionMap() const;
};
