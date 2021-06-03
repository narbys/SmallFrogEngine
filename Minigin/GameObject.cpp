#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
frog::GameObject::GameObject(const std::vector<BaseComponent*>& pComponents)
	: m_pTransform(new TransformComponent(0,0,0)), m_pComponents(pComponents)
{
}

frog::GameObject::~GameObject()
{
	//Remove all components when object is destroyed
	for(auto* pComponent : m_pComponents) 
	{
		delete pComponent;
		pComponent = nullptr;
	}
	delete m_pTransform;
}

void frog::GameObject::Update()
{
	//update it's components or core aspects of the GameObject
	for (auto* pCo : m_pComponents)
	{
		pCo->Update();
	}
}

void frog::GameObject::Render() const
{
	//Go through it's components and call their render
	for(auto* pCo : m_pComponents)
	{
		pCo->Render();
	}
	
	//const auto pos = m_Transform.GetPosition();
	//Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
}

frog::BaseComponent* frog::GameObject::AddComponent(BaseComponent* pComponent)
{
	pComponent->SetOwner(this);
	m_pComponents.push_back(pComponent);
	return pComponent;
}

frog::TransformComponent* frog::GameObject::GetTransform() const
{
	return m_pTransform;
}

//void frog::GameObject::SetPosition(float x, float y)
//{
//	m_Transform.SetPosition(x, y, 0.0f);
//}
