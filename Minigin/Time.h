#pragma once
#include "Singleton.h"

namespace dae
{
	class Time : public Singleton<Time>
	{
	public:
		friend class Singleton<Time>;
		float GetDeltaTime() const;
		void SetDeltaTime(float dt);
	private:
		Time() = default;
		float m_DeltaTime{};
	};
}
