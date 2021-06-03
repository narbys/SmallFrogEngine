#include "MiniginPCH.h"
#include "TransformComponent.h"

frog::TransformComponent::TransformComponent(float x, float y, float z)
	: m_Position{x,y,z}
{
}

void frog::TransformComponent::SetPosition(const float x, const float y, const float z)
{
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = z;
}
