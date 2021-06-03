#include "MiniginPCH.h"
#include "Renderer.h"
#include <SDL.h>

#pragma warning (disable : 26812)
#pragma warning (disable : 4189)
#pragma warning (push)
//#include "imgui.h"
#include "backends/imgui_impl_opengl2.h"
#include "backends/imgui_impl_sdl.h"
#pragma warning (pop)

#include "SceneManager.h"
#include "Texture2D.h"


void frog::Renderer::Init(SDL_Window * window)
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

void frog::Renderer::Render()
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
#ifdef  _DEBUG
	RenderImGuiWindows();
#endif
	
	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
	
	SDL_RenderPresent(m_pRenderer);
}

void frog::Renderer::Destroy()
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

void frog::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void frog::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void frog::Renderer::LogDebugText(const std::string& txt, const ImVec4& col)
{
	if (!m_DebugLogOpen)
		m_DebugLogOpen = true;
	m_LogText.push_back({ txt,col });
}

int frog::Renderer::GetOpenGLDriverIndex()
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

void frog::Renderer::RenderImGuiWindows()
{
	//debug log window
	if (m_DebugLogOpen)
	{
		ImGui::Begin("DebugLog", &m_DebugLogOpen);
		if (ImGui::Button("Clear"))
			m_LogText.clear();
		ImGui::BeginChild("Scrolling");
		const size_t loglines = m_LogText.size();
		for (size_t n = 0; n < loglines; n++)
			ImGui::TextColored(m_LogText[n].color , "%04d: %s", n, m_LogText[n].text.c_str());
		ImGui::EndChild();
		ImGui::End();
	}
	
	//window with 3 buttons as requested
	ImGui::Begin("Buttons");
	if (ImGui::Button("Easy"))
		LogDebugText("Easy mode",{0,1,0,1});
	if (ImGui::Button("Normal"))
		LogDebugText("Normal mode",{0,0,1,1});
	if (ImGui::Button("Hard"))
		LogDebugText("Hard mode",{1,0,0,1});
	ImGui::End();
}
