#include "MiniginPCH.h"
#include "BaseComponent.h"
#include "Subject.h"

frog::BaseComponent::BaseComponent()
	: m_pSubject(new Subject())
{
}

frog::BaseComponent::~BaseComponent()
{
	delete m_pSubject;
	m_pSubject = nullptr;
}
