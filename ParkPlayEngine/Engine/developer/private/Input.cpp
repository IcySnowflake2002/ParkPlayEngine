#include "Input.h"
#include "SDL2/SDL.h"
#include "Game.h"

Input::Input()
{
	KeyboardState = SDL_GetKeyboardState(NULL);
}

void Input::ProcessInput()
{

	if (KeyboardState == nullptr) 
		KeyboardState = SDL_GetKeyboardState(NULL);

	//Reset the delta each frame to make sure we get 0
	MouseXDelta = MouseYDelta = ScrollDelta = 0;

	SDL_Event Event;

	while (SDL_PollEvent(&Event)) {
		switch (Event.type) {
		case SDL_KEYUP:
			KeyboardState = SDL_GetKeyboardState(NULL);
			break;
		case SDL_KEYDOWN:
			KeyboardState = SDL_GetKeyboardState(NULL);
			break;
		case SDL_MOUSEBUTTONDOWN :
			MouseState[Event.button.button] = true;
			break;
		case SDL_MOUSEBUTTONUP :
			MouseState[Event.button.button] = false;
			break;
		case SDL_MOUSEMOTION :
			MouseXDelta += Event.motion.xrel;
			MouseYDelta += Event.motion.yrel;
			break;
		case SDL_MOUSEWHEEL :
			ScrollDelta += Event.wheel.preciseY;
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

bool Input::isMouseButtonDown(PPUint Button)
{
	//making sure the button isn't out of the array scope
	if (Button > MAX_MOUSE_BUTTONS) 
		return false;


	return MouseState[Button];
}

MouseData Input::GetMouseData() const
{
	return MouseData(MouseXDelta, MouseYDelta, ScrollDelta);
}

void Input::SetCursorVisible(bool bIsVisible)
{
	//set the cursor to be visible by default
	SDL_bool RelativeMode = SDL_FALSE;

	//turn the cursor off and activate relative mode if we want to hide the cursor
	if (!bIsVisible)
		RelativeMode = SDL_TRUE;

	SDL_SetRelativeMouseMode(RelativeMode);
}

void Input::SetMouseState(PPUint Button, bool bState)
{
	if (Button > MAX_MOUSE_BUTTONS)
		return;
	
	MouseState[Button] = bState;
}
