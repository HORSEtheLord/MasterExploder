#pragma once

class AStarNode
{
	friend class AStarAlgorithm;
private:
	int m_x, m_y;
public:
	static int CopyConstructorInvocationCount;

	AStarNode(int x, int y);
	//AStarNode(const AStarNode& other) = delete;
	AStarNode(const AStarNode& other);

	bool operator==(const AStarNode &other) const
	{
		return m_x == other.m_x && m_y == other.m_y;
	}

	int GetX() const { return m_x; }
	int GetY() const { return m_y; }
};
