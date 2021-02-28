#pragma once
struct SDL_Window;


namespace dae
{
	class GameObject;
	
	class SmallFrog
	{
	public:
		void Initialize();
		void LoadGame();
		void Cleanup();
		void Run();
	private:
		static const int MsPerFrame = 16; //16 for 60 fps, 33 for 30 fps
		SDL_Window* m_Window{};

		//GAMEOBJECTS
		GameObject* m_pQBert{};
	};
}