#pragma once
#include "BaseComponent.h"
#include "GameObject.h"
#include "TextComponent.h"
namespace dae
{
	class FPSComponent final : public BaseComponent
	{
	public:
		FPSComponent();
		~FPSComponent();
		int GetFps()const;
		void Update() override;
	private:
		float m_ElapsedSec{};
		int m_Fps{};
		TextComponent* m_pText = nullptr;
	};
}

