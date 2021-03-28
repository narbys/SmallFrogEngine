#include "MiniginPCH.h"
#include "SoundSystem.h"

//DEBUG
#include "Renderer.h"

dae::SimpleSDL2AudioSoundSystem::SimpleSDL2AudioSoundSystem()
{
}

void dae::SimpleSDL2AudioSoundSystem::PlaySound(const std::string& filename, int volume)
{
	Renderer::GetInstance().LogDebugText("Playing sound "+filename+" at "+std::to_string(volume));
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
