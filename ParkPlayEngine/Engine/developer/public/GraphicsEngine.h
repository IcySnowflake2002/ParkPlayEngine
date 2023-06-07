#pragma once

typedef void* SDL_GLContext;
struct SDL_Window;
class VertexArrayObject;

class GraphicsEngine {

public: //functions
	GraphicsEngine();
	~GraphicsEngine();

	//initialise all of the required graphic libraries
	bool Initialise();

	//return the Open GL Renderer context
	SDL_GLContext GetRenderer();
	
	//return the SDL Window
	SDL_Window* GetWindow() const;

	//This will clear the previous frame
	void ClearGraphics();

	//This will draw the new frame
	void DrawGraphics();

	//This will present the new frame to the renderer
	void PresentGraphics();

private: //functions


public: //variables


private: //variables
	SDL_GLContext Renderer;
	SDL_Window* Window;

	//DEBUG VARIABLES
	VertexArrayObject* TriangleVAO;
	VertexArrayObject* PolygonVAO;
};