#include "MiniginPCH.h"
#include "Time.h"

float frog::Time::GetDeltaTime() const
{
	return m_DeltaTime;
}

void frog::Time::SetDeltaTime(float dt)
{
	m_DeltaTime = dt;
}
