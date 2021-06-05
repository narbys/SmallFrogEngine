#include "LevelComponent.h"

#include <fstream>

#include "GameObject.h"
#include "TextureComponent.h"
#include "TransformComponent.h"

#include "rapidjson.h"
#include "document.h"
#include "istreamwrapper.h"
#include "SlickAndSamComponent.h"
#include "TileComponent.h"

LevelComponent::LevelComponent()
{
}

LevelComponent::~LevelComponent()
{
	for (auto* tile : m_pTiles)
	{
		delete tile;
		tile = nullptr;
	}
	m_pTiles.clear();
	
	for(auto* entity:m_pLevelEntities)
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
	for(auto* entity:m_pLevelEntities)
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
	for(auto* entity : m_pLevelEntities)
	{
		entity->Update();
	}

	SpawnSlickOrSam();
}

void LevelComponent::BuildLevel()
{
	using namespace frog;

	LevelData lvlData = ParseLevelData();

	m_StartPos=lvlData.StartPos;
	GameObject* pTile = nullptr;

	const float textureSize{ 32.f }; //temporarily as i cannot get the size from the texturecomponent
	float xoffset{};
	const float yoffset{textureSize*0.75};
	glm::vec3 pos{ m_StartPos };
	
	int rows = 7;
	//int idx = 0;
	
	for (int i{ 1 }; i <= rows; i++)
	{
		for (int j{ 1 }; j <= i; j++)
		{
			//make tile
			pTile=MakeTile(pos, lvlData);
			m_pTiles.push_back(pTile);
			//m_TileIndices.push_back(std::vector<int>());
			//m_TileIndices[idx].push_back(i-1);
			m_TileRowByIdx.push_back(i-1);
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
	if(!m_SlickOrSamSpawned)
	{
		auto* obj = new frog::GameObject();
		const int picker = rand() % 2;
		if(picker==0)
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

void LevelComponent::SetPlayer(frog::GameObject* pPlayer)
{
	m_pPlayer = pPlayer;
}

frog::GameObject* LevelComponent::GetPlayer() const
{
	return m_pPlayer;
}

frog::GameObject* LevelComponent::MakeTile(const glm::vec3& pos, const LevelData& lvlData)
{
	using namespace frog;
	
	GameObject* pTile = new GameObject();
	auto pTexture = new TextureComponent(lvlData.InactiveImage);
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

	for (auto* it = doc.Begin(); it != doc.End(); ++it)
	{
		const Value& obj = *it;
		const Value& StartPosition = obj["StartPosition"];
		const Value& InactiveImg = obj["InactiveImage"];
		const Value& ActiveImg = obj["ActiveImage"];

		levelData.StartPos.x = StartPosition["x"].GetFloat();
		levelData.StartPos.y = StartPosition["y"].GetFloat();
		levelData.StartPos.z = StartPosition["z"].GetFloat();

		levelData.InactiveImage = InactiveImg.GetString();
		levelData.ActiveImage = ActiveImg.GetString();
	}
	
	return levelData;
}
