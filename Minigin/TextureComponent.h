#pragma once
#include "BaseComponent.h"
namespace dae
{
	class Texture2D;
	class TextureComponent final : public BaseComponent
	{
	public:
		TextureComponent();
		TextureComponent(const std::string& filename);
		TextureComponent(const std::string& filename,float x, float y, float width, float height);
		
		~TextureComponent();
		TextureComponent(const TextureComponent& other) = delete;
		TextureComponent(TextureComponent&& other) noexcept = delete;
		TextureComponent& operator=(const TextureComponent& other) = delete;
		TextureComponent& operator=(TextureComponent&& other) noexcept = delete;
		
		void Update() override;
		void Render() const override;
		void SetTexture(const std::string& filename);
	private:
		Texture2D* m_pTexture2D;
		float m_X{}, m_Y{}, m_Width{}, m_Height{};
	};
}