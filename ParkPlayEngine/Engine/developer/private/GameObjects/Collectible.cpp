#include "GameObjects/Collectible.h"
#include "graphics/Model.h"
#include "graphics/Material.h"
#include "graphics/Texture.h"
#include "Game.h"
#include "GameObjects/Player.h"
#include "SDL2/SDL_mixer.h"

Collectible::Collectible(PPTransform Transform, int Order)
	: GameObject(Transform)
{
	bActivated = false; 
	bIsActive = false;
	ActiveTexture = nullptr;
	CollectedTexture = nullptr;
	this->Order = Order;
}

void Collectible::BeginPlay()
{
	Model* M = AddModel("Engine/developer/models/ring/ring basic.obj");

	//initalise audio
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == 1) {
		PP_MSG_ERR("Collectible", "SDL_Mixer failed to initialise");
		return;
	}

	//Preset transforms
	Transform.Scale = glm::vec3(0.010f);

	//Not Ready Yet
	Texture* T = Game::GetGameInstance()->GetOrCreateTexture("Engine/developer/textures/red.png");
	M->SetTextureByMaterial(1, ETEXTYPES::BaseColor, T);

	//Next Collectible
	ActiveTexture = Game::GetGameInstance()->GetOrCreateTexture("Engine/developer/textures/ylw.png");

	//Already Collected
	CollectedTexture = Game::GetGameInstance()->GetOrCreateTexture("Engine/developer/textures/grn.png");
	
	//If it's already set to "not collected" and is next in the sequence, ready it for collection
	if (Order == 0)
		ReadyNextCollectible();

	AddCollider(glm::vec3(1.0f));
}

void Collectible::DetectCollisions(GameObject* OtherObject)
{
	if (!bIsActive)
		return;

	if (dynamic_cast<Player*>(OtherObject)) {
		Activate();
	}
}

void Collectible::Activate()
{
	if (bActivated)
		return;

	bActivated = true;

	ModelsRef[0]->SetTextureByMaterial(1, ETEXTYPES::BaseColor, CollectedTexture);
	//play sound effect

	sfx_Collect[0] = Mix_LoadWAV("Engine/developer/audio/collect.wav");

	if (sfx_Collect[0] == NULL)
		PP_MSG_ERR("Collectible", "Couldn't load sfx");

	Mix_VolumeChunk(sfx_Collect[0], 100);

	if (OtherCollectible != nullptr) {
		OtherCollectible->ReadyNextCollectible();
	}
	else {
		Game::GetGameInstance()->CloseGame();
	}

}

void Collectible::ReadyNextCollectible()
{
	ModelsRef[0]->SetTextureByMaterial(1, ETEXTYPES::BaseColor, ActiveTexture);
	bIsActive = true;
}
