#include "Game.h"
#include "GraphicsEngine.h"
#include "CoreMinimal.h"
#include "SDL2/SDL.h"

Game* Game::GetGameInstance()
{
	//Create a game instance the first time this function runs
	//After the first time since this is static the variable will not run again and will remain constant
	static Game* GameInstance = new Game();

	return GameInstance;
}

void Game::DestroyGameInstance()
{
	delete GetGameInstance();
}

void Game::Run()
{
	//if initialise succeeds then game is not over
	bIsGameOver = !Initialise();

	//run the game loop
	while (!bIsGameOver) {
		ProcessInput();
		Update();
		Draw();
	}

	//once game is over clean up any memory
	CleanUpGame();
}

void Game::CloseGame()
{
	bIsGameOver = true;
}

Game::Game()
{
	bIsGameOver = false;
	Graphics = nullptr;
}

Game::~Game()
{
}

bool Game::Initialise()
{
	//create new object of the GraphicsEngine
	Graphics = new GraphicsEngine;

	//Check to see if GraphicsEngine failed or not
	if (!Graphics->Initialise()) {
		return false;
	}

	return true;
}

void Game::ProcessInput()
{
	//TODO : Process the input of the player
	SDL_Event Event;

	while (SDL_PollEvent(&Event)) {
		switch (Event.type) {
		case SDL_QUIT :
			CloseGame();
			break;
		default:
			break;
		}
	}
}

void Game::Update()
{
	//TODO : Process the logic of the game
}

void Game::Draw()
{
	//clears the previous frame
	Graphics->ClearGraphics();

	//draws the new frame
	Graphics->DrawGraphics();

	//presents the frame to the window
	Graphics->PresentGraphics();

}

void Game::CleanUpGame()
{
	//destroy the graphics engine
	if (Graphics != nullptr) {
		delete Graphics;
	}
}
