#pragma once
#include "BaseComponent.h"
#pragma warning(push)
#pragma warning(disable : 4201)
#include "glm/glm.hpp"
#pragma warning(pop)
namespace dae
{
	class Texture2D;
	class TextureComponent final : public BaseComponent
	{
	public:
		TextureComponent();
		TextureComponent(const std::string& filename);
		TextureComponent(const std::string& filename,float x, float y, float width=0, float height=0);
		
		~TextureComponent();
		TextureComponent(const TextureComponent& other) = delete;
		TextureComponent(TextureComponent&& other) noexcept = delete;
		TextureComponent& operator=(const TextureComponent& other) = delete;
		TextureComponent& operator=(TextureComponent&& other) noexcept = delete;
		
		void Update() override;
		void Render() const override;
		void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);
		void SetSize(float w, float h);
	private:
		Texture2D* m_pTexture2D;
		float m_Width{}, m_Height{};
		glm::vec3 m_Position{};
	};
}