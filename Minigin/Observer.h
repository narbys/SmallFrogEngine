#pragma once
#include "Event.h"
#include "TextComponent.h"

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
			if (event.event == Events::PLAYER_DEATH)
			{
				auto tuple = event.GetData<int>();
				const int lives = std::get<0>(tuple);
				m_pDisplay->SetText(std::to_string(lives));
			}
		};
	private:
		TextComponent* m_pDisplay;
	};
}
