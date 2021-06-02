#pragma once
#include "BaseComponent.h"

namespace frog
{
	class ScoreComponent : public BaseComponent
	{
	public:
		ScoreComponent() = default;
		int GetScore()const;
		void AddToScore(int scoreToAdd);
		void Update() override;
	private:
		int m_Score{};
	};
}

