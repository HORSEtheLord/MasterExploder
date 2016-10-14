#include <algorithm>
#include <cmath>
#include <limits>
#include <memory>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "AStarAlgorithm.h"

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

bool AStarAlgorithm::IsNodeBlocked(int x, int y) const
{
	return m_map[x * m_height + y];
}

std::vector<std::shared_ptr<AStarNode>> AStarAlgorithm::GetNeighbours(const std::shared_ptr<AStarNode> node) const
{
	std::vector<std::shared_ptr<AStarNode>> neighbours;
	if (node->m_x > 0)
	{
		if (!IsNodeBlocked(node->m_x - 1, node->m_y))
			neighbours.push_back(std::make_shared<AStarNode>(AStarNode(node->m_x - 1, node->m_y)));
		/*if (node->m_y > 0)
			neighbours.push_back(AStarNode(node->m_x - 1, node->m_y - 1));
		if (node->m_y < m_height - 1)
			neighbours.push_back(AStarNode(node->m_x - 1, node->m_y + 1));*/
	}

	if (node->m_x < m_width - 1)
	{
		if (!IsNodeBlocked(node->m_x + 1, node->m_y))
			neighbours.push_back(std::make_shared<AStarNode>(AStarNode(node->m_x + 1, node->m_y)));
		/*if (node->m_y > 0)
			neighbours.push_back(AStarNode(node->m_x + 1, node->m_y - 1));
		if (node->m_y < m_height - 1)
			neighbours.push_back(AStarNode(node->m_x + 1, node->m_y + 1));*/
	}

	if (node->m_y > 0)
		if (!IsNodeBlocked(node->m_x, node->m_y - 1))
			neighbours.push_back(std::make_shared<AStarNode>(AStarNode(node->m_x, node->m_y - 1)));
	if (node->m_y < m_height - 1)
		if (!IsNodeBlocked(node->m_x, node->m_y + 1))
			neighbours.push_back(std::make_shared<AStarNode>(AStarNode(node->m_x, node->m_y + 1)));

	return neighbours;
}

float AStarAlgorithm::GetEstimatedDistance(const std::shared_ptr<AStarNode> from, const std::shared_ptr<AStarNode> to) const
{
	int xDistance = to->m_x - from->m_x;
	int yDistance = to->m_y - from->m_y;

	return sqrt(xDistance * xDistance - yDistance * yDistance);
}

std::vector<std::shared_ptr<AStarNode>> AStarAlgorithm::FindPath(const std::shared_ptr<AStarNode> start, const std::shared_ptr<AStarNode> goal) const
{
	int height = m_height;
	auto hasher = [height](const std::shared_ptr<AStarNode> node) { return std::hash<int>()(node->m_x * height + node->m_y); };

	std::unordered_map<std::shared_ptr<AStarNode>, int, decltype(hasher)> fscore(10, hasher);
	std::unordered_map<std::shared_ptr<AStarNode>, int, decltype(hasher)> gscore(10, hasher);
	gscore[start] = 0;
	std::unordered_map<std::shared_ptr<AStarNode>, int, decltype(hasher)> hscore(10, hasher);
	std::unordered_set<std::shared_ptr<AStarNode>, decltype(hasher)> closedSet(10, hasher);

	auto cmp = [&fscore, &hasher](const std::shared_ptr<AStarNode> first, const std::shared_ptr<AStarNode> second)
	{
		if (fscore.find(first) == fscore.cend())
			fscore.insert(std::unordered_map<std::shared_ptr<AStarNode>, int, decltype(hasher)>::value_type(first, std::numeric_limits<int>::max()));

		if (fscore.find(second) == fscore.cend())
			fscore.insert(std::unordered_map<std::shared_ptr<AStarNode>, int, decltype(hasher)>::value_type(second, std::numeric_limits<int>::max()));

		return fscore.at(first) < fscore.at(second);
	};

	std::set<std::shared_ptr<AStarNode>, decltype(cmp)> openSet(cmp);
	openSet.insert(start);

	std::unordered_map<std::shared_ptr<AStarNode>, std::shared_ptr<AStarNode>, decltype(hasher)> cameFrom(10, hasher);

	while (!openSet.empty())
	{
		std::shared_ptr<AStarNode> node = *(openSet.begin());
		if (*node == *goal)
		{
			std::vector<std::shared_ptr<AStarNode>> path{ node };

			auto it = cameFrom.find(node);
			while (it != cameFrom.cend())
			{
				const std::shared_ptr<AStarNode> next = it->second;
				path.push_back(next);
				it = cameFrom.find(next);
			}

			std::reverse(path.begin(), path.end());
			return path;
		}

		openSet.erase(openSet.begin());
		closedSet.insert(node);

		for (const std::shared_ptr<AStarNode> neighbour : GetNeighbours(node))
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
					cameFrom.insert(std::unordered_map<std::shared_ptr<AStarNode>, std::shared_ptr<AStarNode>, decltype(hasher)>::value_type(neighbour, node));
				else
					it->second = node;

				gscore[neighbour] = ngscore;
				fscore[neighbour] = ngscore + hscore[neighbour];
			}
		}
	}

	std::vector<std::shared_ptr<AStarNode>> path;
	return path;
}