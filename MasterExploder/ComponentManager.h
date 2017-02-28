#pragma once
#include <algorithm>
#include <vector>
#include "MovementComponent.h"

template <class TComponent>
class ComponentManager
{
private:
	std::vector<TComponent> m_components;
public:
	ComponentManager();
	~ComponentManager();

	std::vector<TComponent>& GetComponentsCollection() { return m_components; }
	template <class... Args>
	void Insert(EntityId entityId, Args&&... args);

	std::reference_wrapper<TComponent> GetComponent(EntityId entityId);
};

template <class TComponent>
ComponentManager<TComponent>::ComponentManager()
{
	m_components.reserve(1000);
}

template <class TComponent>
ComponentManager<TComponent>::~ComponentManager()
{
}

template <class TComponent>
template <class ... Args>
void ComponentManager<TComponent>::Insert(EntityId entityId, Args&&... args)
{
	//m_components.emplace_back(entityId, std::forward<Args>(args)...);
	auto it = std::upper_bound(m_components.begin(), m_components.end(), entityId,
		[](EntityId eId, const TComponent& comp) { return eId < comp.GetEntityId(); });

	m_components.emplace(it, entityId, std::forward<Args>(args)...);
}

template <class TComponent>
std::reference_wrapper<TComponent> ComponentManager<TComponent>::GetComponent(EntityId entityId)
{
	auto it = std::lower_bound(
		m_components.begin(),
		m_components.end(),
		entityId);
	return std::ref(*it);
}