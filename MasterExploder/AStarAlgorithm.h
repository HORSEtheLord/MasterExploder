#pragma once

#include <vector>

#include "AStarNode.h"

class AStarAlgorithm
{
private:
	static AStarAlgorithm *m_instance;

	int m_width, m_height;
	bool *m_map = nullptr;

	bool IsNodeBlocked(int x, int y) const;
	std::vector<AStarNode> GetNeighbours(const AStarNode &node) const;
	float GetEstimatedDistance(const AStarNode &from, const AStarNode &to) const;

	AStarAlgorithm(int width, int height, bool *map);
public:
	~AStarAlgorithm();

	static bool Init(int width, int height, bool *map);
	static AStarAlgorithm* GetInstance() { return m_instance; }

	std::vector<AStarNode> FindPath(const AStarNode &start, const AStarNode &goal) const;
};