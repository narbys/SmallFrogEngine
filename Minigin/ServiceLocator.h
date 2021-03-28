#pragma once
#include "SoundSystem.h"

namespace dae
{

	class ServiceLocator final
	{
	public:
		//ServiceLocator();
		static ISoundSystem* GetSoundSystem();
		static void Provide(ISoundSystem* pService);
		static void Cleanup();
	
	private:
		static ISoundSystem* m_pSoundService;
		static NullSoundSystem* m_pNullService;
	};

}

