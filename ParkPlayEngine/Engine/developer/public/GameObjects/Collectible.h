#pragma once
#include "CoreMinimal.h"
#include "GameObjects/GameObject.h"

class Collectible : public GameObject {
public: //functions
	Collectible(PPTransform Transform) : GameObject(Transform) {}

	virtual void BeginPlay() override;

public: //variables


private: //functions


private: //variables


protected: //functions


protected: //variables


};