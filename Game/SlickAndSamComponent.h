#pragma once
#include "BaseComponent.h"
#include "LevelComponent.h"

class SlickAndSamComponent final : public frog::BaseComponent
{
public:
	void Init(const frog::GameObject* level);
	void Update() override;

private:
	LevelComponent* m_pLevelComp{};
	int m_CurrentTileIdx{};
	float m_CharacterOffset{ 8 };
	float m_Timer{};
	
	void MoveLeft();
	void MoveRight();
	void MoveToTile(int tileIdx) const;
	void MoveCharacter(const glm::vec3& pos) const;
	void Die() const;

};

