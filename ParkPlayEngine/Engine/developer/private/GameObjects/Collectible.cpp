#include "GameObjects/Collectible.h"

void Collectible::BeginPlay()
{
	AddModel("Engine/developer/models/PrimitiveModels/Sphere.fbx");
	AddCollider(glm::vec3(1.0f));
}
