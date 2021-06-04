#pragma once
#include "Game.h"


namespace frog {
	class GameObject;
}

class QBertGame final : public frog::Game
{	
public:
	virtual ~QBertGame() = default;
	void LoadGame() override;
private:
	frog::GameObject* m_pLevel{};
	frog::GameObject* m_pQbert{};
};

