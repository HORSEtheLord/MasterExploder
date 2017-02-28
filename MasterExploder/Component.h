#pragma once
#include "Utils.h"

class Component
{
protected:
	EntityId m_entityId;
	Component(EntityId entityId);
public:
	virtual ~Component();

	bool operator<(const Component &other) const { return m_entityId < other.m_entityId; }
	bool operator<(EntityId entityId) const { return m_entityId < entityId; }

	EntityId GetEntityId() const { return m_entityId; }
};
