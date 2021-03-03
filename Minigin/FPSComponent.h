#pragma once
#include "BaseComponent.h"
#include "GameObject.h"
namespace dae
{
	class TextComponent;
	class FPSComponent final : public BaseComponent
	{
	public:
		FPSComponent();
		virtual ~FPSComponent();
		int GetFps()const;
		void Update() override;
	private:
		float m_ElapsedSec{};
		int m_Fps{};
		TextComponent* m_pText = nullptr;
	};
}

