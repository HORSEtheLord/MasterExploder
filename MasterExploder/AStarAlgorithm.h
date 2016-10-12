#pragma once

#include <vector>

#include "AStarNode.h"

class AStarAlgorithm
{
private:
	int m_width, m_height;

	std::vector<AStarNode> GetNeighbours(const AStarNode &node) const;
	float GetEstimatedDistance(const AStarNode &from, const AStarNode &to) const;
public:
	AStarAlgorithm(int width, int height);
	~AStarAlgorithm();

	std::vector<AStarNode> FindPath(const AStarNode &start, const AStarNode &goal) const;
};