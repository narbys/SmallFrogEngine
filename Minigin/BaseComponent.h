#pragma once
namespace frog
{
	class GameObject;
	class Subject;
	class BaseComponent
	{
	public:
		BaseComponent();
		virtual ~BaseComponent();
		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) noexcept = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) noexcept = delete;

		virtual void Update() = 0;
		virtual void Render() const {}
		void SetOwner(GameObject* pGo) { m_pGameObject = pGo; }
		Subject* GetSubject() const { return m_pSubject; }
	protected:
		GameObject* m_pGameObject{};
		Subject* m_pSubject;
	private:
	};
}

