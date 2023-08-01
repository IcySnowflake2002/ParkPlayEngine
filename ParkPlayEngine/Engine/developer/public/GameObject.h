#pragma once
#include "CoreMinimal.h"
#include "PPTransform.h"

class GraphicsEngine;
class Texture;
class Model;

class GameObject {
public: //functions
	GameObject();
	virtual ~GameObject();

	//virtual void ProcessInput(Input* PlayerInput) {}

	//Draw the Objects
	virtual void Draw() {};
	//Run the logic of the object
	virtual void Update();

public: //variables

	// Keep Track of transformations
	PPTransform Transforms;

private: //functions


private: //variables

	// If set the game will destroy the object
	bool bShouldDestroy;

protected: //functions


protected: //variables


};