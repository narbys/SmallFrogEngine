#include "MiniginPCH.h"
#include "GameTime.h"

float frog::GameTime::GetDeltaTime() const
{
	return m_DeltaTime;
}

void frog::GameTime::SetDeltaTime(float dt)
{
	m_DeltaTime = dt;
}
