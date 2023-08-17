#pragma once
#include "CoreMinimal.h"
#include "PPTransform.h"
#include "SDL2/SDL_mixer.h"

class GraphicsEngine;
class Texture;
class Input;
class ShaderProgram;
class Model;
class DirLight;
class PointLight;
class GameObject;
class Collectible;
class Camera;
class Player;

class Game {

public: //functions
	//create a game instance or return the one we already created
	static Game* GetGameInstance();

	//destroy the game instance
	static void DestroyGameInstance();

	//Start/run the application/game loop
	void Run();
	
	//Close the whole app
	void CloseGame();

	// Get the default Texture for objects
	Texture* GetEngineTexture(EENGINETEX EngineTex) const;

	//import 3D Model to the graphics engine
	Model* Import3DModel(PPString& FilePath);

	//get the default shader for objects
	ShaderProgram* GetDefaultShader() const;

	//Super accurate DeltaTime
	double GetDeltaTime() const { return DeltaTime; }

	//Less Accurate DeltaTime
	float GetDeltaTimeF() const { return static_cast<float>(DeltaTime); }

	//Get input for the game
	Input* GetGameInput() const { return GameInput; }

	//create a directional light and render it in the graphics
	DirLight* CreateDirLight(glm::vec3 Ambience = glm::vec3(0.0f), glm::vec3 Colour = glm::vec3(1.0f)) const;

	//create a point light and render it in the graphics
	PointLight* CreatePointLight(float Attenuation, glm::vec3 Colour = glm::vec3(1.0f), bool bDebug = false);

	//removes a model from the graphics engine
	void RemoveModelFromGraphics(Model* ModelRef);

	//set the current engine camera
	void SetCurrentCamera(TSharedPtr<Camera> NewCamera);

	//show or hide the mouse cursor
	void SetCursorVisible(bool bVisible);

	//create or get a texture from the graphics engine
	Texture* GetOrCreateTexture(PPString FilePath);

	//add a game object to the game object stack
	GameObject* AddGameObjectToGame(GameObject* NewGameObject);

public: //variables


private: //functions
	Game();
	~Game();

	//when the app first loads
	//we will initalise all required dependencies
		//if they fail, close the app
	bool Initialise();

	//runs at the start of play (after initialisation)
	void BeginPlay();

	//listen and detect for input
	void ProcessInput();

	//handle the games logic
	void Update();

	//render graphics to the screen
	void Draw();

	//delete all objects that are listed for deletion
	void GarbageCollection();

	//Uninitialise and delete all memory
	void CleanUpGame();


private: //variables

	//if false game runs, if true game closes
	bool bIsGameOver;

	//hold the graphics engine
	GraphicsEngine* Graphics;

	//store the BGM music
	Mix_Music* SSBGM;

	//the time between each frame
	double DeltaTime;

	//timer for the race
	float GameTimer;

	//holds the input logic for the game (using SDL2)
	Input* GameInput;

	//GameObjects
	TArray<GameObject*> GameObjectStack;
};