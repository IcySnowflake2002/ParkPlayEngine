#pragma once
#include "CoreMinimal.h"
#include "GameObject.h"

class Ring : public GameObject {
public: //functions
	Ring(PPTransform Transform) : GameObject(Transform) {}

	virtual void BeginPlay() override;

public: //variables


private: //functions


private: //variables


protected: //functions


protected: //variables

};