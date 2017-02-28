#pragma once

#include <memory>
#include <vector>
#include "CollisionSystem.h"

class AStarAlgorithm
{
private:
	size_t m_width = 0, m_height = 0;
	CollisionSystem *m_collisionSystem;

	bool IsNodeBlocked(int node) const;
	bool IsNodeBlocked(int x, int y) const;
	std::vector<int> GetNeighbours(int node) const;
	float GetEstimatedDistance(int from, int to) const;
	AStarAlgorithm();
public:
	AStarAlgorithm(const AStarAlgorithm&) = delete;
	~AStarAlgorithm();

	void operator=(const AStarAlgorithm&) = delete;

	static bool Init(size_t width, size_t height, CollisionSystem *collisionSystem);
	static AStarAlgorithm& GetInstance()
	{ 
		static AStarAlgorithm instance;
		return instance; 
	}

	std::vector<int> FindPath(int start, int goal, bool includeGoalInPath = true) const;
};
