#include <algorithm>
#include <cmath>
#include <limits>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "AStarAlgorithm.h"

AStarAlgorithm::AStarAlgorithm(int width, int height)
	: m_width(width), m_height(height)
{
}

AStarAlgorithm::~AStarAlgorithm()
{
}

std::vector<AStarNode> AStarAlgorithm::GetNeighbours(const AStarNode &node) const
{
	std::vector<AStarNode> neighbours;
	if (node.m_x > 0)
	{
		neighbours.push_back(AStarNode(node.m_x - 1, node.m_y));
		/*if (node.m_y > 0)
			neighbours.push_back(AStarNode(node.m_x - 1, node.m_y - 1));
		if (node.m_y < m_height - 1)
			neighbours.push_back(AStarNode(node.m_x - 1, node.m_y + 1));*/
	}

	if (node.m_x < m_width - 1)
	{
		neighbours.push_back(AStarNode(node.m_x + 1, node.m_y));
		/*if (node.m_y > 0)
			neighbours.push_back(AStarNode(node.m_x + 1, node.m_y - 1));
		if (node.m_y < m_height - 1)
			neighbours.push_back(AStarNode(node.m_x + 1, node.m_y + 1));*/
	}

	if (node.m_y > 0)
		neighbours.push_back(AStarNode(node.m_x, node.m_y - 1));
	if (node.m_y < m_height - 1)
		neighbours.push_back(AStarNode(node.m_x, node.m_y + 1));

	return neighbours;
}

float AStarAlgorithm::GetEstimatedDistance(const AStarNode &from, const AStarNode &to) const
{
	int xDistance = to.m_x - from.m_x;
	int yDistance = to.m_y - from.m_y;

	return sqrt(xDistance * xDistance - yDistance * yDistance);
}

std::vector<AStarNode> AStarAlgorithm::FindPath(const AStarNode &start, const AStarNode &goal) const
{
	int width = m_width;
	auto hasher = [width](const AStarNode &node) { return std::hash<int>()(node.m_x * width + node.m_y); };

	std::unordered_map<AStarNode, int, decltype(hasher)> fscore(10, hasher);
	std::unordered_map<AStarNode, int, decltype(hasher)> gscore(10, hasher);
	gscore[start] = 0;
	std::unordered_map<AStarNode, int, decltype(hasher)> hscore(10, hasher);
	std::unordered_set<AStarNode, decltype(hasher)> closedSet(10, hasher);

	auto cmp = [&fscore, &hasher](const AStarNode &first, const AStarNode &second)
	{
		if (fscore.find(first) == fscore.cend())
			fscore.insert(std::unordered_map<AStarNode, int, decltype(hasher)>::value_type(first, std::numeric_limits<int>::max()));

		if (fscore.find(second) == fscore.cend())
			fscore.insert(std::unordered_map<AStarNode, int, decltype(hasher)>::value_type(second, std::numeric_limits<int>::max()));

		return fscore.at(first) < fscore.at(second);
	};

	std::set<AStarNode, decltype(cmp)> openSet(cmp);
	openSet.insert(start);

	std::unordered_map<AStarNode, AStarNode, decltype(hasher)> cameFrom(10, hasher);

	while (!openSet.empty())
	{
		AStarNode node = *(openSet.begin());
		if (node == goal)
		{
			std::vector<AStarNode> path{ node };

			auto it = cameFrom.find(node);
			while (it != cameFrom.cend())
			{
				const AStarNode &next = it->second;
				path.push_back(next);
				it = cameFrom.find(next);
			}

			std::reverse(path.begin(), path.end());
			return path;
		}

		openSet.erase(openSet.begin());
		closedSet.insert(node);

		for (const AStarNode &neighbour : GetNeighbours(node))
		{
			if (closedSet.find(neighbour) != closedSet.cend())
				continue;

			int ngscore = gscore[node] + 1;
			bool isBetter = false;

			if (openSet.find(neighbour) == openSet.cend())
			{
				openSet.insert(neighbour);
				hscore[neighbour] = GetEstimatedDistance(neighbour, goal);
				isBetter = true;
			}
			else if (ngscore < gscore[neighbour])
				isBetter = true;

			if (isBetter)
			{
				//MKOS: równowa¿ne z cameFrom[neighbour] = node;
				//operator[] wymaga jednak by wartoœæ (AStarNode) mia³a defaultowy konstruktor
				//nie chcê go robiæ u siebie
				auto it = cameFrom.find(neighbour);
				if (it == cameFrom.cend())
					cameFrom.insert(std::unordered_map<AStarNode, AStarNode, decltype(hasher)>::value_type(neighbour, node));
				else
					it->second = node;

				gscore[neighbour] = ngscore;
				fscore[neighbour] = ngscore + hscore[neighbour];
			}
		}
	}

	std::vector<AStarNode> path;
	return path;
}