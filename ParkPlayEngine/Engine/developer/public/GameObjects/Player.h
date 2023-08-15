#pragma once
#include "CoreMinimal.h"
#include "GameObjects/GameObject.h"

class Input;
class Camera;

class Player : public GameObject {
public: //functions
	Player(PPTransform DefaultTransform);

	//this will listen for player input
	virtual void ProcessInput(Input* GameInput);

	virtual void BeginPlay() override;

	virtual void Update(float DeltaTime) override;

public: //variables


private: //functions


private: //variables


protected: //functions


protected: //variables
	//the camera the player will look through
	TSharedPtr<Camera> PlayerCamera;

	//the move direction of the player's input
	glm::vec3 MovementAxis;

	//speed of movement
	float Speed;

	//rotation variables
	float PitchInput, YawInput;
};