#pragma once
#include "Singleton.h"

namespace dae
{
	class Time : public Singleton<Time>
	{
	public:
		float GetDeltaTime() const;
		void SetDeltaTime(float dt);
	private:
		float m_DeltaTime{};
	};
}
