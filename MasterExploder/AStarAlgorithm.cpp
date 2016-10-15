#include <algorithm>
#include <cmath>
#include <limits>
#include <memory>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "AStarAlgorithm.h"
#include "Utils.h"

AStarAlgorithm::AStarAlgorithm(int width, int height, bool *map)
	: m_width(width), m_height(height), m_map(map)
{
}

AStarAlgorithm::~AStarAlgorithm()
{
}

AStarAlgorithm* AStarAlgorithm::m_instance = nullptr;

bool AStarAlgorithm::Init(int width, int height, bool *map)
{
	m_instance = new AStarAlgorithm(width, height, map);
	return true;
}

bool AStarAlgorithm::IsNodeBlocked(int key) const
{
	return m_map[key];
}

std::vector<int> AStarAlgorithm::GetNeighbours(int node) const
{
	std::vector<int> neighbours;
	int x = CALCULATE_X(node);
	int y = CALCULATE_Y(node);
	int key;
	if (x > 0)
	{
		key = CALCULATE_KEY(x - 1, y);
		if (!IsNodeBlocked(key))
			neighbours.push_back(key);
		/*if (node->m_y > 0)
			neighbours.push_back(AStarNode(node->m_x - 1, node->m_y - 1));
		if (node->m_y < m_height - 1)
			neighbours.push_back(AStarNode(node->m_x - 1, node->m_y + 1));*/
	}

	if (x < m_width - 1)
	{
		key = CALCULATE_KEY(x + 1, y);
		if (!IsNodeBlocked(key))
			neighbours.push_back(key);
		/*if (node->m_y > 0)
			neighbours.push_back(AStarNode(node->m_x + 1, node->m_y - 1));
		if (node->m_y < m_height - 1)
			neighbours.push_back(AStarNode(node->m_x + 1, node->m_y + 1));*/
	}

	if (y > 0)
	{
		key = CALCULATE_KEY(x, y - 1);
		if (!IsNodeBlocked(key))
			neighbours.push_back(key);
	}
	if (y < m_height - 1)
	{
		key = CALCULATE_KEY(x, y + 1);
		if (!IsNodeBlocked(key))
			neighbours.push_back(key);
	}

	return neighbours;
}

float AStarAlgorithm::GetEstimatedDistance(int from, int to) const
{
	float estimatedDistance = abs(CALCULATE_X(to) - CALCULATE_X(from)) + abs(CALCULATE_Y(to) - CALCULATE_Y(from));
	estimatedDistance *= 1.0001f;
	return estimatedDistance;
}

std::vector<int> AStarAlgorithm::FindPath(int start, int goal) const
{
	std::unordered_map<int, float> fscore;
	std::unordered_map<int, int> gscore;
	gscore[start] = 0;
	std::unordered_map<int, float> hscore;
	std::unordered_set<int> closedSet;

	/*auto cmp = [&fscore](int first, int second)
	{
		if (fscore.find(first) == fscore.cend())
			fscore.insert(std::unordered_map<int, float>::value_type(first, std::numeric_limits<float>::max()));

		if (fscore.find(second) == fscore.cend())
			fscore.insert(std::unordered_map<int, float>::value_type(second, std::numeric_limits<float>::max()));

		return fscore.at(first) < fscore.at(second);
	};*/

	std::unordered_set<int> openSet;
	//std::set<int, decltype(cmp)> openSet(cmp);
	openSet.insert(start);

	std::unordered_map<int, int> cameFrom;

	while (!openSet.empty())
	{
		int node = *(openSet.cbegin());

		for (auto it = openSet.cbegin(); it != openSet.cend(); ++it)
		{
			if (fscore[*it] < fscore[node])
				node = *it;
		}

		if (node == goal)
		{
			std::vector<int> path{ node };

			auto it = cameFrom.find(node);
			while (it != cameFrom.cend())
			{
				int next = it->second;
				path.push_back(next);
				it = cameFrom.find(next);
			}

			std::reverse(path.begin(), path.end());
			return path;
		}

		openSet.erase(node);
		closedSet.insert(node);

		for (int neighbour : GetNeighbours(node))
		{
			if (closedSet.find(neighbour) != closedSet.cend())
				continue;

			int ngscore = gscore[node] + 1;
			bool isBetter = false;

			if (openSet.find(neighbour) == openSet.cend())
			{
				hscore[neighbour] = GetEstimatedDistance(neighbour, goal);
				/*cameFrom[neighbour] = node;

				gscore[neighbour] = ngscore;
				fscore[neighbour] = ngscore + hscore[neighbour];*/
				openSet.insert(neighbour);
				isBetter = true;
			}
			else if (ngscore < gscore[neighbour])
			{
				isBetter = true;
				/*cameFrom[neighbour] = node;

				gscore[neighbour] = ngscore;
				fscore[neighbour] = ngscore + hscore[neighbour];
				openSet.erase(neighbour);
				openSet.insert(neighbour);*/
			}

			if (isBetter)
			{
				//MKOS: równowa¿ne z cameFrom[neighbour] = node;
				//operator[] wymaga jednak by wartoœæ (AStarNode) mia³a defaultowy konstruktor
				//nie chcê go robiæ u siebie
				/*auto it = cameFrom.find(neighbour);
				if (it == cameFrom.cend())
					cameFrom.insert(std::unordered_map<std::shared_ptr<AStarNode>, std::shared_ptr<AStarNode>, decltype(hasher)>::value_type(neighbour, node));
				else
					it->second = node;*/
				cameFrom[neighbour] = node;

				gscore[neighbour] = ngscore;
				fscore[neighbour] = ngscore + hscore[neighbour];
			}
		}
	}

	std::vector<int> path;
	return path;
}