#pragma once
#include "CoreMinimal.h"

typedef void* SDL_GLContext;
struct SDL_Window;
class Mesh;
class ShaderProgram;
class ShapeMatrices;

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

	//Create a shape matrix to create a mesh
	Mesh* CreateShapeMesh(ShapeMatrices Shape, ShaderProgram* Shader);

private: //functions


public: //variables


private: //variables
	SDL_GLContext Renderer;
	SDL_Window* Window;

	ShaderProgram* VCShader;

	//DEBUG VARIABLES
	//VertexArrayObject* ParallelVAO;
	TArray<Mesh*> MeshStack;
	Mesh* PolyMesh;
	Mesh* TriMesh;
	Mesh* ParaMesh;
};