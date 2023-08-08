#include "physics/AABBCollision.h"

bool AABBCollision::IsIntersecting(const AABBCollision& Col1, const AABBCollision& Col2)
{
	bool X = Col1.Min().x <= Col2.Max().x && Col1.Max().x >= Col2.Min().x;
	bool Y = Col1.Min().y <= Col2.Max().y && Col1.Max().y >= Col2.Min().y;
	bool Z = Col1.Min().z <= Col2.Max().z && Col1.Max().z >= Col2.Min().z;

	return X && Y && Z;
}

glm::vec3 AABBCollision::Max() const
{
	return Origin + HalfSize;
}

glm::vec3 AABBCollision::Min() const
{
	return Origin - HalfSize;
}
