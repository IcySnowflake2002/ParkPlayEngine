#include "graphics/Camera.h"
#include "Game.h"
#include "Input.h"
#include "SDL2/SDL.h"

Camera::Camera(float x, float y, float z)
{
	FOV = 70.0f;
	Transform.Location = glm::vec3(x, y, z);
	NearClip = 0.1f;
	FarClip = 1000.0f;
	Speed = 15.0f;
}

Camera::~Camera()
{
	FOV = 0.0f;
	NearClip = 0.0f;
	FarClip = 0.0f;
}

void Camera::Update()
{
	Input* GameInput = Game::GetGameInstance()->GetGameInput();

	//Move camera forward if W is down
	if (GameInput->isKeyDown(SDL_SCANCODE_W)) {
		Transform.Location.z += Speed * Game::GetGameInstance()->GetDeltaTimeF();
	}

	//Move camera backwards if S is down
	if (GameInput->isKeyDown(SDL_SCANCODE_S)) {
		Transform.Location.z -= Speed * Game::GetGameInstance()->GetDeltaTimeF();
	}

	//Move camera left if A is down
	if (GameInput->isKeyDown(SDL_SCANCODE_A)) {
		Transform.Location.x += Speed * Game::GetGameInstance()->GetDeltaTimeF();
	}

	//Move camera right if D is down
	if (GameInput->isKeyDown(SDL_SCANCODE_D)) {
		Transform.Location.x -= Speed * Game::GetGameInstance()->GetDeltaTimeF();
	}

	//Move camera up if E is down
	if (GameInput->isKeyDown(SDL_SCANCODE_E)) {
		Transform.Location.y += Speed * Game::GetGameInstance()->GetDeltaTimeF();
	}

	//Move camera down if Q is down
	if (GameInput->isKeyDown(SDL_SCANCODE_Q)) {
		Transform.Location.y -= Speed * Game::GetGameInstance()->GetDeltaTimeF();
	}
}
