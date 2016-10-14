#pragma once

#include <memory>
#include <vector>

#include "AStarNode.h"

class AStarAlgorithm
{
private:
	static AStarAlgorithm *m_instance;

	int m_width, m_height;
	bool *m_map = nullptr;

	bool IsNodeBlocked(int x, int y) const;
	std::vector<std::shared_ptr<AStarNode>> GetNeighbours(const std::shared_ptr<AStarNode> node) const;
	float GetEstimatedDistance(const std::shared_ptr<AStarNode> from, const std::shared_ptr<AStarNode> to) const;

	AStarAlgorithm(int width, int height, bool *map);
public:
	~AStarAlgorithm();

	static bool Init(int width, int height, bool *map);
	static AStarAlgorithm* GetInstance() { return m_instance; }

	std::vector<std::shared_ptr<AStarNode>> FindPath(const std::shared_ptr<AStarNode> start, const std::shared_ptr<AStarNode> goal) const;
};