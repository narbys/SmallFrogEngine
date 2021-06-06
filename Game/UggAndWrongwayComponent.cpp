#include "UggAndWrongwayComponent.h"
#include "GameObject.h"
#include "GameTime.h"
#include "LevelComponent.h"
#include "QbertComponent.h"
#include "ServiceLocator.h"
#include "TileComponent.h"

void UggAndWrongwayComponent::Init(const frog::GameObject* level, bool isUgg)
{
	m_pLevelComp = level->GetComponent<LevelComponent>();
	m_IsUgg = isUgg;
	if (isUgg)
		MoveToTile(ConvertTileIdxRight(0));
	else
		MoveToTile(ConvertTileIdxLeft(0));
}

void UggAndWrongwayComponent::Update()
{

	auto* pPlayer = m_pLevelComp->GetPlayer();
	if (pPlayer)
	{
		const float killDistance(16);
		const float dist = glm::distance(m_pGameObject->GetTransform()->GetPosition(), pPlayer->GetTransform()->GetPosition());
		if (dist < killDistance)
		{
			//kill the player
			pPlayer->GetComponent<QbertComponent>()->Die();
			frog::ServiceLocator::GetSoundSystem()->PlaySound("../Data/QbertDie.wav", 10);
		}
	}
	
	const float elapsedSec = frog::GameTime::GetInstance().GetDeltaTime();
	m_Timer += elapsedSec;
	const float moveDelay{ 1.f };
	if (m_Timer > moveDelay)
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

void UggAndWrongwayComponent::MoveLeft()
{
	//X+=Y+1
	const int thisRow = m_pLevelComp->GetRowOfTile(m_CurrentTileIdx);
	const int newTileIdx = m_CurrentTileIdx + thisRow + 1;

	if (newTileIdx > m_pLevelComp->GetMaxTiles() - 1)
	{
		Die();
		return;	//fall off
	}
	//need conversion for position
	int convertedIdx{};
	if (m_IsUgg)
		convertedIdx = ConvertTileIdxRight(newTileIdx);
	else
		convertedIdx = ConvertTileIdxLeft(newTileIdx);
	MoveToTile(convertedIdx);
	m_CurrentTileIdx = newTileIdx;
}

void UggAndWrongwayComponent::MoveRight()
{
	//X+=Y+2
	const int thisRow = m_pLevelComp->GetRowOfTile(m_CurrentTileIdx);
	const int newTileIdx = m_CurrentTileIdx + thisRow + 2;

	if (newTileIdx > m_pLevelComp->GetMaxTiles() - 1 || newTileIdx < 0)
	{
		Die();
		return;	//fall off
	}
	//need conversion for position
	int convertedIdx{};
	if (m_IsUgg)
		convertedIdx = ConvertTileIdxRight(newTileIdx);
	else
		convertedIdx = ConvertTileIdxLeft(newTileIdx);
	MoveToTile(convertedIdx);
	m_CurrentTileIdx = newTileIdx;
}
void UggAndWrongwayComponent::MoveToTile(int tileIdx) const
{
	auto* pTile = m_pLevelComp->GetTileAtIdx(tileIdx);
	const auto pos = pTile->GetTransform()->GetPosition();
	MoveCharacter(pos);
}

void UggAndWrongwayComponent::MoveCharacter(const glm::vec3& pos) const
{
	if(m_IsUgg)
		m_pGameObject->GetTransform()->SetPosition(pos.x + m_CharacterOffset * 2, pos.y + m_CharacterOffset, 1);
	else
		m_pGameObject->GetTransform()->SetPosition(pos.x, pos.y + m_CharacterOffset, 1);
}

void UggAndWrongwayComponent::Die() const
{
	m_pLevelComp->ResetUggWrongwayTimer();
	m_pLevelComp->RemoveEntity(m_pGameObject);
}

int UggAndWrongwayComponent::ConvertTileIdxRight(int idx)
{
	//hardcoded since i dont have the time to find a formula
	int h[] = { 27, 20, 26, 14, 19, 25, 9, 13, 18, 24, 5, 8, 12, 17, 23, 2, 4, 7,11,16,22, 0, 1,3,6,10,15,21 };
	const int newIdx = h[idx];
	return newIdx;
}

int UggAndWrongwayComponent::ConvertTileIdxLeft(int idx)
{
	int h[] = {21,22,15,23,16,10,24,17,11,6,25,18,12,7,3,26,19,13,8,4,1,27,20,14,9,5,2,0 };
	const int newIdx = h[idx];
	return newIdx;
}
