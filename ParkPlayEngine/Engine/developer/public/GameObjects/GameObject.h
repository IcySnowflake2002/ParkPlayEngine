#pragma once
#include "CoreMinimal.h"
#include "PPTransform.h"

class AABBCollision;
class Model;
class Texture;

class GameObject {
public: //functions
	GameObject(PPTransform DefaultTransform) : Transform(DefaultTransform), Collider(nullptr), bShouldDestroy(false) {}
	~GameObject();

	//run on spawn
	virtual void BeginPlay() {}

	//run the logic for the gameobject
	virtual void Update(float DeltaTime);

	//get the collider of the game object
	AABBCollision* GetCollider() const { return Collider; }

	//this will run only if there is a collision and will run for each potential collision
	virtual void DetectCollisions(GameObject* OtherObject) {}

	//mark the gameobject for destroy/deletion from the game
	void DestroyObject() { bShouldDestroy = true; }

	//get whether the object should be destroyed from the game
	bool ShouldDestroy() const { return bShouldDestroy; }

public: //variables
	//location of the object in the world
	PPTransform Transform;

private: //functions


private: //variables
	bool bShouldDestroy;

protected: //functions
	//add a collider to the gameobject
	void AddCollider(glm::vec3 Size);

	//runs when the gameobject is destroyed
	virtual void OnDestroy() {}

	//Add a model as a game object
	Model* AddModel(PPString FilePath);

protected: //variables
	//collider for the object
	AABBCollision* Collider;

	//store a reference to the models that we use
	TArray<Model*> ModelsRef;
};