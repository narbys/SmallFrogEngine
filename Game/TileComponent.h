#pragma once
#include "BaseComponent.h"
#include "LevelData.h"
class TileComponent : public frog::BaseComponent
{
public:
	void Init(const LevelData& lvlData);
	void Update() override;
	void ActivateTileTwice();
	void TileEntered();
	void TileEnteredByGreenDude();
	bool IsTileActivated()const;
private:
	LevelData m_LevelData{};
	bool m_IsTileActive = false;
	bool m_IsTileActiveTwice = false;
	void ActivateTile();
	void DeactivateTile();
};

