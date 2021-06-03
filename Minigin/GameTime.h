#pragma once
#include "Singleton.h"

namespace frog
{
	class GameTime : public Singleton<GameTime>
	{
	public:
		friend class Singleton<GameTime>;
		float GetDeltaTime() const;
		void SetDeltaTime(float dt);
	private:
		GameTime() = default;
		float m_DeltaTime{};
	};
}
