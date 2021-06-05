#include "QbertComponent.h"

#include "GameObject.h"
#include "TextureComponent.h"
#include "TileComponent.h"

void QbertComponent::Init(frog::GameObject* level)
{
	m_pLevelComp = level->GetComponent<LevelComponent>();
	const auto startpos = m_pLevelComp->GetStartPos();

	m_CharacterOffset = 8;	//tex->GetSize()
	MoveCharacter(startpos);
	auto* tex = m_pGameObject->GetComponent<frog::TextureComponent>();
}

void QbertComponent::MoveDownLeft()
{
	//X+=Y+1
	const int thisRow = m_pLevelComp->GetRowOfTile(m_CurrentTileIdx);
	const int newTileIdx = m_CurrentTileIdx + thisRow + 1;

	if (newTileIdx > m_pLevelComp->GetMaxTiles() - 1 || newTileIdx < 0)
		return;

	MoveToTile(newTileIdx);
	m_CurrentTileIdx = newTileIdx;
}

void QbertComponent::MoveDownRight()
{
	//X+=Y+2
	const int thisRow = m_pLevelComp->GetRowOfTile(m_CurrentTileIdx);
	const int newTileIdx = m_CurrentTileIdx + thisRow + 2;

	if (newTileIdx > m_pLevelComp->GetMaxTiles() - 1 || newTileIdx < 0)
		return;

	MoveToTile(newTileIdx);
	m_CurrentTileIdx = newTileIdx;
}

void QbertComponent::MoveUpLeft()
{
	//X-=Y+1
	const int thisRow = m_pLevelComp->GetRowOfTile(m_CurrentTileIdx);
	const int newTileIdx = m_CurrentTileIdx - (thisRow + 1);

	if (newTileIdx > m_pLevelComp->GetMaxTiles() - 1 || newTileIdx < 0)
		return;

	const int newRow = m_pLevelComp->GetRowOfTile(newTileIdx);

	//Check if you can go to that tile
	if (newRow != thisRow - 1)
	{
		//idk die or some shit
		return;
	}

	MoveToTile(newTileIdx);
	m_CurrentTileIdx = newTileIdx;
}

void QbertComponent::MoveUpRight()
{
	//X-=Y
	const int thisRow = m_pLevelComp->GetRowOfTile(m_CurrentTileIdx);
	const int newTileIdx = m_CurrentTileIdx - thisRow;

	if (newTileIdx > m_pLevelComp->GetMaxTiles() - 1 || newTileIdx < 0)
		return;

	const int newRow = m_pLevelComp->GetRowOfTile(newTileIdx);

	//Check if you can go to that tile
	if (newRow != thisRow - 1)
	{
		//idk die or some shit
		return;
	}
	MoveToTile(newTileIdx);
	m_CurrentTileIdx = newTileIdx;
}

void QbertComponent::MoveToTile(int tileIdx)
{
	auto* pTile = m_pLevelComp->GetTileAtIdx(tileIdx);
	const auto pos = pTile->GetTransform()->GetPosition();
	pTile->GetComponent<TileComponent>()->TileEntered();
	
	MoveCharacter(pos);
}

void QbertComponent::MoveCharacter(const glm::vec3& pos)
{
	m_pGameObject->GetTransform()->SetPosition(pos.x + m_CharacterOffset, pos.y - m_CharacterOffset, 1);
}

void QbertComponent::Update()
{
}
