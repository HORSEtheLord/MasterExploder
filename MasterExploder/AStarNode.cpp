#include "AStarNode.h"

int AStarNode::CopyConstructorInvocationCount = 0;

AStarNode::AStarNode(int x, int y)
	: m_x(x), m_y(y)
{
}

AStarNode::AStarNode(const AStarNode& other)
	: m_x(other.m_x), m_y(other.m_y)
{
	++CopyConstructorInvocationCount;
}