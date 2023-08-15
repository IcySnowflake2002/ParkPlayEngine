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
#include "GameObjects/Player.h"
#include "physics/AABBCollision.h"

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
		GarbageCollection();
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

void Game::SetCurrentCamera(TSharedPtr<Camera> NewCamera)
{
	Graphics->SetCurrentCamera(NewCamera);
}

void Game::SetCursorVisible(bool bVisible)
{
	if (GameInput != nullptr)
		GameInput->SetCursorVisible(bVisible);
}

Texture* Game::GetOrCreateTexture(PPString FilePath)
{
	return Graphics->GetTexture(FilePath.c_str());
}

GameObject* Game::AddGameObjectToGame(GameObject* NewGameObject)
{
	GameObjectStack.push_back(NewGameObject);

	return NewGameObject;
}

Game::Game()
{
	bIsGameOver = false;
	Graphics = nullptr;
	DeltaTime = 0.0;
	GameInput = nullptr;
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
	PointLight* L = CreatePointLight(10.0f, glm::vec3(1.0f), false);
	L->Transform.Location = glm::vec3(5.0f, 0.0f, 0.0f);

	PointLight* L2 = CreatePointLight(-30.0f, glm::vec3(1.0f), false);
	L2->Transform.Location = glm::vec3(-5.0f, 0.0f, 5.0f);

	//Create collectible objects
	PPTransform ColTrans;
	ColTrans.Location.x = 3.0f;
	ColTrans.Scale = glm::vec3(0.1f);
	GameObject* CollectibleObj = new Collectible(ColTrans);
	AddGameObjectToGame(CollectibleObj);

	ColTrans.Location.x += 3.0f;
	GameObject* CollectibleObj2 = new Collectible(ColTrans);
	AddGameObjectToGame(CollectibleObj2);

	//create a player object
	GameObject* PlayerObj = new Player(PPTransform());
	AddGameObjectToGame(PlayerObj);

	//Run the BeginPlay functions for all game objects
	for (GameObject* GO : GameObjectStack) {
		if (GO != nullptr)
			GO->BeginPlay();
	}
}

void Game::ProcessInput()
{
	//TODO : Process the input of the player
	GameInput->ProcessInput();

	//Close the game with escape press
	if (GameInput->isKeyDown(SDL_SCANCODE_ESCAPE))
		CloseGame();

	for (GameObject* GO : GameObjectStack) {
		if (GO != nullptr) {
			//test if the player is a player object class and use that pointer if it is
			if (Player* PO = dynamic_cast<Player*>(GO)) {
				PO->ProcessInput(GameInput);
			}
		}
	}
}

void Game::Update()
{
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

	//TODO : Process the logic of the game

	//Update the game object
	for (GameObject* GO : GameObjectStack) {
		if (GO != nullptr)
			GO->Update(GetDeltaTimeF());
	}

	//handle collision detection
	for (GameObject* GO : GameObjectStack) {
		if (GO != nullptr) {
			//if the game object does not have a collider then ignore it and go the next one
			if (GO->GetCollider() == nullptr)
				continue;

			//looping through all the objects to test collision
			for (GameObject* TestGO : GameObjectStack) {
				//is there a collider on the test game object - ignore it if not
				if (TestGO->GetCollider() == nullptr || TestGO == GO)
					continue;

				//if they are intersecting then detect the collision
				if (AABBCollision::IsIntersecting(*GO->GetCollider(), *TestGO->GetCollider())) {
					GO->DetectCollisions(TestGO);
				}
			}
		}
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

void Game::GarbageCollection()
{
	//loop through all game objects and delete them if needed
	for (TArray<GameObject*>::iterator i = GameObjectStack.begin(); i < GameObjectStack.end();) {
		if ((*i)->ShouldDestroy()) {
			delete (*i);
			(*i) = nullptr;
			//erase provides i with a proper updated iterator if the size has changed
			i = GameObjectStack.erase(i);
			continue;
		}

		i++;
	}
}

void Game::CleanUpGame()
{
	//clean up all game objects
	for (GameObject* GO : GameObjectStack) {
		if (GO != nullptr)
			delete GO;
	}

	//destroy the graphics engine
	if (Graphics != nullptr) {
		delete Graphics;
	}
}
