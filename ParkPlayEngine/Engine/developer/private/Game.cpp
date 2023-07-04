#include "Game.h"
#include "GraphicsEngine.h"
#include "CoreMinimal.h"
#include "SDL2/SDL.h"
#include "Input.h"

//DEBUG
#include "graphics/ShapeMatrices.h"
#include "graphics/Mesh.h"

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

	if (!bIsGameOver)
		BeginPlay();

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

Texture* Game::GetDefaultTexture() const
{
	return Graphics->GetDefaultTexture();
}

Game::Game()
{
	bIsGameOver = false;
	Graphics = nullptr;
	DeltaTime = 0.0;
	GameInput = nullptr;

	//DEBUG
	Cube1 = nullptr;
	Cube2 = nullptr;
}

Game::~Game()
{
}

bool Game::Initialise()
{
	//create new object of the GraphicsEngine
	Graphics = new GraphicsEngine();

	//Check to see if GraphicsEngine failed or not
	if (!Graphics->Initialise()) {
		return false;
	}

	//create new object of the Input
	GameInput = new Input();

	return true;
}

void Game::BeginPlay()
{
	//TODO: Add anything that needs to load at the start

	Cube1 = Graphics->Create3DShape(ppsm3D::Cube);
	Cube2 = Graphics->Create3DShape(ppsm3D::Cube);

	//change one of the cubes to a different texture
	Cube1->BaseColor = Graphics->GetTexture("Engine/developer/textures/default_texGRN.png");

	//move the cubes away from each other
	Cube1->Transform.Location.x += 1.0f;
	Cube2->Transform.Location.x -= 1.0f;
}

void Game::ProcessInput()
{
	//TODO : Process the input of the player
	GameInput->ProcessInput();
}

void Game::Update()
{
	//TODO : Process the logic of the game

	//initialise the last frame time as static to remember the last frame
	static double LastFrameTime = 0.0;
	//get the curretn frame time
	double CurrentFrameTime = static_cast<double>(SDL_GetTicks64());
	//find the delta time 
	double NewDelta = CurrentFrameTime - LastFrameTime;
	//set delta time as seconds
	DeltaTime = NewDelta / 1000.0;
	//update the last frame time for the next loop
	LastFrameTime = CurrentFrameTime;

	//Update any logic in the graphics engine
	Graphics->Update();

	//Transforming Objects
	//Rotating Cube 1
	if (Cube1 != nullptr) {
		Cube1->Transform.Rotation.x += GetDeltaTimeF() * 25.0f;
		Cube1->Transform.Rotation.y += GetDeltaTimeF() * 25.0f;
		Cube1->Transform.Rotation.z += GetDeltaTimeF() * 25.0f;
	}
	
	//Scaling Cube 2
	static bool ScaleUpOrDown = false;

	if (Cube2 != nullptr) {
		if (Cube2->Transform.Scale.x >= 1.2f)
			ScaleUpOrDown = true;

		else if (Cube2->Transform.Scale.x <= 1.0f)
			ScaleUpOrDown = false;

		if (ScaleUpOrDown)
			Cube2->Transform.Scale -= GetDeltaTimeF() * 1.0f;
		else
			Cube2->Transform.Scale += GetDeltaTimeF() * 1.0f;
	}
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
