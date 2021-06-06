#pragma once
#include <string>
#include <glm/detail/type_vec.hpp>
#include <glm/detail/type_vec3.hpp>

struct LevelData
{
	int Config;
	glm::vec3 StartPos;
	std::string InactiveImage;
	std::string ActiveImage;
	std::string ActiveImage2;
};
