#pragma once
#include <glm/detail/type_vec.hpp>

#include "BaseComponent.h"

class LevelComponent;

class UggAndWrongwayComponent final : public frog::BaseComponent
{
public:
	void Init(const frog::GameObject* level, bool isUgg);
	void Update() override;
private:
	bool m_IsUgg{};
	LevelComponent* m_pLevelComp;
	int m_CurrentTileIdx{};
	float m_CharacterOffset{ 8 };
	float m_Timer{};

	void MoveLeft();
	void MoveRight();
	void MoveToTile(int tileIdx) const;
	void MoveCharacter(const glm::vec3& pos) const;
	void Die() const;

	int ConvertTileIdxRight(int idx);
	int ConvertTileIdxLeft(int idx);
};

