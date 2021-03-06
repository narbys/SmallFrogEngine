#include "MiniginPCH.h"
#include "SmallFrog.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>


#include "audio.h"
#include "ComponentIncludes.h"
#include "Command.h"
#include "Game.h"
#include "GameObject.h"
#include "Scene.h"
#include "GameTime.h"
#include "SoundSystem.h"
#include "ServiceLocator.h"

using namespace std;
using namespace std::chrono;

void frog::SmallFrog::Initialize()
{
	_putenv("SDL_AUDIODRIVER=DirectSound");
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	// Initialize SDL2 Audio only
	SDL_Init(SDL_INIT_AUDIO);

	// Initialize Simple-SDL2-Audio
	initAudio();
	
	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);

	//soundsystem test
	SimpleSDL2AudioSoundSystem* pss = new SimpleSDL2AudioSoundSystem();
	ServiceLocator::Provide(pss);
}

/**
 * Code constructing the scene world starts here
 */
void frog::SmallFrog::LoadGame()
{
	if (m_pGame) m_pGame->LoadGame();
	//auto& scene = SceneManager::GetInstance().CreateScene("");

	////Background
	//auto go = new GameObject();
	//go->AddComponent(new TextureComponent{ "background.jpg" });
	//scene.Add(go);
	//
	////Logo
	//go = new GameObject();
	//go->AddComponent(new TextureComponent{ "observer.jpg",100,180,500,100 });
	//scene.Add(go);
	//
	////Title
	//auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	//go = new GameObject();
	//go->AddComponent(new TextComponent("Small frogs are cute", font));
	//go->GetComponent<TextComponent>()->SetPosition(150, 20);
	//scene.Add(go);

	////FPS counter
	//go = new GameObject();
	//go->AddComponent(new FPSComponent());
	//go->AddComponent(new TextComponent("null", font));
	//scene.Add(go);

	////Live display observer
	//go = new GameObject();
	//const auto pLivesText = static_cast<TextComponent*>(go->AddComponent(new TextComponent("Lives: ", font)));
	//pLivesText->SetPosition(0, 50);
	//const auto livesDisplayObserver = std::make_shared<Display>(pLivesText);
	//scene.Add(go);

	////Score display observer
	//go = new GameObject();
	//const auto pScoreText= static_cast<TextComponent*>(go->AddComponent(new TextComponent("Score: 0", font)));
	//pScoreText->SetPosition(0, 80);
	//const auto scoreDisplayObserver = std::make_shared<Display>(pScoreText);
	//scene.Add(go);
	//
	////Initialise Q*Bert
	//m_pQBert = new GameObject();
	//m_pQBert->AddComponent(new TextureComponent( "qbert.jpg", 100,150, 50,50));
	//LivesComponent* pLivesComp = new LivesComponent(3);
	//pLivesText->SetText("Lives: "+std::to_string(pLivesComp->GetLives()));
	//pLivesComp->GetSubject()->AddObserver(livesDisplayObserver);
	//ScoreComponent* pScoreComp = new ScoreComponent();
	//pScoreComp->GetSubject()->AddObserver(scoreDisplayObserver);
	//m_pQBert->AddComponent(pLivesComp);
	//m_pQBert->AddComponent(pScoreComp);
	//scene.Add(m_pQBert);

	////Input
	//InputManager::GetInstance().BindCommand(VK_PAD_A, new BeepboopCommand());
	//InputManager::GetInstance().BindCommand(VK_PAD_B, new KillPlayerCommand(m_pQBert));
	//InputManager::GetInstance().BindCommand(VK_PAD_X, new IncreaseScoreCommand(m_pQBert));



	//****************
	//soundsystem test
	//****************
	//SimpleSDL2AudioSoundSystem* pss = new SimpleSDL2AudioSoundSystem();
	//ServiceLocator::Provide(pss);
	
}

void frog::SmallFrog::Cleanup()
{
	ServiceLocator::Cleanup();

	// End Simple-SDL2-Audio
	endAudio();
	//End
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
	delete m_pGame;
}

void frog::SmallFrog::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	LoadGame();

	{
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();

		bool doContinue = true;
		auto lastTime = high_resolution_clock::now();
		float lag = 0.f;
		while (doContinue)
		{
			const auto currentTime = high_resolution_clock::now();
			const float deltaTime = duration<float>(currentTime - lastTime).count();
			GameTime::GetInstance().SetDeltaTime(deltaTime);
			lastTime = currentTime;
			lag += deltaTime;
			doContinue = input.ProcessInput();
			
			while(lag >= MsPerFrame)
			{
				//FixedUpdate(msPerUpdate)
				//
				lag -= MsPerFrame;
			}
			sceneManager.Update(); 
			renderer.Render();
			
			auto sleepTime = duration_cast<duration<float>>(currentTime + milliseconds(MsPerFrame) - high_resolution_clock::now());
			this_thread::sleep_for(sleepTime);
		}
	}

	Cleanup();
}
