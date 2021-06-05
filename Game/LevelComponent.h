#pragma once
#include <string>
#include <vector>
#include <glm/detail/type_vec.hpp>
#include <glm/detail/type_vec3.hpp>

#include "LevelData.h"

#include "BaseComponent.h"

namespace frog {
	class TextureComponent;
}

class LevelComponent final : public frog::BaseComponent
{
public:
	LevelComponent();
	~LevelComponent() override;
	void Update() override;
	void Render() const override;
	void BuildLevel();
	glm::vec3 GetStartPos()const;
	frog::GameObject* GetTileAtIdx(int idx)const;
	int GetRowOfTile(int tileIdx)const;
	int GetMaxTiles()const;
	void AddEntity(frog::GameObject* pEntity);
	void RemoveEntity(frog::GameObject* pEntity);
	void SpawnSlickOrSam();
	
	bool m_SlickOrSamSpawned{};
private:
	std::vector<frog::GameObject*> m_pLevelEntities;
	std::vector<frog::GameObject*> m_pTiles;
	std::vector<int> m_TileRowByIdx;
	glm::vec3 m_StartPos;
	
	frog::GameObject* MakeTile(const glm::vec3& pos, const LevelData& lvlData);
	LevelData ParseLevelData();
};

