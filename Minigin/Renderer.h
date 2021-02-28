#pragma once
#include "Singleton.h"

struct SDL_Window;
struct SDL_Renderer;

namespace dae
{
	class Texture2D;
	/**
	 * Simple RAII wrapper for the SDL renderer
	 */
	class Renderer final : public Singleton<Renderer>
	{
	public:
		void Init(SDL_Window* window);
		void Render();
		void Destroy();

		void RenderTexture(const Texture2D& texture, float x, float y) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;

		SDL_Renderer* GetSDLRenderer() const { return m_pRenderer; }

		void LogDebugText(const std::string& txt);
	private:
		int GetOpenGLDriverIndex();

		void RenderImGuiWindows();
		
		SDL_Renderer* m_pRenderer{};
		SDL_Window* m_pWindow{};
		bool m_ShowDemo{true};


		std::vector<std::string> m_LogText{"SmallFrogEngine: Start of debug log"};
	};
}

