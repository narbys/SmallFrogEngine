#pragma once
#include <iostream>
#include <mutex>
#include <queue>

namespace dae
{

	class ISoundSystem abstract
	{
	public:
		virtual ~ISoundSystem() = default;
		virtual void PlaySound(const std::string& filename, int volume) = 0;
		virtual void PauseSound() = 0;
		virtual void StopSound() = 0;
		virtual void StopAllSounds() = 0;
	};
	class NullSoundSystem final : public ISoundSystem
	{
	public:
		void PlaySound(const std::string&, int) override {};
		void PauseSound() override {};
		void StopSound() override {};
		void StopAllSounds() override {};
	};

	class SimpleSDL2AudioSoundSystem final : public ISoundSystem
	{
	public:
		SimpleSDL2AudioSoundSystem();
		virtual ~SimpleSDL2AudioSoundSystem();
		void PlaySound(const std::string& filename, int volume) override;
		void PauseSound() override;
		void StopSound() override;
		void StopAllSounds() override;

		void ProcessEventQueue();
	private:
		std::queue<std::pair<std::string, int>> m_EventQueue;
		std::atomic<bool> m_IsRunning;
		std::mutex m_Mutex;
	};

}