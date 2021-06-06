#include "TileComponent.h"
#include "GameObject.h"
#include "TextureComponent.h"

void TileComponent::Init(const LevelData& lvlData)
{
	m_LevelData = lvlData;
}

void TileComponent::Update()
{
}



void TileComponent::TileEntered()
{
	int config = m_LevelData.Config;
	switch (config)
	{
		case 1:
		{
			if (!m_IsTileActive)
				ActivateTile();
		}
		break;
		case 2:
		{
			if (!m_IsTileActive)
				ActivateTile();
			else if (!m_IsTileActiveTwice)
				ActivateTileTwice();
		}
		break;
		case 3:
		{
			if (!m_IsTileActive)
				ActivateTile();
			else
				DeactivateTile();
		}
		break;
		default:
			frog::Renderer::GetInstance().LogDebugText("NO LEVEL CONFIGURATION SET", { 1,0,0,1 });
			break;
	}
}

void TileComponent::TileEnteredByGreenDude()
{
	if (m_IsTileActive)
		DeactivateTile();
}

bool TileComponent::IsTileActivated() const
{
	if (m_LevelData.Config != 2)
		return m_IsTileActive;
	else
		return m_IsTileActiveTwice;
}

void TileComponent::ActivateTile()
{
	auto* pTexture = m_pGameObject->GetComponent<frog::TextureComponent>();
	pTexture->SetTexture(m_LevelData.ActiveImage);
	m_IsTileActive = true;
}
void TileComponent::ActivateTileTwice()
{
	auto* pTexture = m_pGameObject->GetComponent<frog::TextureComponent>();
	pTexture->SetTexture(m_LevelData.ActiveImage2);
	m_IsTileActiveTwice = true;
}
void TileComponent::DeactivateTile()
{
	auto* pTexture = m_pGameObject->GetComponent<frog::TextureComponent>();
	if (!m_IsTileActiveTwice)
	{
		pTexture->SetTexture(m_LevelData.InactiveImage);
		m_IsTileActive = false;
	}
	else
	{
		pTexture->SetTexture(m_LevelData.ActiveImage);
		m_IsTileActiveTwice = false;
	}
}
