#pragma once
//AABB = Access Aligned Bounding Box
#include "CoreMinimal.h"
#include "PPTransform.h"

class AABBCollision {
public: //functions
	AABBCollision(glm::vec3 Origin, glm::vec3 HalfSize) : Origin(Origin), HalfSize(HalfSize) {}

	static bool IsIntersecting(const AABBCollision& Col1, const AABBCollision& Col2);

	void Update(glm::vec3 NewOrigin) { Origin = NewOrigin; }

	void SetHalfSize(glm::vec3 NewSize) { HalfSize = NewSize; }

	//highest vector within the box
	glm::vec3 Max() const;

	//lowest vector within the box
	glm::vec3 Min() const;

public: //variables


private: //functions


private: //variables


protected: //functions


protected: //variables
	//location/origin/center of the box
	glm::vec3 Origin;
	//box extent
	glm::vec3 HalfSize;
};

