#include "GraphicsEngine.h"
#include "SDL2/SDL.h"
#include "GLEW/glew.h"
#include "CoreMinimal.h"

//DEBUG INCLUDES
#include "graphics/VertexArrayObject.h"
#include "graphics/ShapeMatrices.h"

GraphicsEngine::GraphicsEngine()
{
	Window = nullptr;
	Renderer = nullptr;
}

GraphicsEngine::~GraphicsEngine()
{
	SDL_DestroyWindow(Window);
	SDL_GL_DeleteContext(Renderer);
}

bool GraphicsEngine::Initialise()
{
	//initialise SDL2
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		PP_MSG_ERR("Graphics Engine", "SDL Failed To Initialise: " << SDL_GetError());
		return false;
	}

	//set up opengl for SDL2
	//setting up the required attributes for opengl
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4); //major version of opengl to use v4
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6); //minor version of opengl to use v4.6
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY); //allow SDL to use the latest version of opengl
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24); //OpenGL Transparency
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8); //Colour Red bit depth
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8); //Colour Green bit depth
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8); //Colour Blue bit depth

	//create the SDL flags for the window
	Uint32 WindowFlags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL;

	//Create Window
	Window = SDL_CreateWindow(
		"ParkPlay Engine | An OpenGL Engine",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640,
		480,
		WindowFlags);

	//if the window fails to create, fail the app and print error message to console
	if (Window == nullptr) {
		PP_MSG_ERR("Graphics Engine", "Window failed to initialise: " << SDL_GetError());
		SDL_Quit();
		return false;
	}

	//create the opengl Renderer
	Renderer = SDL_GL_CreateContext(Window);

	//if the renderer fails to create, fail the app and print error message to console
	if (Renderer == nullptr) {
		PP_MSG_ERR("Graphics Engine", "SDL failed to create opengl context: " << SDL_GetError());
		SDL_Quit();
		return false;
	}

	//activates the experimental libraries in GLEW (which seems to be all of them?)
	glewExperimental = GL_TRUE;

	//initialise glew and fail if it doesn't succeed
	if (glewInit() != GLEW_OK) {
		PP_MSG_ERR("Graphics Engine", "Glew failed to initialise: " << glewGetErrorString(glewInit()));
		SDL_GL_DeleteContext(Renderer);
		SDL_DestroyWindow(Window);
		SDL_Quit();
		return false;
	}

	return true;
}

SDL_GLContext GraphicsEngine::GetRenderer()
{
	return Renderer;
}

SDL_Window* GraphicsEngine::GetWindow() const
{
	return Window;
}

void GraphicsEngine::ClearGraphics()
{
	// set the background colour when there are no objects over it
	glClearColor(0.23f, 0.38f, 0.47f, 1.0f);

	//clear the screen
	glClear(GL_COLOR_BUFFER_BIT);
}

void GraphicsEngine::DrawGraphics()
{
	//TODO : Draw 3D Objects to the screen
	//Creating the VAO
	TArray<PPVertex> Vertices = PPVertex::ConvertShapeMatrix(ppsm::Triangle);

	//Checking if shape has not yet been loaded
		// Loading Triangle
	if (TriangleVAO == nullptr) {
		PP_MSG_LOG("GE", "Triangle");
		TriangleVAO = new VertexArrayObject(Vertices, ppsm::Triangle.Indices);
	}

	//Drawing the VAO Triangle to the screen
	if (TriangleVAO != nullptr) {
		TriangleVAO->Draw();
	}

	Vertices = PPVertex::ConvertShapeMatrix(ppsm::Polygon);

		//Loading Polygon
	if (PolygonVAO == nullptr) {
		PP_MSG_LOG("GE", "Polygon");
		Vertices = PPVertex::ConvertShapeMatrix(ppsm::Polygon);

		PolygonVAO == new VertexArrayObject(Vertices, ppsm::Polygon.Indices);
	}

	//Drawing the VAO Polygon to the screen
	if (PolygonVAO != nullptr) {
		PolygonVAO->Draw();
	}

}

void GraphicsEngine::PresentGraphics()
{
	//present the opengl renderer to the window
	SDL_GL_SwapWindow(Window);
}
