#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

void frog::SceneManager::Update()
{
	for(auto& scene : m_Scenes)
	{
		scene->Update();
	}
}

void frog::SceneManager::Render()
{
	for (const auto& scene : m_Scenes)
	{
		scene->Render();
	}
}

frog::Scene& frog::SceneManager::CreateScene(const std::string& name)
{
	const auto scene = std::shared_ptr<Scene>(new Scene(name));
	m_Scenes.push_back(scene);
	return *scene;
}
