#include "MiniginPCH.h"
#include "FPSComponent.h"

#include "Time.h"

dae::FPSComponent::FPSComponent()
{
	
}

dae::FPSComponent::~FPSComponent()
{
}

int dae::FPSComponent::GetFps() const
{
	return m_Fps;
}

void dae::FPSComponent::Update()
{
	if(!m_pText)
		m_pText=m_pGameObject->GetComponent<TextComponent>();

	m_ElapsedSec = Time::GetInstance().GetDeltaTime();	
	m_Fps = static_cast<int>(1.f / m_ElapsedSec);
	if (m_pText)
			m_pText->SetText("FPS: " + std::to_string(m_Fps));
}
