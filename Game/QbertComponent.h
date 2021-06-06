#pragma once
#include "BaseComponent.h"
#include "LevelComponent.h"

class QbertComponent final : public frog::BaseComponent
{
public:
	void Update() override;

	void Init(frog::GameObject* level);

	void MoveDownLeft();
	void MoveDownRight();
	void MoveUpLeft();
	void MoveUpRight();

private:
	int m_CurrentTileIdx{};
	float m_CharacterOffset{};
	LevelComponent* m_pLevelComp{};
	
	void MoveToTile(int tileIdx);
	void MoveCharacter(const glm::vec3& pos);
	void Die();
};

