#pragma once
#include <map>
#include <XInput.h>
#include "Singleton.h"

namespace dae
{
	//enum class ControllerButton
	//{
	//	ButtonA,
	//	ButtonB,
	//	ButtonX,
	//	ButtonY
	//};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		~InputManager();
		
		bool ProcessInput();
		bool IsPressed(WORD button) const;
		void BindCommand(WORD button, class Command* command);
	private:
		XINPUT_KEYSTROKE m_CurrentStroke{};
		std::map<WORD, class Command*> m_KeyMap;
	};
}
