#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "AStarAlgorithm.h"
#include "Utils.h"
#include "CollisionChecker.h"

AStarAlgorithm::AStarAlgorithm()
	: m_collisionSystem(nullptr)
{
}

AStarAlgorithm::~AStarAlgorithm()
{
}

bool AStarAlgorithm::Init(size_t width, size_t height, CollisionSystem *collisionSystem)
{
	GetInstance().m_width = width;
	GetInstance().m_height = height;
	GetInstance().m_collisionSystem = collisionSystem;
	return true;
}

bool AStarAlgorithm::IsNodeBlocked(int node) const
{
	int x = CALCULATE_X(node);
	int y = CALCULATE_Y(node);
	return IsNodeBlocked(x, y);
}

bool AStarAlgorithm::IsNodeBlocked(int x, int y) const
{
	return m_collisionSystem->Collide(x, y);
}

std::vector<int> AStarAlgorithm::GetNeighbours(int node) const
{
	std::vector<int> neighbours;
	int x = CALCULATE_X(node);
	int y = CALCULATE_Y(node);
	int key;

	if (x > 0)
	{
		if (!IsNodeBlocked(x - 1, y))
		{
			key = CALCULATE_KEY(x - 1, y);
			neighbours.push_back(key);
		}
	}

	if (x + 1 < m_width)
	{
		if (!IsNodeBlocked(x + 1, y))
		{
			key = CALCULATE_KEY(x + 1, y);
			neighbours.push_back(key);
		}
	}

	if (y > 0)
	{
		if (!IsNodeBlocked(x, y - 1))
		{
			key = CALCULATE_KEY(x, y - 1);
			neighbours.push_back(key);
		}
	}

	if (y + 1 < m_height)
	{
		if (!IsNodeBlocked(x, y + 1))
		{
			key = CALCULATE_KEY(x, y + 1);
			neighbours.push_back(key);
		}
	}

	return neighbours;
}

float AStarAlgorithm::GetEstimatedDistance(int from, int to) const
{
	float estimatedDistance = abs(CALCULATE_X(to) - CALCULATE_X(from)) + abs(CALCULATE_Y(to) - CALCULATE_Y(from));
	estimatedDistance *= 1.0001f;
	return estimatedDistance;
}

std::vector<int> AStarAlgorithm::FindPath(int start, int goal, bool includeGoalInPath) const
{
	std::unordered_set<int> goalNodes;

	if (includeGoalInPath)
	{
		if (IsNodeBlocked(goal))
		{
			std::vector<int> path;
			return path;
		}

		goalNodes.insert(goal);
	}
	else
	{
		for (int neighbour : GetNeighbours(goal))
		{
			goalNodes.insert(neighbour);
		}
	}

	if (goalNodes.empty())
	{
		std::vector<int> path;
		return path;
	}

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

		if (goalNodes.find(node) != goalNodes.cend())
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
				//MKOS: r�wnowa�ne z cameFrom[neighbour] = node;
				//operator[] wymaga jednak by warto�� (AStarNode) mia�a defaultowy konstruktor
				//nie chc� go robi� u siebie
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