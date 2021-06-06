#include "QbertComponent.h"

#include "GameObject.h"
#include "LivesComponent.h"
#include "ScoreComponent.h"
#include "ServiceLocator.h"
#include "TextureComponent.h"
#include "TileComponent.h"

void QbertComponent::Init(frog::GameObject* level)
{
	m_pLevelComp = level->GetComponent<LevelComponent>();
	const auto startpos = m_pLevelComp->GetStartPos();

	m_CharacterOffset = 8;
	MoveCharacter(startpos);
	//auto* tex = m_pGameObject->GetComponent<frog::TextureComponent>();
}

void QbertComponent::MoveDownLeft()
{
	//X+=Y+1
	const int thisRow = m_pLevelComp->GetRowOfTile(m_CurrentTileIdx);
	const int newTileIdx = m_CurrentTileIdx + thisRow + 1;

	if (newTileIdx > m_pLevelComp->GetMaxTiles() - 1 || newTileIdx < 0)
	{
		Die();
		frog::ServiceLocator::GetSoundSystem()->PlaySound("../Data/QbertFall.wav", 10);
		return;
	}

	MoveToTile(newTileIdx);
}

void QbertComponent::MoveDownRight()
{
	//X+=Y+2
	const int thisRow = m_pLevelComp->GetRowOfTile(m_CurrentTileIdx);
	const int newTileIdx = m_CurrentTileIdx + thisRow + 2;

	if (newTileIdx > m_pLevelComp->GetMaxTiles() - 1 || newTileIdx < 0)
	{
		Die();
		frog::ServiceLocator::GetSoundSystem()->PlaySound("../Data/QbertFall.wav", 10);
		return;
	}

	MoveToTile(newTileIdx);
}

void QbertComponent::MoveUpLeft()
{
	//X-=Y+1
	const int thisRow = m_pLevelComp->GetRowOfTile(m_CurrentTileIdx);
	const int newTileIdx = m_CurrentTileIdx - (thisRow + 1);

	if (newTileIdx > m_pLevelComp->GetMaxTiles() - 1 || newTileIdx < 0)
	{
		Die();
		frog::ServiceLocator::GetSoundSystem()->PlaySound("../Data/QbertFall.wav", 10);
		return;
	}

	const int newRow = m_pLevelComp->GetRowOfTile(newTileIdx);

	//Check if you can go to that tile
	if (newRow != thisRow - 1)
	{
		Die();
		frog::ServiceLocator::GetSoundSystem()->PlaySound("../Data/QbertFall.wav", 10);
		return;
	}

	MoveToTile(newTileIdx);
}

void QbertComponent::MoveUpRight()
{
	//X-=Y
	const int thisRow = m_pLevelComp->GetRowOfTile(m_CurrentTileIdx);
	const int newTileIdx = m_CurrentTileIdx - thisRow;

	if (newTileIdx > m_pLevelComp->GetMaxTiles() - 1 || newTileIdx < 0)
	{
		Die();
		frog::ServiceLocator::GetSoundSystem()->PlaySound("../Data/QbertFall.wav", 10);
		return;
	}

	const int newRow = m_pLevelComp->GetRowOfTile(newTileIdx);

	//Check if you can go to that tile
	if (newRow != thisRow - 1)
	{
		Die();
		frog::ServiceLocator::GetSoundSystem()->PlaySound("../Data/QbertFall.wav", 10);
		return;
	}
	MoveToTile(newTileIdx);
}

void QbertComponent::ResetCharacter()
{
	MoveToTile(0);
}

void QbertComponent::MoveToTile(int tileIdx)
{
	m_CurrentTileIdx = tileIdx;
	auto* pTile = m_pLevelComp->GetTileAtIdx(tileIdx);
	const auto pos = pTile->GetTransform()->GetPosition();
	auto tileComp = pTile->GetComponent<TileComponent>();
	bool previousTileState = tileComp->IsTileActivated();
	tileComp->TileEntered();
	MoveCharacter(pos);
	if (tileComp->IsTileActivated() != previousTileState)
	{
		m_pGameObject->GetComponent<frog::ScoreComponent>()->AddToScore(25);
		m_pLevelComp->CheckCompletion();
	}
}

void QbertComponent::MoveCharacter(const glm::vec3& pos)
{
	m_pGameObject->GetTransform()->SetPosition(pos.x + m_CharacterOffset, pos.y - m_CharacterOffset, 1);
	frog::ServiceLocator::GetSoundSystem()->PlaySound("../Data/QbertJump.wav", 10);
}

void QbertComponent::Die()
{
	MoveToTile(0);
	m_pGameObject->GetComponent<frog::LivesComponent>()->ReduceLives();
}

void QbertComponent::Update()
{
}
