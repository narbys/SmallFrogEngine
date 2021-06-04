#include "QBertGame.h"

#include "FPSComponent.h"
#include "GameObject.h"
#include "InputManager.h"
#include "LevelComponent.h"
#include "QbertComponent.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "SceneManager.h"
#include "TextureComponent.h"
#include "CustomCommands.h"

void QBertGame::LoadGame()
{
	auto& scene = frog::SceneManager::GetInstance().CreateScene("Level1");

	//Background
	auto go = new frog::GameObject();
	go->AddComponent(new frog::TextureComponent{ "background.jpg" });
	scene.Add(go);
	
	//Title
	const auto font = frog::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	go = new frog::GameObject();
	go->AddComponent(new frog::TextComponent("I will scream again", font));
	go->GetComponent<frog::TextComponent>()->SetPosition(150, 20);
	scene.Add(go);

	//FPS counter
	go = new frog::GameObject();
	go->AddComponent(new frog::FPSComponent());
	go->AddComponent(new frog::TextComponent("null", font));
	scene.Add(go);

	//The Level
	m_pLevel = new frog::GameObject();
	auto* pLevelComp = new LevelComponent();
	m_pLevel->AddComponent(pLevelComp);
	pLevelComp->BuildLevel();
	scene.Add(m_pLevel);

	//The Character
	m_pQbert = new frog::GameObject();
	m_pQbert->AddComponent(new frog::TextureComponent{ "QbertSprite.png" });
	auto* QbertComp = new QbertComponent();
	m_pQbert->AddComponent(QbertComp);
	QbertComp->Init(m_pLevel);
	scene.Add(m_pQbert);


	//Input
	frog::InputManager::GetInstance().BindCommand(VK_PAD_DPAD_LEFT, new MoveQbertBottomLeftCommand(QbertComp));
	frog::InputManager::GetInstance().BindCommand(VK_PAD_DPAD_DOWN, new MoveQbertBottomRightCommand(QbertComp));
	frog::InputManager::GetInstance().BindCommand(VK_PAD_DPAD_UP, new MoveQbertUpLeftCommand(QbertComp));
	frog::InputManager::GetInstance().BindCommand(VK_PAD_DPAD_RIGHT, new MoveQbertUpRightCommand(QbertComp));
	//frog::InputManager::GetInstance().BindCommand(VK_PAD_B, new frog::KillPlayerCommand(m_pQbert));
	//frog::InputManager::GetInstance().BindCommand(VK_PAD_X, new frog::IncreaseScoreCommand(m_pQbert));
}
