#pragma once
#include "CoreMinimal.h"
#include "PPTransform.h"

class AABBCollision;
class Model;
class Texture;

class GameObject {
public: //functions
	GameObject(PPTransform DefaultTransform) : Transform(DefaultTransform), Collider(nullptr) {}
	~GameObject();

	//run on spawn
	virtual void BeginPlay() {}

	//run the logic for the gameobject
	virtual void Update(float DeltaTime);

	//get the collider of the game object
	AABBCollision* GetCollider() const { return Collider; }

	//Add a model as a game object
	void AddModel(PPString FilePath);

public: //variables
	//location of the object in the world
	PPTransform Transform;

private: //functions


private: //variables


protected: //functions
	//add a collider to the gameobject
	void AddCollider(glm::vec3 Size);

	//runs when the gameobject is destroyed
	virtual void OnDestroy() {}

protected: //variables
	//collider for the object
	AABBCollision* Collider;

	//store a reference to the models that we use
	TArray<Model*> ModelsRef;
};