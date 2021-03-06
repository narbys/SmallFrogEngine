#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>

#include "Command.h"

frog::InputManager::~InputManager()
{
	for(auto c : m_KeyMap)
	{
		delete c.second;
		c.second = nullptr;
	}
}

bool frog::InputManager::ProcessInput()
{
	auto err = XInputGetKeystroke(0, 0, &m_CurrentStroke);
	if (err == ERROR_NOT_CONNECTED)
		std::cerr << "XINPUT ERROR: no controller found\n";

	//Handle Buttons
	for (auto iter = m_KeyMap.begin(); iter != m_KeyMap.end(); ++iter)
	{
		WORD k = iter->first;
		if (IsPressed(k)) m_KeyMap[k]->Execute();
	}
	
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) 
		{
			return false;
		}
		if (e.type == SDL_KEYDOWN) 
		{
			WORD k = static_cast<WORD>(e.key.keysym.sym);
			auto* Command = m_KeyMap[k];
			if(Command)
				Command->Execute();
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) 
		{
			
		}
	}
	return true;
}

bool frog::InputManager::IsPressed(WORD button) const
{
	if (m_CurrentStroke.Flags == XINPUT_KEYSTROKE_KEYDOWN && m_CurrentStroke.VirtualKey == button)
		return true;
	return false;
}

void frog::InputManager::BindCommand(WORD button, Command* command)
{
	m_KeyMap[button] = command;
}

