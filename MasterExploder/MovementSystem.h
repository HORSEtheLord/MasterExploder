#pragma once
#include "ISystem.h"
#include <vector>
#include "MovementComponent.h"

class MovementSystem : public ISystem
{
private:
	std::vector<MovementComponent> &m_components;
public:
	MovementSystem(std::vector<MovementComponent> &components);
	virtual ~MovementSystem();

	void Update() override;
};
