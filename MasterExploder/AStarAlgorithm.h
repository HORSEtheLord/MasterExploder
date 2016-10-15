#pragma once

#include <memory>
#include <vector>

class AStarAlgorithm
{
private:
	static std::shared_ptr<AStarAlgorithm> m_instance;

	int m_width, m_height;
	bool *m_map = nullptr;

	bool IsNodeBlocked(int key) const;
	std::vector<int> GetNeighbours(int node) const;
	float GetEstimatedDistance(int from, int to) const;

public:
	//MKOS: TODO private
	AStarAlgorithm(int width, int height, bool *map);
	AStarAlgorithm(const AStarAlgorithm &other) = delete;
	~AStarAlgorithm();

	static bool Init(int width, int height, bool *map);
	static std::shared_ptr<AStarAlgorithm> GetInstance() { return m_instance; }

	std::vector<int> FindPath(int start, int goal) const;
};