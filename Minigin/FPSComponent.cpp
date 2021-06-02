#include "MiniginPCH.h"
#include "FPSComponent.h"
#include "TextComponent.h"
#include "Time.h"

frog::FPSComponent::FPSComponent()
{
	
}

frog::FPSComponent::~FPSComponent()
{
}

int frog::FPSComponent::GetFps() const
{
	return m_Fps;
}

void frog::FPSComponent::Update()
{
	if(!m_pText)
		m_pText=m_pGameObject->GetComponent<TextComponent>();

	m_ElapsedSec = Time::GetInstance().GetDeltaTime();	
	m_Fps = static_cast<int>(1.f / m_ElapsedSec);
	if (m_pText)
			m_pText->SetText("FPS: " + std::to_string(m_Fps));
}
