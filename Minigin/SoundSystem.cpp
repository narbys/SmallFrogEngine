#include "MiniginPCH.h"
#include "SoundSystem.h"
#include <thread>
#include "audio.h"

//DEBUG
#include "Renderer.h"


frog::SimpleSDL2AudioSoundSystem::SimpleSDL2AudioSoundSystem()
	: m_IsRunning{true}
{
	m_Thread =std::thread(&SimpleSDL2AudioSoundSystem::ProcessEventQueue, this);
	//std::thread thread(&SimpleSDL2AudioSoundSystem::ProcessEventQueue, this);
	//thread.detach();
}

frog::SimpleSDL2AudioSoundSystem::~SimpleSDL2AudioSoundSystem()
{
	m_IsRunning.store(false);
	m_Thread.join();
}

void frog::SimpleSDL2AudioSoundSystem::PlaySound(const std::string& filename, int volume)
{
	//Renderer::GetInstance().LogDebugText("Playing sound "+filename+" at "+std::to_string(volume));
	const std::pair<std::string, int> data{ filename, volume };
	
	std::lock_guard<std::mutex> lock(m_Mutex);
	m_EventQueue.push(data);
}

void frog::SimpleSDL2AudioSoundSystem::PauseSound()
{
}

void frog::SimpleSDL2AudioSoundSystem::StopSound()
{
}

void frog::SimpleSDL2AudioSoundSystem::StopAllSounds()
{
}

void frog::SimpleSDL2AudioSoundSystem::ProcessEventQueue()
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
