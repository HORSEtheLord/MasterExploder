#pragma once

#include <memory>
#include <vector>

class AStarAlgorithm
{
private:
	static AStarAlgorithm *m_instance;

	int m_width, m_height;
	bool *m_map = nullptr;

	bool IsNodeBlocked(int key) const;
	std::vector<int> GetNeighbours(int node) const;
	float GetEstimatedDistance(int from, int to) const;

	AStarAlgorithm(int width, int height, bool *map);
public:
	~AStarAlgorithm();

	static bool Init(int width, int height, bool *map);
	static AStarAlgorithm* GetInstance() { return m_instance; }

	std::vector<int> FindPath(int start, int goal) const;
};