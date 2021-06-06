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
#include "../3rdParty/SDL2/include/SDL_keycode.h"

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
	go->AddComponent(new frog::TextComponent("Death comes to all", font));
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

	//Live display observer
	go = new frog::GameObject();
	const auto pLivesText = static_cast<frog::TextComponent*>(go->AddComponent(new frog::TextComponent("Lives: ", font)));
	pLivesText->SetPosition(0, 50);
	const auto livesDisplayObserver = std::make_shared<frog::Display>(pLivesText);
	scene.Add(go);

	//Score display observer
	go = new frog::GameObject();
	const auto pScoreText= static_cast<frog::TextComponent*>(go->AddComponent(new frog::TextComponent("Score: 0", font)));
	pScoreText->SetPosition(0, 80);
	const auto scoreDisplayObserver = std::make_shared<frog::Display>(pScoreText);
	scene.Add(go);

	//The Character
	m_pQbert = new frog::GameObject();
	m_pQbert->AddComponent(new frog::TextureComponent{ "QbertSprite.png" });
	auto* QbertComp = new QbertComponent();
	m_pQbert->AddComponent(QbertComp);
	QbertComp->Init(m_pLevel);
	pLevelComp->SetPlayer(m_pQbert);
	
	auto* pLivesComp = new frog::LivesComponent(3);
	pLivesText->SetText("Lives: "+std::to_string(pLivesComp->GetLives()));
	pLivesComp->GetSubject()->AddObserver(livesDisplayObserver);
	m_pQbert->AddComponent(pLivesComp);

	auto* pScoreComp = new frog::ScoreComponent();
	pScoreComp->GetSubject()->AddObserver(scoreDisplayObserver);
	m_pQbert->AddComponent(pScoreComp);
	
	scene.Add(m_pQbert);

	//slick and sam (spawned by level later)
	//go = new frog::GameObject();
	//go->AddComponent(new frog::TextureComponent("Slick.png"));
	//auto* pGreenDudeComp=new SlickAndSamComponent();
	//pGreenDudeComp->Init(m_pLevel);
	//go->AddComponent(pGreenDudeComp);
	////owned and managed by the level
	//pLevelComp->AddEntity(go);
	////scene.Add(go);
	
	//Input
	frog::InputManager::GetInstance().BindCommand(VK_PAD_DPAD_LEFT, new MoveQbertBottomLeftCommand(QbertComp));
	frog::InputManager::GetInstance().BindCommand(VK_PAD_DPAD_DOWN, new MoveQbertBottomRightCommand(QbertComp));
	frog::InputManager::GetInstance().BindCommand(VK_PAD_DPAD_UP, new MoveQbertUpLeftCommand(QbertComp));
	frog::InputManager::GetInstance().BindCommand(VK_PAD_DPAD_RIGHT, new MoveQbertUpRightCommand(QbertComp));

	frog::InputManager::GetInstance().BindCommand(SDL_SCANCODE_LEFT, new MoveQbertBottomLeftCommand(QbertComp));
	frog::InputManager::GetInstance().BindCommand(SDL_SCANCODE_DOWN, new MoveQbertBottomRightCommand(QbertComp));
	frog::InputManager::GetInstance().BindCommand(SDL_SCANCODE_UP, new MoveQbertUpLeftCommand(QbertComp));
	frog::InputManager::GetInstance().BindCommand(SDL_SCANCODE_RIGHT, new MoveQbertUpRightCommand(QbertComp));

}

