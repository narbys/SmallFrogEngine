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
	LevelComponent() = default;
	virtual ~LevelComponent();
	void Update() override;
	void Render() const override;
	void BuildLevel();
	glm::vec3 GetStartPos()const;
	frog::GameObject* GetTileAtIdx(int idx)const;
	int GetRowOfTile(int tileIdx)const;
	int GetMaxTiles()const;
private:
	glm::vec3 m_StartPos;
	std::vector<frog::GameObject*> m_pTiles;
	//std::vector<std::vector<int>> m_TileIndices;
	std::vector<int> m_TileRowByIdx;
	frog::GameObject* MakeTile(const glm::vec3& pos, const LevelData& lvlData);
	LevelData ParseLevelData();
};

