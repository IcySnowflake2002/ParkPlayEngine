#pragma once
#include "SDL2/SDL.h"
#include "CoreMinimal.h"

// making our max mouse button more readable
#define MAX_MOUSE_BUTTONS SDL_BUTTON_X2

struct MouseData {

	MouseData()
		: MouseXDelta(0), MouseYDelta(0), ScrollDelta(0.0f) {}

	MouseData(int mousexdelta, int mouseydelta, float scrolldelta)
		: MouseXDelta(mousexdelta), MouseYDelta(mouseydelta), ScrollDelta(scrolldelta) {}
		
		int MouseXDelta, MouseYDelta;
		float ScrollDelta;
};


class Input {
public: //functions
	Input();

	//process inputs
	void ProcessInput();

	//check if key is down
	bool isKeyDown(SDL_Scancode KeyCode);

	//check if a mouse button is down
	bool isMouseButtonDown(PPUint Button);

	//return the data of the mouse
	MouseData GetMouseData() const;

	//show and hide the cursor
	void SetCursorVisible(bool bIsVisible);

public: //variables


private: //functions

	//set mouse button state
	void SetMouseState(PPUint Button, bool bState);

private: //variables

	//holds the state of the keyboard
	const unsigned char* KeyboardState;

	//holds the state of the mouse buttons
	PPUint MouseState[SDL_BUTTON_X2] = { false };

	// amount the mouse has moved in either x or y
	int MouseXDelta, MouseYDelta;

	//amount the scroll wheel has moved in either direction
	float ScrollDelta;
};