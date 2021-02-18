#include "MiniginPCH.h"
#include "Time.h"

float dae::Time::GetDeltaTime() const
{
	return m_DeltaTime;
}

void dae::Time::SetDeltaTime(float dt)
{
	m_DeltaTime = dt;
}
