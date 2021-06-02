#include "ServiceLocator.h"

frog::ISoundSystem* frog::ServiceLocator::m_pSoundService{};
frog::NullSoundSystem* frog::ServiceLocator::m_pNullService{};

frog::ISoundSystem* frog::ServiceLocator::GetSoundSystem()
{
	return m_pSoundService;
}

void frog::ServiceLocator::Provide(ISoundSystem* pService)
{
	if (pService == nullptr)
		m_pSoundService = m_pNullService;
	else
	{
		delete m_pSoundService;
		m_pSoundService = pService;
	}
}

void frog::ServiceLocator::Cleanup()
{
	delete m_pNullService;
	m_pNullService = nullptr;
	delete m_pSoundService;
	m_pSoundService = nullptr;
}
