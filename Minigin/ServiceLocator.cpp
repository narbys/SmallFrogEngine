#include "ServiceLocator.h"

dae::ISoundSystem* dae::ServiceLocator::m_pSoundService{};
dae::NullSoundSystem* dae::ServiceLocator::m_pNullService{};

dae::ISoundSystem* dae::ServiceLocator::GetSoundSystem()
{
	return m_pSoundService;
}

void dae::ServiceLocator::Provide(ISoundSystem* pService)
{
	if (pService == nullptr)
		m_pSoundService = m_pNullService;
	else
	{
		delete m_pSoundService;
		m_pSoundService = pService;
	}
}

void dae::ServiceLocator::Cleanup()
{
	delete m_pNullService;
	m_pNullService = nullptr;
	delete m_pSoundService;
	m_pSoundService = nullptr;
}
