#include "ScoreComponent.h"

#include "Subject.h"

int dae::ScoreComponent::GetScore() const
{
	return m_Score;
}

void dae::ScoreComponent::AddToScore(int scoreToAdd)
{
	m_Score += scoreToAdd;
	m_pSubject->Notify({ Events::SCORE_INCREASE,m_Score });
}

void dae::ScoreComponent::Update()
{
}
