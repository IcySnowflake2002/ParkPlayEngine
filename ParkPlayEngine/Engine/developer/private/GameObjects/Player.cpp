#include "GameObjects/Player.h"
#include "Game.h"
#include "graphics/Camera.h"
#include "Input.h"

Player::Player(PPTransform DefaultTransform)
	: GameObject(DefaultTransform)
{
	PlayerCamera = std::make_shared<Camera>();
	Speed = 10.0f;
	PitchInput = YawInput = 0.0f;
	PlayerCamera->Speed = Speed;
}

void Player::ProcessInput(Input* GameInput)
{
	//reset the movement each frame so we stop moving when we are not pressing input
	MovementAxis = glm::vec3(0.0f);
	 
	//Add forwards direction if we press w to movement axis
	if (GameInput->isKeyDown(SDL_SCANCODE_W))
		MovementAxis += Transform.GetForward();

	//Add backwards direction if we press s to movement axis
	if (GameInput->isKeyDown(SDL_SCANCODE_S))
		MovementAxis += -Transform.GetForward();

	//Add right direction if we press d to movement axis
	if (GameInput->isKeyDown(SDL_SCANCODE_D))
		MovementAxis += Transform.GetRight();

	//Add right direction if we press a to movement axis
	if (GameInput->isKeyDown(SDL_SCANCODE_A))
		MovementAxis += -Transform.GetRight();

	//Add up direction if we press q to movement axis
	if (GameInput->isKeyDown(SDL_SCANCODE_Q))
		MovementAxis += Transform.GetUp();

	//Add down direction if we press e to movement axis
	if (GameInput->isKeyDown(SDL_SCANCODE_E))
		MovementAxis += -Transform.GetUp();

	// make sure our axis can't go above 1 or below -1
	if (glm::length(MovementAxis) > 0.0f)
		MovementAxis = glm::normalize(MovementAxis);

	//set rotational inputs based on mouse movement
	YawInput = GameInput->GetMouseData().MouseXDelta;
	PitchInput = -GameInput->GetMouseData().MouseYDelta;
}

void Player::BeginPlay()
{
	GameObject::BeginPlay();

	Game::GetGameInstance()->SetCurrentCamera(PlayerCamera);

	Game::GetGameInstance()->SetCursorVisible(false);

	AddCollider(glm::vec3(1.0f));
}

void Player::Update(float DeltaTime)
{
	GameObject::Update(DeltaTime);

	//move the camera based on player input
	PlayerCamera->AddMovementInput(MovementAxis);
	//rotate the camera based on mouse input
	PlayerCamera->AddRotation(glm::vec3(PitchInput, YawInput, 0.0f));

	//make the player follow the camera
	Transform = PlayerCamera->Transform;
}
