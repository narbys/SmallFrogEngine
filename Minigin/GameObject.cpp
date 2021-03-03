#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
dae::GameObject::GameObject(const std::vector<BaseComponent*>& pComponents)
	: m_pComponents(pComponents)
{
}

dae::GameObject::~GameObject()
{
	//Remove all components when object is destroyed
	for(auto* pComponent : m_pComponents) 
	{
		delete pComponent;
		pComponent = nullptr;
	}
}

void dae::GameObject::Update()
{
	//update it's components or core aspects of the GameObject
	for (auto* pCo : m_pComponents)
	{
		pCo->Update();
	}
}

void dae::GameObject::Render() const
{
	//Go through it's components and call their render
	for(auto* pCo : m_pComponents)
	{
		pCo->Render();
	}
	
	//const auto pos = m_Transform.GetPosition();
	//Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
}

dae::BaseComponent* dae::GameObject::AddComponent(BaseComponent* pComponent)
{
	pComponent->SetOwner(this);
	m_pComponents.push_back(pComponent);
	return pComponent;
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}
