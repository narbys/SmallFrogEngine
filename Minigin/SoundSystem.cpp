#include "MiniginPCH.h"
#include "SoundSystem.h"
#include <thread>
#include "audio.h"

//DEBUG
#include "Renderer.h"


dae::SimpleSDL2AudioSoundSystem::SimpleSDL2AudioSoundSystem()
	: m_IsRunning{true}
{
	std::thread thread(&SimpleSDL2AudioSoundSystem::ProcessEventQueue, this);
	thread.detach();
}

dae::SimpleSDL2AudioSoundSystem::~SimpleSDL2AudioSoundSystem()
{
	m_IsRunning.store(false);
}

void dae::SimpleSDL2AudioSoundSystem::PlaySound(const std::string& filename, int volume)
{
	Renderer::GetInstance().LogDebugText("Playing sound "+filename+" at "+std::to_string(volume));
	const std::pair<std::string, int> data{ filename, volume };
	
	//std::lock_guard<std::mutex> lock(m_Mutex);
	m_EventQueue.push(data);
}

void dae::SimpleSDL2AudioSoundSystem::PauseSound()
{
}

void dae::SimpleSDL2AudioSoundSystem::StopSound()
{
}

void dae::SimpleSDL2AudioSoundSystem::StopAllSounds()
{
}

void dae::SimpleSDL2AudioSoundSystem::ProcessEventQueue()
{	
	while(m_IsRunning.load()==true)
	{
		std::lock_guard<std::mutex> lock(m_Mutex);
		if (!m_EventQueue.empty())
		{
			const auto data = m_EventQueue.front();
			m_EventQueue.pop();
			playSound(data.first.c_str(), data.second);
		}
	}
}
