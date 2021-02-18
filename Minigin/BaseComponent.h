#pragma once
namespace dae
{
	class GameObject;
	class BaseComponent
	{
	public:
		BaseComponent() = default;
		virtual ~BaseComponent() = default;
		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) noexcept = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) noexcept = delete;

		virtual void Update() = 0;
		virtual void Render() const {}
		void SetOwner(GameObject* pGo) { m_pGameObject = pGo; }
	protected:
		GameObject* m_pGameObject{};
	private:
	};
}

