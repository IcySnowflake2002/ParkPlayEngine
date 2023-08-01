#include "GameState.h"
#include "SDL2/SDL.h"
#include "GameObject.h"
#include "GraphicsEngine.h"


// GAME STATE

GameState::GameState(SDL_Renderer* Renderer, SDL_Window* Window)
{
	StateWindow = Window;
	StateRenderer = Renderer;
	bHasActivated = false;
}

GameState::~GameState()
{
	//delete all of the objects in the objects-to-spawn list
	for (GameObject* SingleModel : ObjectsToSpawn) {
		delete SingleModel;
	}

	ObjectsToSpawn.clear();
}

void GameState::ProcessInput(Input* PlayerInput)
{

}

void GameState::Update(float DeltaTime)
{
}

void GameState::Draw(SDL_Renderer* Renderer)
{
}

void GameState::Instantiate()
{
}

void GameState::HandleGarbage()
{
}

void GameState::BeginState()
{
}

void GameState::EndState()
{
}

// GAME STATE MACHINE

GameStateMachine::GameStateMachine(GameState* StartingState)
{
}

GameStateMachine::~GameStateMachine()
{
}

void GameStateMachine::SwitchState(GameState* NewState)
{
}

void GameStateMachine::PushState(GameState* NewState)
{
}

void GameStateMachine::PopState()
{
}
