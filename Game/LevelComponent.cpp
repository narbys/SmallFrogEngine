#include "LevelComponent.h"

#include <fstream>

#include "GameObject.h"
#include "TextureComponent.h"
#include "TransformComponent.h"

#include "rapidjson.h"
#include "document.h"
#include "GameTime.h"
#include "istreamwrapper.h"
#include "QbertComponent.h"
#include "SlickAndSamComponent.h"
#include "TileComponent.h"

LevelComponent::LevelComponent()
{
	ResetSlickSamTimer();
}

LevelComponent::~LevelComponent()
{
	for (auto* tile : m_pTiles)
	{
		delete tile;
		tile = nullptr;
	}
	m_pTiles.clear();

	for (auto* entity : m_pLevelEntities)
	{
		delete entity;
		entity = nullptr;
	}
	m_pLevelEntities.clear();
}

void LevelComponent::Render() const
{
	for (auto* tile : m_pTiles)
	{
		tile->Render();
	}
	for (auto* entity : m_pLevelEntities)
	{
		entity->Render();
	}
}

void LevelComponent::Update()
{
	for (auto* tile : m_pTiles)
	{
		tile->Update();
	}
	for (auto* entity : m_pLevelEntities)
	{
		entity->Update();
	}

	if (m_SlickSamSpawnTimer <= 0)
	{
		SpawnSlickOrSam();
	}
	else
	{
		const float elapsedSec = frog::GameTime::GetInstance().GetDeltaTime();
		//countdown
		m_SlickSamSpawnTimer -= elapsedSec;
	}
}

void LevelComponent::BuildLevel()
{
	using namespace frog;

	m_LevelData = ParseLevelData();

	m_StartPos = m_LevelData.StartPos;
	GameObject* pTile = nullptr;

	const float textureSize{ 32.f };
	float xoffset{};
	const float yoffset{ textureSize * 0.75 };
	glm::vec3 pos{ m_StartPos };

	int rows = 7;
	//int idx = 0;

	for (int i{ 1 }; i <= rows; i++)
	{
		for (int j{ 1 }; j <= i; j++)
		{
			//make tile
			pTile = MakeTile(pos, m_LevelData);
			m_pTiles.push_back(pTile);
			m_TileRowByIdx.push_back(i - 1);
			pos.x += textureSize;
			//++idx;
		}
		xoffset += textureSize * 0.5f;
		pos.y += yoffset;
		pos.x = m_StartPos.x;
		pos.x -= xoffset;
	}

}

glm::vec3 LevelComponent::GetStartPos() const
{
	return m_StartPos;
}

frog::GameObject* LevelComponent::GetTileAtIdx(int idx) const
{
	return m_pTiles[idx];
}

int LevelComponent::GetRowOfTile(int tileIdx) const
{
	return m_TileRowByIdx[tileIdx];
}

int LevelComponent::GetMaxTiles() const
{
	return m_pTiles.size();
}

void LevelComponent::AddEntity(frog::GameObject* pEntity)
{
	m_pLevelEntities.push_back(pEntity);
}

void LevelComponent::RemoveEntity(frog::GameObject* pEntity)
{
	m_pLevelEntities.erase(std::remove(m_pLevelEntities.begin(), m_pLevelEntities.end(), pEntity), m_pLevelEntities.end());
	delete pEntity;
}

void LevelComponent::SpawnSlickOrSam()
{
	if (!m_SlickOrSamSpawned)
	{
		auto* obj = new frog::GameObject();
		const int picker = rand() % 2;
		if (picker == 0)
			obj->AddComponent(new frog::TextureComponent("Slick.png"));
		else
			obj->AddComponent(new frog::TextureComponent("Sam.png"));

		auto* pGreenDudeComp = new SlickAndSamComponent();
		obj->AddComponent(pGreenDudeComp);
		pGreenDudeComp->Init(m_pGameObject);
		//owned and managed by the level
		AddEntity(obj);
		m_SlickOrSamSpawned = true;
	}
}

void LevelComponent::NextLevel()
{
	//Reset this level and go to the next one
	//remove the tiles of this level
	for (auto* tile : m_pTiles)
	{
		delete tile;
		tile = nullptr;
	}
	m_pTiles.clear();
	//increase level index
	m_CurrentLevelIdx++;
	//build up the new level again
	BuildLevel();
	m_pPlayer->GetComponent<QbertComponent>()->ResetCharacter();
}

void LevelComponent::SetPlayer(frog::GameObject* pPlayer)
{
	m_pPlayer = pPlayer;
}

frog::GameObject* LevelComponent::GetPlayer() const
{
	return m_pPlayer;
}

void LevelComponent::ResetSlickSamTimer()
{
	const int maxTime{ 30 };
	const int minTime{ 2 };
	m_SlickSamSpawnTimer = static_cast<float>(rand() % maxTime + minTime);

	m_SlickOrSamSpawned = false;
}

void LevelComponent::CheckCompletion()
{
	for (frog::GameObject* pTile : m_pTiles)
	{
		const bool active = pTile->GetComponent<TileComponent>()->IsTileActivated();
		if (!active) return;
	}
	//if it gets here, level is completed
	//destroy this level and load in the next one
	frog::Renderer::GetInstance().LogDebugText("Level completed!", { 0,1,0,1 });
	NextLevel();
}

frog::GameObject* LevelComponent::MakeTile(const glm::vec3& pos, const LevelData& lvlData)
{
	using namespace frog;

	GameObject* pTile = new GameObject();
	auto* pTexture = new TextureComponent(lvlData.InactiveImage);
	pTile->AddComponent(pTexture);
	auto* tileComp = new TileComponent();
	pTile->AddComponent(tileComp);
	tileComp->Init(lvlData);
	pTile->GetTransform()->SetPosition(pos.x, pos.y, pos.z);
	return pTile;
}

LevelData LevelComponent::ParseLevelData()
{
	using namespace rapidjson;

	LevelData levelData{};

	std::ifstream in{ "../Data/Levels.json" };
	IStreamWrapper inwrap{ in };

	Document doc;
	doc.ParseStream(inwrap);
	int maxIdx = doc.Size()-1;
	if (m_CurrentLevelIdx > maxIdx) m_CurrentLevelIdx = 0;
	//for (auto* it = doc.Begin(); it != doc.End(); ++it)
	//{
	const Value& obj = doc[m_CurrentLevelIdx];//*it;
	const Value& startPosition = obj["StartPosition"];
	const Value& inactiveImg = obj["InactiveImage"];
	const Value& activeImg = obj["ActiveImage"];
	const Value& activeImg2 = obj["ActiveImage2"];
	const Value& levelConfig = obj["Configuration"];

	levelData.StartPos.x = startPosition["x"].GetFloat();
	levelData.StartPos.y = startPosition["y"].GetFloat();
	levelData.StartPos.z = startPosition["z"].GetFloat();

	levelData.InactiveImage = inactiveImg.GetString();
	levelData.ActiveImage = activeImg.GetString();
	levelData.ActiveImage2 = activeImg2.GetString();

	levelData.Config = levelConfig.GetInt();
	//}

	return levelData;
}
