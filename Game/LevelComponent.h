#pragma once
#include <vector>
#include <glm/detail/type_vec.hpp>


#include "BaseComponent.h"

namespace frog {
	class TextureComponent;
}

class LevelComponent : public frog::BaseComponent
{
public:
	LevelComponent() = default;
	virtual ~LevelComponent();
	void Update() override;
	void Render() const override;
	void BuildLevel();
private:
	std::vector<frog::GameObject*> m_pTiles;
	frog::GameObject* MakeTile(glm::vec3 pos);
};

