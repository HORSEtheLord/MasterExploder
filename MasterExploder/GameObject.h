#pragma once
#include <memory>
#include <string>

#include "Graphics.h"

class GameObject
{
private:
	std::wstring m_name;

protected:
	GameObject(const std::wstring &name);

public:
	virtual ~GameObject() {}

	virtual bool Init(std::shared_ptr<Graphics> graphics) = 0;
	virtual void Update() = 0;
	virtual void Draw(std::shared_ptr<Graphics> graphics) const = 0;

	const std::wstring& GetName() const { return m_name; }
};
