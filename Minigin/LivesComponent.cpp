#include "LivesComponent.h"

frog::LivesComponent::LivesComponent(int lives)
	: m_Lives(lives)
{
}

frog::LivesComponent::~LivesComponent()
{
}

int frog::LivesComponent::GetLives() const
{
	return m_Lives;
}

void frog::LivesComponent::ReduceLives()
{
	m_Lives--;
	m_pSubject->Notify({ Events::PLAYER_DEATH, m_Lives });
}

void frog::LivesComponent::IncreaseLives()
{
	m_Lives++;
}

void frog::LivesComponent::SetLives(int lifeAmount)
{
	m_Lives = lifeAmount;
}
