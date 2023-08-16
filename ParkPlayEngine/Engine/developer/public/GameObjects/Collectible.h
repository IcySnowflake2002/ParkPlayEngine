#pragma once
#include "CoreMinimal.h"
#include "GameObjects/GameObject.h"

class Collectible : public GameObject {
public: //functions
	Collectible(PPTransform Transform, int Order);

	virtual void BeginPlay() override;

	virtual void DetectCollisions(GameObject* OtherObject) override;

	//Checkpoint System
	void SetNextCollectible(Collectible* OtherCollectible) { this->OtherCollectible = OtherCollectible; }

	void ReadyNextCollectible();

public: //variables


private: //functions


private: //variables


protected: //functions
	void Activate();

protected: //variables
	//check if the collectible has been activated
	bool bActivated;

	//check if the collectible is ready
	bool bIsActive;

	//Order of collectibles
	int Order;

	//texture pointers
	Texture* ActiveTexture;
	Texture* CollectedTexture;
	Texture* FinishedTexture;

	Collectible* OtherCollectible;
};