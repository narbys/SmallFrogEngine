#pragma once
#include "Singleton.h"

#pragma warning (disable : 26812)
#pragma warning (push)
#include "../3rdParty/imgui-1.81/imgui.h"
#pragma warning (pop)

struct SDL_Window;
struct SDL_Renderer;

namespace frog
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

		void LogDebugText(const std::string& txt, const ImVec4& col={1,1,1,1});
	private:
		int GetOpenGLDriverIndex();

		void RenderImGuiWindows();
		
		SDL_Renderer* m_pRenderer{};
		SDL_Window* m_pWindow{};

		//ImGui window bools
		bool m_ShowDemo{true};
		bool m_DebugLogOpen{ true };
		bool my_tool_active{ true };
		
		//Debug Log variables
		struct colorText
		{
			std::string text;
			ImVec4 color = { 1,1,1,1 };
		};
		std::vector<colorText> m_LogText{ {"SmallFrogEngine: Start of debug log"} };
	};
}

