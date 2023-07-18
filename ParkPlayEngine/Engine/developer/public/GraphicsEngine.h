#pragma once
#include "CoreMinimal.h"

typedef void* SDL_GLContext;
struct SDL_Window;
class Model;
class ShaderProgram;
class ShapeMatrices;
class Texture;
class Camera;

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

	//any logic updates for the Graphics Engine
	void Update();

	//Create a 3D shape using the texture shader
	Model* Create3DShape(ShapeMatrices Shape);

	//create a 3D model class using a filepath
	Model* Import3DModel(PPString& FilePath);

	//get texture using filepath or create if isn't loaded
	Texture* GetTexture(const char* FilePath);

	// Get the default engine texture
	Texture* GetDefaultTexture() const { return DefaultEngineTexture; }

	//get the default shader to apply to all models
	ShaderProgram* GetDefaultShader() const { return TexShader;  }

private: //functions
	bool InitEngineShaders();

	// Create the camera and screen transforms
	void ApplyScreenTransforms();

public: //variables


private: //variables
	SDL_GLContext Renderer;
	SDL_Window* Window;

	//vertex colour shader (DEPRECRATED)
	ShaderProgram* VCShader;

	//texture colour shader
	ShaderProgram* TexShader;

	//default Texture that meshes will load
	Texture* DefaultEngineTexture;

	//hold all of the textures loaded into the game
	TArray<Texture*> TextureStack;

	//Current Rendering camera for the engine
	Camera* CurrentCamera;

	//store all models in the game
	TArray<Model*> ModelStack;

};