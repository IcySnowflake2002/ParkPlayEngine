#pragma once
#include "SDL2/SDL.h"


class Input {
public: //functions
	Input();

	//process inputs
	void ProcessInput();

	//check if key is down
	bool isKeyDown(SDL_Scancode KeyCode);

public: //variables


private: //functions


private: //variables
	const unsigned char* KeyboardState;
};