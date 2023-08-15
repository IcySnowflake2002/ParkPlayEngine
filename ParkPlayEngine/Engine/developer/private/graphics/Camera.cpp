#include "graphics/Camera.h"
#include "Game.h"
#include "Input.h"
#include "SDL2/SDL.h"

#define DEFAULT_FOV 70.0f

Camera::Camera(float x, float y, float z)
{
	FOV = DEFAULT_FOV;
	Transform.Location = glm::vec3(x, y, z);
	NearClip = 0.1f;
	FarClip = 1000.0f;
	Speed = 5.0f;
	LookSensitivity = 40.0f;
}

Camera::~Camera()
{
	FOV = 0.0f;
	NearClip = 0.0f;
	FarClip = 0.0f;
}

void Camera::AddMovementInput(glm::vec3 Direction, float Scale)
{
	//this will make sure that we don't go 2x speed when going diagonal
	//and that direction only passes a direction
	if (glm::length(Direction) > 0.0f)
		Direction = glm::normalize(Direction);

	// adjust the direction for the speed value
	glm::vec3 SpeedDirection = Direction * Speed;

	//get the speed of the camera and account for time
	glm::vec3 DeltaSpeed = SpeedDirection * Game::GetGameInstance()->GetDeltaTimeF();

	// move the camera location based on direction and speed then scale that value
	Transform.Location += DeltaSpeed * Scale;
}

void Camera::AddRotation(glm::vec3 Rotation)
{
	//this will make sure that sensitivity works for the camera rotation
	Rotation *= LookSensitivity / 100.0f;

	//Rotate the pitch
	Transform.Rotation.x += Rotation.x;
	
	//min chooses the smaller number of the two capping x at 89.0f
	Transform.Rotation.x = std::min(Transform.Rotation.x, 89.0f);

	//max chooses the larger number of the two capping x at -89.0f minimum
	Transform.Rotation.x = std::max(Transform.Rotation.x, -89.0f);

	//Rotate the yaw
	Transform.Rotation.y += Rotation.y;

	// makes sure the rotation resets when it hits 360.0f
	Transform.Rotation.y = glm::mod(Transform.Rotation.y, 360.0f);
}
