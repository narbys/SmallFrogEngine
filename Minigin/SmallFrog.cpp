#include "MiniginPCH.h"
#include "SmallFrog.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>

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
void dae::SmallFrog::LoadGame() const
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	auto go = new GameObject();
	go->AddComponent(new TextureComponent{ "background.jpg" });
	//go->GetComponent<TextureComponent>()->SetTexture("logo.png");
	scene.Add(go);

	go = new GameObject();
	go->AddComponent(new TextureComponent{ "logo.png",100,180,500,100 });
	//go->SetTexture("logo.png");
	//go->SetPosition(216, 180);
	scene.Add(go);

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	
	go = new GameObject();
	go->AddComponent(new TextComponent("Small frogs are cute", font));
	go->GetComponent<TextComponent>()->SetPosition(150, 20);
	scene.Add(go);

	//auto to = std::make_shared<TextComponent>("Programming 4 Assignment", font);
	//to->SetPosition(80, 20);
	//scene.Add(to);
	go = new GameObject();
	go->AddComponent(new FPSComponent());
	go->AddComponent(new TextComponent("null", font));
	scene.Add(go);
	
}

void dae::SmallFrog::Cleanup()
{
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
			
			//auto sleepTime = duration_cast<duration<float>>(currentTime + milliseconds(MsPerFrame) - high_resolution_clock::now());
			//this_thread::sleep_for(sleepTime);
		}
	}

	Cleanup();
}
