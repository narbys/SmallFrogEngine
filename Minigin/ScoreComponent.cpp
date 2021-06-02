#include "ScoreComponent.h"

#include "Subject.h"

int frog::ScoreComponent::GetScore() const
{
	return m_Score;
}

void frog::ScoreComponent::AddToScore(int scoreToAdd)
{
	m_Score += scoreToAdd;
	m_pSubject->Notify({ Events::SCORE_INCREASE,m_Score });
}

void frog::ScoreComponent::Update()
{
}
