#pragma once
#include <string>
#include <vector>
//#pragma warning(push,1)
//#include <glm/detail/type_vec.hpp>
//#include <glm/detail/type_vec3.hpp>
//#pragma warning(pop)
#pragma warning(push)
#pragma warning(disable:4201)
#include <glm/glm.hpp>
#pragma warning(pop)

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
	void SetPlayer(frog::GameObject* pPlayer);
	frog::GameObject* GetPlayer()const;
	void CheckCompletion();

	void ResetSlickSamTimer();
	void ResetUggWrongwayTimer();
private:
	int m_CurrentLevelIdx{};
	frog::GameObject* m_pPlayer{};
	std::vector<frog::GameObject*> m_pLevelEntities;
	std::vector<frog::GameObject*> m_pTiles;
	std::vector<int> m_TileRowByIdx;
	glm::vec3 m_StartPos;
	LevelData m_LevelData;

	
	bool m_SlickOrSamSpawned{};
	float m_SlickSamSpawnTimer{};
	
	bool m_UggOrWrongwaySpawned{};
	float m_UggWrongwaySpawnTimer{};
	
	frog::GameObject* MakeTile(const glm::vec3& pos, const LevelData& lvlData);
	LevelData ParseLevelData();
	void SpawnSlickOrSam();
	void SpawnUggOrWrongway();
	void NextLevel();
	void Cleanup();
};

