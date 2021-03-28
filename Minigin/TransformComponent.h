#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#pragma warning (disable:4616)
#include <glm/glm.hpp>
#pragma warning(pop)
namespace dae
{
	class TransformComponent final
	{
	public:
		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(float x, float y, float z);
	private:
		glm::vec3 m_Position;
	};
}
