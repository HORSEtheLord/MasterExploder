#pragma once
#include "ISystem.h"
#include <vector>
#include "AStarComponent.h"

class AStarSystem : public ISystem
{
private:
	std::vector<AStarComponent> &m_components;
public:
	AStarSystem(std::vector<AStarComponent> &components);
	virtual ~AStarSystem();

	void Update() override;
};