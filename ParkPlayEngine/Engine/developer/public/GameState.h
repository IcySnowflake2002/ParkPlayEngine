#pragma once
#include "CoreMinimal.h"
#include "PPTransform.h"

struct SDL_Renderer;
struct SDL_Window;
class GameObject;
class GraphicsEngine;
class Input;

class GameState {
public: //functions
	GameState(SDL_Renderer* Renderer, SDL_Window* Window);
	~GameState();

	//Game Loop functions for the current state
	virtual void ProcessInput(Input* PlayerInput);
	virtual void Update(float DeltaTime);
	virtual void Draw(SDL_Renderer* Renderer);

	//Add objects/Models into the game
	void Instantiate();
	void HandleGarbage();

	//State Updates
	virtual void BeginState();
	virtual void EndState();

	//get the current Renderer and window of the state
	SDL_Renderer* GetRenderer() const { return StateRenderer; }
	SDL_Window* GetWindow() const { return StateWindow; }

public: //variables


private: //functions


private: //variables
	
	//Store all of the GameObjects specific to the state
	TArray<GameObject*> StateGameObjects;
	
	//All of the game objects that will spawn on the next frame loop
	TArray<GameObject*> ObjectsToSpawn;

	//Check if the state is currently active
	bool bHasActivated; 

protected: //functions


protected: //variables

	//The window and renderer assigned to this state
	SDL_Window* StateWindow;
	SDL_Renderer* StateRenderer;

};

class GameStateMachine {
public: //functions
	GameStateMachine(GameState* StartingState);
	~GameStateMachine();

	//switch the current state with a new one
	void SwitchState(GameState* NewState);

	//add a state into the state stack - this won't destroy the current state
	void PushState(GameState* NewState);

	//removes the last state that was added to the stack
	void PopState();

	//return the last added game state
	GameState* GetCurrentState() const { return GameStateStack.back(); }

public: //variables


private: //functions


private: //variables
	TArray<GameState*> GameStateStack;

protected: //functions


protected: //variables


};