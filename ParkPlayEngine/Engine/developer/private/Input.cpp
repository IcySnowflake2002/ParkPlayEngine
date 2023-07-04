#include "Input.h"
#include "SDL2/SDL.h"
#include "Game.h"

Input::Input()
{
	KeyboardState = SDL_GetKeyboardState(NULL);
}

void Input::ProcessInput()
{
	SDL_Event Event;

	while (SDL_PollEvent(&Event)) {
		switch (Event.type) {
		case SDL_KEYUP:
			KeyboardState = SDL_GetKeyboardState(NULL);
			break;
		case SDL_KEYDOWN:
			KeyboardState = SDL_GetKeyboardState(NULL);
			break;
		case SDL_QUIT:
			Game::GetGameInstance()->CloseGame();
			break;
		default:
			break;
		}
	}
}

bool Input::isKeyDown(SDL_Scancode KeyCode)
{
	return KeyboardState[KeyCode];
}
