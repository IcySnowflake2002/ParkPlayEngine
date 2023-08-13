#include "GameObjects/Ring.h"

void Ring::BeginPlay()
{
	AddModel("Engine/developer/models/ring_gltf/scene.gltf");
	AddCollider(glm::vec3(1.0f));
}
