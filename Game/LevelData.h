#pragma once
#include <string>
#pragma warning(push)
#pragma warning(disable:4201)
#include <glm/glm.hpp>
//#include <glm/detail/type_vec3.hpp>
#pragma warning(pop)

struct LevelData
{
	int Config;
	glm::vec3 StartPos;
	std::string InactiveImage;
	std::string ActiveImage;
	std::string ActiveImage2;
};
