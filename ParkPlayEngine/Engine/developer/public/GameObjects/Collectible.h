#pragma once
#include "CoreMinimal.h"
#include "GameObjects/GameObject.h"

class Collectible : public GameObject {
public: //functions
	Collectible(PPTransform Transform) : GameObject(Transform), bActivated(false), ActiveTexture(nullptr) {}

	virtual void BeginPlay() override;

	virtual void DetectCollisions(GameObject* OtherObject) override;

	void Activate(); 

public: //variables


private: //functions


private: //variables


protected: //functions


protected: //variables
	bool bActivated;

	Texture* ActiveTexture;

};