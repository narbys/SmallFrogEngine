#include "LevelComponent.h"

#include <fstream>

#include "GameObject.h"
#include "TextureComponent.h"
#include "TransformComponent.h"

#include "rapidjson.h"
#include "document.h"
#include "istreamwrapper.h"

void LevelComponent::Render() const
{
	for (auto* tile : m_pTiles)
	{
		tile->Render();
	}
}

LevelComponent::~LevelComponent()
{
	for (auto* tile : m_pTiles)
	{
		delete tile;
		tile = nullptr;
	}
	m_pTiles.clear();
}

void LevelComponent::Update()
{
	for (auto* tile : m_pTiles)
	{
		tile->Update();
	}
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
	//m_TileIndices.reserve(rows);
	
	for (int i{ 1 }; i <= rows; i++)
	{
		for (int j{ 1 }; j <= i; j++)
		{
			//make tile
			pTile=MakeTile(pos, lvlData.InactiveImage);
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

frog::GameObject* LevelComponent::MakeTile(const glm::vec3& pos, const std::string& textureFileName)
{
	using namespace frog;
	GameObject* pTile = new GameObject();
	auto pTexture = new TextureComponent(textureFileName);
	pTile->AddComponent(pTexture);
	pTile->GetTransform()->SetPosition(pos.x, pos.y, pos.z);
	return pTile;
}

LevelComponent::LevelData LevelComponent::ParseLevelData()
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
