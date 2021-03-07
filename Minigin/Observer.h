#pragma once
#include "Event.h"
#include "TextComponent.h"
#include "Renderer.h"
namespace dae
{
	class TextComponent;
	class GameObject;

	class Observer
	{
	public:
		virtual ~Observer() = default;
		virtual void OnNotify(const Event& event)=0;
	};

	class Display : public Observer
	{
	public:
		Display(TextComponent* textDisplay) : m_pDisplay(textDisplay) {}
		void OnNotify(const Event& event) override
		{
			if(!m_pDisplay)
			{
				Renderer::GetInstance().LogDebugText("No display connected to Display observer class!\n",{1,0,0,1});
			}
			if (event.event == Events::PLAYER_DEATH)
			{
				auto tuple = event.GetData<int>();
				const int lives = std::get<0>(tuple);
				m_pDisplay->SetText("Lives: "+std::to_string(lives));
			}
			if(event.event == Events::SCORE_INCREASE)
			{
				auto tuple = event.GetData<int>();
				const int score = std::get<0>(tuple);
				m_pDisplay->SetText("Score: " + std::to_string(score));
			}
		};
	private:
		TextComponent* m_pDisplay;
	};
}
