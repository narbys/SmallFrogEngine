#include "MiniginPCH.h"
#include "TextureComponent.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Texture2D.h"
#include "GameObject.h"

frog::TextureComponent::TextureComponent()
	:m_pTexture2D(nullptr)
{
}

frog::TextureComponent::TextureComponent(const std::string& filename, float width,float height)
	: m_Width(width),m_Height(height)
{
	SetTexture(filename);
}

frog::TextureComponent::~TextureComponent()
{
	delete m_pTexture2D;
	m_pTexture2D = nullptr;
}

void frog::TextureComponent::Update()
{
}

void frog::TextureComponent::Render() const
{
	//const auto pos = m_Transform.GetPosition();
	//Renderer::GetInstance().RenderTexture(*m_pTexture2D, pos.x, pos.y);
	//const auto pos = m_pTexture2D->GetSDLTexture()
	const auto & pos= m_pGameObject->GetTransform()->GetPosition();
	if (m_Width >0&& m_Height > 0)
		Renderer::GetInstance().RenderTexture(*m_pTexture2D, pos.x, pos.y,m_Width,m_Height);
	else
		Renderer::GetInstance().RenderTexture(*m_pTexture2D, pos.x, pos.y);
}

void frog::TextureComponent::SetTexture(const std::string& filename)
{
	if (m_pTexture2D != nullptr) delete m_pTexture2D;
	m_pTexture2D = ResourceManager::GetInstance().LoadTexture(filename);
}

void frog::TextureComponent::SetSize(float w, float h)
{
	m_Width = w;
	m_Height = h;
}
