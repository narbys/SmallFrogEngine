#include "LevelComponent.h"
#include "GameObject.h"
#include "TextureComponent.h"
#include "TransformComponent.h"

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

	//const int tileAmount{ 28 };

	//the start tile
	//TextureComponent* pTileTexComponent = new TextureComponent{ "InactiveTile1.png" }; //temporary, read in from json
	glm::vec3 startPos{300,180,0};
	GameObject* pTile = nullptr;
	//m_pTiles.push_back(pTile);

	const float textureSize{ 32.f }; //temporarily as i cannot get the size from the texturecomponent
	float xoffset{};
	const float yoffset{textureSize*0.75};
	glm::vec3 pos{ startPos };
	
	int rows = 7;
	//int idx = 0;

	
	for (int i{ 1 }; i <= rows; i++)
	{
		for (int j{ 1 }; j <= i; j++)
		{
			//make tile
			pTile=MakeTile(pos);
			m_pTiles.push_back(pTile);
			pos.x += textureSize;
			//++idx;
		}
		xoffset += textureSize * 0.5f;
		pos.y += yoffset;
		pos.x = startPos.x;
		pos.x -= xoffset;
	}

}

frog::GameObject* LevelComponent::MakeTile(glm::vec3 pos)
{
	using namespace frog;
	GameObject* pTile = new GameObject();
	TextureComponent* pTexture = new TextureComponent("InactiveTile1.png");
	pTile->AddComponent(pTexture);
	pTile->GetTransform()->SetPosition(pos.x, pos.y, pos.z);
	return pTile;
}
