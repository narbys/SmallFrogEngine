#include "LivesComponent.h"

dae::LivesComponent::LivesComponent(int lives)
	: m_Lives(lives)
{
}

dae::LivesComponent::~LivesComponent()
{
}

int dae::LivesComponent::GetLives() const
{
	return m_Lives;
}

void dae::LivesComponent::ReduceLives()
{
	m_Lives--;
	m_pSubject->Notify({ Events::PLAYER_DEATH, m_Lives });
}

void dae::LivesComponent::IncreaseLives()
{
	m_Lives++;
}

void dae::LivesComponent::SetLives(int lifeAmount)
{
	m_Lives = lifeAmount;
}
