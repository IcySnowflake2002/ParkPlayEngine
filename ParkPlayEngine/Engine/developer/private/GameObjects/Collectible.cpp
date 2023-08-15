#include "GameObjects/Collectible.h"
#include "graphics/Model.h"
#include "graphics/Material.h"
#include "graphics/Texture.h"
#include "Game.h"
#include "GameObjects/Player.h"

void Collectible::BeginPlay()
{
	Model* M = AddModel("Engine/developer/models/damaged_wall/SM_Wall_Damaged_2x1_A.obj");
	Texture* T = Game::GetGameInstance()->GetOrCreateTexture("Engine/developer/textures/default_texBLU.png");
	M->SetTextureByMaterial(0, ETEXTYPES::BaseColor, T);

	ActiveTexture = Game::GetGameInstance()->GetOrCreateTexture("Engine/developer/textures/default_texGRN.png");

	AddCollider(glm::vec3(1.0f));
}

void Collectible::DetectCollisions(GameObject* OtherObject)
{
	if (dynamic_cast<Player*>(OtherObject)) {
		Activate();
	}
}

void Collectible::Activate()
{
	if (bActivated)
		return;

	bActivated = true;

	ModelsRef[0]->SetTextureByMaterial(0, ETEXTYPES::BaseColor, ActiveTexture);
}
