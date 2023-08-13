#include "GameObjects/Ring.h"

void Ring::BeginPlay()
{
	AddModel("Engine/developer/models/ring_gltf/scene.gltf");
	AddCollider(glm::vec3(1.0f));
	Transform.Scale *= 0.1;
	Transform.Rotation = glm::vec3(90.0f, 0.0f, 0.0f);
}
