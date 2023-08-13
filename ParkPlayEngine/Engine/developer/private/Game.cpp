#include "Game.h"
#include "GraphicsEngine.h"
#include "CoreMinimal.h"
#include "SDL2/SDL.h"
#include "Input.h"
#include "graphics/ShaderProgram.h"
#include "graphics/ShapeMatrices.h"
#include "graphics/Model.h"
#include "graphics/Lights.h"
#include "graphics/Material.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/Collectible.h"
#include "GameObjects/Ring.h"

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

Texture* Game::GetEngineTexture(EENGINETEX EngineTex) const
{
	return Graphics->GetEngineTexture(EngineTex);
}

Model* Game::Import3DModel(PPString& FilePath)
{
	return Graphics->Import3DModel(FilePath);
}

ShaderProgram* Game::GetDefaultShader() const
{
	return Graphics->GetDefaultShader();
}

DirLight* Game::CreateDirLight(glm::vec3 Ambience, glm::vec3 Colour) const
{
	return Graphics->CreateDirLight(Ambience, Colour);
}

PointLight* Game::CreatePointLight(float Attenuation, glm::vec3 Colour, bool bDebug)
{
	return Graphics->CreatePointLight(Attenuation, Colour, bDebug);
}

void Game::RemoveModelFromGraphics(Model* ModelRef)
{
	Graphics->RemoveModelByRef(ModelRef);
}

Game::Game()
{
	bIsGameOver = false;
	Graphics = nullptr;
	DeltaTime = 0.0;
	GameInput = nullptr;

	//DEBUG

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
	// CREATE LIGHTS
	
	//Create a directional light
	CreateDirLight(glm::vec3(-70.0f), glm::vec3(1.0f, 1.0f, 0.5f));

	//Create a point light
	PointLight* L = CreatePointLight(10.0f, glm::vec3(1.0f), true);
	L->Transform.Location = glm::vec3(5.0f, 0.0f, 0.0f);

	PointLight* L2 = CreatePointLight(-30.0f, glm::vec3(1.0f), true);
	L2->Transform.Location = glm::vec3(-5.0f, 0.0f, 5.0f);

	CollectibleObj = new Collectible(PPTransform());
	CollectibleObj->BeginPlay();
	CollectibleObj->Transform.Scale *= 100.0f;

	RingObj = new Ring(PPTransform());
	RingObj->BeginPlay();
	
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

	//Set game timer
	GameTimer += GetDeltaTimeF();

	//Update any logic in the graphics engine
	Graphics->Update();

	//Update the game object
	CollectibleObj->Update(GetDeltaTimeF());

	if (GameInput->isMouseButtonDown(SDL_BUTTON_RIGHT)) {
		GameInput->SetCursorVisible(false);
	}
	else {
		GameInput->SetCursorVisible(true);
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
