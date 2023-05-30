#pragma once

class GraphicsEngine;

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

public: //variables


private: //functions
	Game();
	~Game();

	//when the app first loads
	//we will initalise all required dependencies
		//if they fail, close the app
	bool Initialise();


	//listen and detect for input
	void ProcessInput();

	//handle the games logic
	void Update();

	//render graphics to the screen
	void Draw();

	//Uninitialise and delete all memory
	void CleanUpGame();

private: //variables

	//Check if game is over
	bool bIsGameOver;

	//hold the graphics engine
	GraphicsEngine* Graphics;

};