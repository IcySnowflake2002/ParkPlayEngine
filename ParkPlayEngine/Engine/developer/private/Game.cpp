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
	Cube1 = nullptr;
	Cube2 = nullptr;
	Wall = nullptr;
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


	//Load the file path for a 3D cube/sphere
	PPString CubePath = ("Engine/developer/models/PrimitiveModels/Sphere.fbx");

	//Set the Cube models to the CubePath
	Cube1 = Import3DModel(CubePath);
	Cube2 = Import3DModel(CubePath);

	//change one of the cubes to a different texture
	Cube1->SetTextureByMaterial(
		0,
		ETEXTYPES::BaseColor,
		Graphics->GetTexture("Engine/developer/textures/default_texGRN.png")
	);

	//move the cubes away from each other
	Cube1->Transform.Location += glm::vec3(2.0f, 0.0f, 1.0f);
	Cube2->Transform.Location += glm::vec3(2.0f, -1.0f, -1.0f);

	//Create two new cubes
	Model* Cube3 = Import3DModel(CubePath);
	Model* Cube4 = Import3DModel(CubePath);

	//Set Cube 3 to a cobblestone texture
	Cube3->SetTextureByMaterial(
		0,
		ETEXTYPES::BaseColor, 
		Graphics->GetTexture("Engine/developer/textures/cobble.png")
	);
	
	//Set cube 4 to a carpet Texture
	Cube4->SetTextureByMaterial(
		0,
		ETEXTYPES::BaseColor, 
		Graphics->GetTexture("Engine/developer/textures/carpet.png")
	);

	//Adjust Cube3 and Cube4 transforms
	Cube3->Transform.Location += glm::vec3(-4.0f, -1.0f, 1.0f);
	Cube3->Transform.Scale = glm::vec3(0.5f);

	Cube4->Transform.Location += glm::vec3(-6.0f, 1.0f, -1.0f);
	Cube4->Transform.Rotation = glm::vec3(0.0f, 0.0f, 25.0f);
	Cube4->Transform.Scale = glm::vec3(2.0f);

	//custom model filepaths
	PPString WallPath = "Engine/developer/models/damaged_wall/SM_Wall_Damaged_2x1_A.obj";
	PPString RingPath = "Engine/developer/models/ring_gltf/scene.gltf";

	//custom models
	//Wall
	Wall = Graphics->Import3DModel(WallPath);

	if (Wall != nullptr) {
			Wall->SetTextureByMaterial(
				1,
				ETEXTYPES::BaseColor,
				Graphics->GetTexture("Engine/developer/models/damaged_wall/T_Wall_Damaged_2x1_A_basecolor.png")
			);

		Wall->Transform.Location += glm::vec3(7.0f, 0.0f, -3.0f);
		Wall->Transform.Rotation = glm::vec3(0.0f, 90.0f, 0.0f);
		Wall->Transform.Scale *= 0.01;

	}

	//Ring
	Ring = Graphics->Import3DModel(RingPath);

	if (Ring != nullptr) {
			Ring->SetTextureByMaterial(
				0,
				ETEXTYPES::BaseColor,
				Graphics->GetTexture("Engine/developer/models/ring_gltf/defaultMat_baseColor.jpeg")
			);

		Ring->Transform.Scale *= 0.1;
		Ring->Transform.Location += glm::vec3(5.0f, 0.0f, 5.0f);
		Ring->Transform.Rotation = glm::vec3(90.0f, 0.0f, 0.0f);

	}
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
