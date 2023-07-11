#pragma once
#include "GLM/glm.hpp"

//the general up direction of the world
#define WORLD_UP glm::vec3(0.0f, 1.0f, 0.0f)


struct PPDirection {

	PPDirection(glm::vec3 Rotation) {

		//determine the cosine and sine values of the rotation
		float CosX = cos(glm::radians(Rotation.x));
		float CosY = cos(glm::radians(Rotation.y));
		float SinX = sin(glm::radians(Rotation.x));
		float SinY = sin(glm::radians(Rotation.y));
		
		// find the vector using the axis angles
		Forward.x = CosY * CosX;
		Forward.y = SinX;
		Forward.z = SinY * CosX;

		//normalise the forward to make sure the values sat between 1 and -1
		//we need to normalise direction values to make sure they don't consider distance
		Forward = glm::normalize(Forward);
		
		//cross product gives the axis perpendicular to two given axes
		Right = glm::normalize(glm::cross(Forward, WORLD_UP));
		
		//the local up direction for the camera
		Up = glm::normalize(glm::cross(Right, Forward));

	}


	glm::vec3 Forward;
	glm::vec3 Right;
	glm::vec3 Up;
};


struct PPTransform {
	PPTransform() {
		Location = glm::vec3(0.0f);
		Rotation = glm::vec3(0.0f);
		Scale = glm::vec3(1.0f);
	}

	//Get all three directions
	PPDirection GetDirections() {
		return PPDirection(Rotation);
	}

	//Get the forward vector based on the rotation
	glm::vec3 GetForward() {
		return PPDirection(Rotation).Forward;
	}

	//get the right vector based on the rotation
	glm::vec3 GetRight() {
		return PPDirection(Rotation).Right;
	}

	//get the up vector based on the rotation
	glm::vec3 GetUp() {
		return PPDirection(Rotation).Up;
	}

	glm::vec3 Location;
	glm::vec3 Rotation;
	glm::vec3 Scale;
};