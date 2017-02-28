#pragma once
#include <vector>
#include "RenderComponent.h"
#include "Graphics.h"

class RenderSystem
{
private:
	const std::vector<RenderComponent> &m_components;
public:
	RenderSystem(const std::vector<RenderComponent> &components);
	virtual ~RenderSystem();

	virtual void Draw(const Graphics &graphics) const;
};
