#include "GameObjects/Cloud.h"
#include "Game.h"
#include "graphics/Texture.h"
#include "graphics/Model.h"
#include "graphics/Material.h"

Cloud::Cloud(PPTransform DefaultTransform)
{

}

void Cloud::BeginPlay()
{
	Model* M = AddModel("Engine/developer/models/clouds/cloud.obj");

	Texture* T = Game::GetGameInstance()->GetOrCreateTexture("Engine/developer/models/clouds/cloud.obj.mtl");
	M->SetTextureByMaterial(1, ETEXTYPES::BaseColor, T);
}
