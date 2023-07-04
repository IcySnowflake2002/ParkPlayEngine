#pragma once

#pragma once
#include "CoreMinimal.h"
#include "PPTransform.h"


class Camera {
public: //functions
	Camera(float x = 0.0f, float y = 0.0f, float z = 0.0f);
	~Camera();

	//Game logic for the camera
	void Update();

public: //variables
	float FOV; //field of view

	// closest that a 3D object can render on the camera
	float NearClip;

	// furtherest that a 3D object can render on the camera
	float FarClip;

	//location, transformation and rotation in the world space
	PPTransform Transform;
	
	//Speed the camera moves at
	float Speed;

private: //functions


private: //variables

};