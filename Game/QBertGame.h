#pragma once
#include "Game.h"
class QBertGame final : public frog::Game
{
public:
	virtual ~QBertGame() = default;
	void LoadGame() const override;
};

