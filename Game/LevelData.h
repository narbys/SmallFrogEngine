#pragma once
#include <string>
#include <glm/detail/type_vec.hpp>
#include <glm/detail/type_vec3.hpp>

struct LevelData
{
	glm::vec3 StartPos;
	std::string InactiveImage;
	std::string ActiveImage;
};
