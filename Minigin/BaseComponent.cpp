#include "MiniginPCH.h"
#include "BaseComponent.h"
#include "Subject.h"

dae::BaseComponent::BaseComponent()
	: m_pSubject(new Subject())
{
}

dae::BaseComponent::~BaseComponent()
{
	delete m_pSubject;
	m_pSubject = nullptr;
}
