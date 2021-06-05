#pragma once
#include "BaseComponent.h"
#include "LevelData.h"
class TileComponent : public frog::BaseComponent
{
public:
	void Init(const LevelData& lvlData);
	void Update() override;
	void TileEntered();
	void TileEnteredByGreenDude();
	bool IsTileActivated()const;
private:
	LevelData m_LevelData{};
	bool m_IsTileActive = false;
	void ActivateTile();
	void DeactivateTile();
};

