#pragma once
#include "TransformComponent.h"
//#include "SceneObject.h"
#include <vector>

#include "BaseComponent.h"
#include "Subject.h"

namespace frog
{
	//class BaseComponent;
	//class Texture2D;
	class GameObject final
	{
	public:
		//GameObject() = default;
		GameObject(const std::vector<BaseComponent*>& pComponents={});
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void Update();
		void Render() const;
		BaseComponent* AddComponent(BaseComponent* pComponent);

		//Getters
		TransformComponent* GetTransform() const;
		
		//Setters
		//void SetPosition(float x, float y);
		
		//Template Functions
		template <typename T>
		T* GetComponent() const;
	private:
		TransformComponent* m_pTransform;
		std::vector<BaseComponent*> m_pComponents;
	};
	
	template<typename T>
	inline T* GameObject::GetComponent() const
	{
		for (auto* component : m_pComponents)
		{
			T* pCom = dynamic_cast<T*>(component);
			if(pCom)
				return pCom;
		}
		return nullptr;
	}
}
