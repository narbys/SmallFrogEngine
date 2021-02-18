#include "MiniginPCH.h"
#include "TextureComponent.h"


#include "Renderer.h"
#include "ResourceManager.h"
#include "Texture2D.h"

dae::TextureComponent::TextureComponent()
	:m_pTexture2D(nullptr)
{
}

dae::TextureComponent::TextureComponent(const std::string& filename)
{
	SetTexture(filename);
}

dae::TextureComponent::TextureComponent(const std::string& filename, float x, float y, float width,float height)
	: m_X{x},m_Y{y},m_Width(width),m_Height(height)
{
	SetTexture(filename);
}

dae::TextureComponent::~TextureComponent()
{
	delete m_pTexture2D;
	m_pTexture2D = nullptr;
}

void dae::TextureComponent::Update()
{
}

void dae::TextureComponent::Render() const
{
	//const auto pos = m_Transform.GetPosition();
	//Renderer::GetInstance().RenderTexture(*m_pTexture2D, pos.x, pos.y);
	//const auto pos = m_pTexture2D->GetSDLTexture()
	if (m_Width >0&& m_Height > 0)
		Renderer::GetInstance().RenderTexture(*m_pTexture2D, m_X, m_Y,m_Width,m_Height);
	else
		Renderer::GetInstance().RenderTexture(*m_pTexture2D, m_X, m_Y);
}

void dae::TextureComponent::SetTexture(const std::string& filename)
{
	m_pTexture2D = ResourceManager::GetInstance().LoadTexture(filename);
}
