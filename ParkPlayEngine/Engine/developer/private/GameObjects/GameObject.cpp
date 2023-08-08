#include "GameObjects/GameObject.h"
#include "Game.h"
#include "GraphicsEngine.h"
#include "graphics/Model.h"
#include "physics/AABBCollision.h"

GameObject::~GameObject()
{
	//run child destroy functionality
	OnDestroy();

	//remove the collider if there is one
	if (Collider != nullptr)
		delete Collider;
	
	//remove any models from reference
	if (ModelsRef.size() > 0) {
		//loop through all the models
		for (Model* M : ModelsRef) {
			//remove each one from the graphics engine
			Game::GetGameInstance()->RemoveModelFromGraphics(M);
		}

		ModelsRef.clear();
	}
}

void GameObject::Update(float DeltaTime)
{
	//if there is a collider set its origin to the game object
	if (Collider != nullptr)
		Collider->Update(Transform.Location);

	//If there are any models move them to the same position as the game object
	for (Model* M : ModelsRef) {
		M->Transform = Transform;
	}
}

void GameObject::AddModel(PPString FilePath)
{
	Model* M = Game::GetGameInstance()->Import3DModel(FilePath);

	ModelsRef.push_back(M);
}

void GameObject::AddCollider(glm::vec3 Size)
{
	//if there is no collider create one
	if (Collider == nullptr)
		Collider = new AABBCollision(Transform.Location, Size);
	//if there is already a collider then just adjust its size
	else
		Collider->SetHalfSize(Size);
}
