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
	//depends on which level, lvl1 now
	if(!m_IsTileActive)
	{
		ActivateTile();
	}
}

void TileComponent::ActivateTile()
{
	auto* pTexture = m_pGameObject->GetComponent<frog::TextureComponent>();
	pTexture->SetTexture(m_LevelData.ActiveImage);
	m_IsTileActive = true;
}
