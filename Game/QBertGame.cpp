#include "QBertGame.h"

#include "FPSComponent.h"
#include "GameObject.h"
#include "LevelComponent.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "SceneManager.h"
#include "TextureComponent.h"

void QBertGame::LoadGame() const
{
	auto& scene = frog::SceneManager::GetInstance().CreateScene("Level1");

	//Background
	auto go = new frog::GameObject();
	go->AddComponent(new frog::TextureComponent{ "background.jpg" });
	scene.Add(go);
	
	//Title
	const auto font = frog::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	go = new frog::GameObject();
	go->AddComponent(new frog::TextComponent("Small frogs are cute", font));
	go->GetComponent<frog::TextComponent>()->SetPosition(150, 20);
	scene.Add(go);

	//FPS counter
	go = new frog::GameObject();
	go->AddComponent(new frog::FPSComponent());
	go->AddComponent(new frog::TextComponent("null", font));
	scene.Add(go);


	//The Level
	go = new frog::GameObject();
	auto* pLevelComp = new LevelComponent();
	go->AddComponent(pLevelComp);
	pLevelComp->BuildLevel();
	scene.Add(go);
}
