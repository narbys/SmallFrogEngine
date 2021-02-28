#include "MiniginPCH.h"
#include "SmallFrog.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>


#include "Command.h"
#include "FPSComponent.h"
#include "TextComponent.h"
#include "GameObject.h"
#include "Scene.h"
#include "TextureComponent.h"
#include "Time.h"

using namespace std;
using namespace std::chrono;

void dae::SmallFrog::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

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
}

/**
 * Code constructing the scene world starts here
 */
void dae::SmallFrog::LoadGame()
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	//Background
	auto go = new GameObject();
	go->AddComponent(new TextureComponent{ "background.jpg" });
	scene.Add(go);
	
	//Logo
	go = new GameObject();
	go->AddComponent(new TextureComponent{ "logo.png",100,180,500,100 });
	scene.Add(go);
	
	//Title
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	go = new GameObject();
	go->AddComponent(new TextComponent("Small frogs are cute", font));
	go->GetComponent<TextComponent>()->SetPosition(150, 20);
	scene.Add(go);

	//FPS counter
	go = new GameObject();
	go->AddComponent(new FPSComponent());
	go->AddComponent(new TextComponent("null", font));
	scene.Add(go);

	//Initialise Q*Bert
	m_pQBert = new GameObject();
	m_pQBert->AddComponent(new TextureComponent( "qbert.jpg", 100,100, 50,50));
	scene.Add(m_pQBert);

	//Input
	InputManager::GetInstance().BindCommand(VK_PAD_A, new BeepboopCommand());
	
}

void dae::SmallFrog::Cleanup()
{	
	//End
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void dae::SmallFrog::Run()
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
			Time::GetInstance().SetDeltaTime(deltaTime);
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
