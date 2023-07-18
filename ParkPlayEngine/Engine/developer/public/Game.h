#pragma once

class GraphicsEngine;
class Texture;
class Input;
class ShaderProgram;
class Model;

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
	Texture* GetDefaultTexture() const;

	//get the default shader for objects
	ShaderProgram* GetDefaultShader() const;

	//Super accurate DeltaTime
	double GetDeltaTime() const { return DeltaTime; }

	//Less Accurate DeltaTime
	float GetDeltaTimeF() const { return static_cast<float>(DeltaTime); }

	//Get input for the game
	Input* GetGameInput() const { return GameInput; }

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

	//Uninitialise and delete all memory
	void CleanUpGame();

private: //variables

	//if false game runs, if true game closes
	bool bIsGameOver;

	//hold the graphics engine
	GraphicsEngine* Graphics;

	//the time between each frame
	double DeltaTime;

	//holds the input logic for the game (using SDL2)
	Input* GameInput;

	//Models
	Model* Cube1;
	Model* Cube2;
	Model* Wall;
	Model* Ring;
};