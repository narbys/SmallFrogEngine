#include "MiniginPCH.h"
#include "Renderer.h"
#include <SDL.h>

#pragma warning (disable : 26812)
#pragma warning (push)
#include "imgui.h"
#pragma warning (pop)

#include "SceneManager.h"
#include "Texture2D.h"
#include "backends/imgui_impl_opengl2.h"
#include "backends/imgui_impl_sdl.h"


void dae::Renderer::Init(SDL_Window * window)
{
	m_pWindow = window;
	m_pRenderer = SDL_CreateRenderer(window, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_pRenderer == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(window, SDL_GL_GetCurrentContext());
	ImGui_ImplOpenGL2_Init();
}

void dae::Renderer::Render()
{
	SDL_RenderClear(m_pRenderer);

	SceneManager::GetInstance().Render();

	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplSDL2_NewFrame(m_pWindow);
	ImGui::NewFrame();

	//Render ImGui
	//
	//if (m_ShowDemo)
		//ImGui::ShowDemoWindow(&m_ShowDemo);
	RenderImGuiWindows();

	
	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
	
	SDL_RenderPresent(m_pRenderer);
}

void dae::Renderer::Destroy()
{
	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
	
	if (m_pRenderer != nullptr)
	{
		SDL_DestroyRenderer(m_pRenderer);
		m_pRenderer = nullptr;
	}
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void dae::Renderer::LogDebugText(const std::string& txt)
{
	m_LogText.push_back(txt);
}

int dae::Renderer::GetOpenGLDriverIndex()
{
	auto openglIndex = 1;
	const auto  driverCount = SDL_GetNumRenderDrivers();
	for(auto i = 0; i < driverCount; ++i)
	{
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(i, &info))
			if (!strcmp(info.name, "opengl"))
				openglIndex = i;
	}
	return openglIndex;
}

void dae::Renderer::RenderImGuiWindows()
{
	//todo: make proper debug log window
	ImGui::Begin("DebugLog");
	if (ImGui::Button("Clear"))
		m_LogText.clear();
	ImGui::BeginChild("Scrolling");
	const size_t loglines = m_LogText.size();
	for (int n = 0; n < loglines; n++)
		ImGui::Text("%04d: %s", n, m_LogText[n].c_str());
	ImGui::EndChild();
	ImGui::End();

	//todo: make window with 3 buttons as requested
	
}
