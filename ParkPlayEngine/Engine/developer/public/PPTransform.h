#pragma once
#include "GLM/glm.hpp"

struct PPTransform {
	PPTransform() {
		Location = glm::vec3(0.0f);
		Rotation = glm::vec3(0.0f);
		Scale = glm::vec3(1.0f);
	}

	glm::vec3 Location;
	glm::vec3 Rotation;
	glm::vec3 Scale;
};