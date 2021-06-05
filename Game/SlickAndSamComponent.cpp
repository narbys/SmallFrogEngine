#include "SlickAndSamComponent.h"

#include "GameObject.h"
#include "GameTime.h"
#include "ScoreComponent.h"
#include "TileComponent.h"

void SlickAndSamComponent::Init(const frog::GameObject* level)
{
	m_pLevelComp = level->GetComponent<LevelComponent>();
	const auto startpos = m_pLevelComp->GetStartPos();
	MoveToTile(0);
}

void SlickAndSamComponent::Update()
{
	auto* pPlayer = m_pLevelComp->GetPlayer();
	if (pPlayer)
	{
		const float killDistance(5);
		const float dist = glm::distance(m_pGameObject->GetTransform()->GetPosition(), pPlayer->GetTransform()->GetPosition());
		if (dist < killDistance)
		{
			Die();
			pPlayer->GetComponent<frog::ScoreComponent>()->AddToScore(300);
		}
	}
	
	const float elapsedSec = frog::GameTime::GetInstance().GetDeltaTime();
	m_Timer += elapsedSec;
	const float moveDelay{ 1.f };
	if(m_Timer > moveDelay)
	{
		//do some movement
		const int picker = rand() % 2;
		if (picker == 0)
			MoveRight();
		else
			MoveLeft();
		m_Timer = 0;
	}

}

void SlickAndSamComponent::MoveLeft()
{
	//X+=Y+1
	const int thisRow = m_pLevelComp->GetRowOfTile(m_CurrentTileIdx);
	const int newTileIdx = m_CurrentTileIdx + thisRow + 1;

	if (newTileIdx > m_pLevelComp->GetMaxTiles() - 1)
	{
		Die();
		return;	//fall off
	}

	MoveToTile(newTileIdx);
	m_CurrentTileIdx = newTileIdx;
}

void SlickAndSamComponent::MoveRight()
{
	//X+=Y+2
	const int thisRow = m_pLevelComp->GetRowOfTile(m_CurrentTileIdx);
	const int newTileIdx = m_CurrentTileIdx + thisRow + 2;

	if (newTileIdx > m_pLevelComp->GetMaxTiles() - 1 || newTileIdx < 0)
	{
		Die();
		return;	//fall off
	}

	MoveToTile(newTileIdx);
	m_CurrentTileIdx = newTileIdx;
}

void SlickAndSamComponent::MoveToTile(int tileIdx) const
{
	auto* pTile = m_pLevelComp->GetTileAtIdx(tileIdx);
	const auto pos = pTile->GetTransform()->GetPosition();
	auto tileComp = pTile->GetComponent<TileComponent>();
	tileComp->TileEnteredByGreenDude();

	MoveCharacter(pos);
}

void SlickAndSamComponent::MoveCharacter(const glm::vec3& pos) const
{
	m_pGameObject->GetTransform()->SetPosition(pos.x + m_CharacterOffset, pos.y - m_CharacterOffset, 1);
}

void SlickAndSamComponent::Die() const
{
	m_pLevelComp->m_SlickOrSamSpawned = false;
	m_pLevelComp->RemoveEntity(m_pGameObject);
}
