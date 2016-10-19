#pragma once

#include <memory>
#include <vector>

class AStarAlgorithm
{
private:
	size_t m_width = 0, m_height = 0;

	static bool IsNodeBlocked(int node);
	std::vector<int> GetNeighbours(int node) const;
	float GetEstimatedDistance(int from, int to) const;
	AStarAlgorithm();
public:
	AStarAlgorithm(const AStarAlgorithm&) = delete;
	~AStarAlgorithm();

	void operator=(const AStarAlgorithm&) = delete;

	static bool Init(size_t width, size_t height);
	static AStarAlgorithm& GetInstance()
	{ 
		static AStarAlgorithm instance;
		return instance; 
	}

	std::vector<int> FindPath(int start, int goal, bool includeGoalInPath = true) const;
};