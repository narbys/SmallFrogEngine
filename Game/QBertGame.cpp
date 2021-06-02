#include "QBertGame.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "SceneManager.h"
#include "TextureComponent.h"

void QBertGame::LoadGame() const
{
	auto& scene = frog::SceneManager::GetInstance().CreateScene("poggies");

	//Background
	auto go = new frog::GameObject();
	go->AddComponent(new frog::TextureComponent{ "background.jpg" });
	scene.Add(go);
	
	//Logo
	go = new frog::GameObject();
	go->AddComponent(new frog::TextureComponent{ "observer.jpg",100,180,500,100 });
	scene.Add(go);
	
	//Title
	auto font = frog::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	go = new frog::GameObject();
	go->AddComponent(new frog::TextComponent("Small frogs are cute", font));
	go->GetComponent<frog::TextComponent>()->SetPosition(150, 20);
	scene.Add(go);
}
