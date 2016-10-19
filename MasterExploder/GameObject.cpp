#include "GameObject.h"

GameObject::GameObject(const std::wstring& name, int locationX, int locationY)
	:  m_name(name), m_locationX(locationX), m_locationY(locationY)
{
}