#pragma once
#include "CoreMinimal.h"
#include "GLM/glm.hpp"

typedef void* SDL_GLContext;
struct SDL_Window;
class Model;
class ShaderProgram;
class ShapeMatrices;
class Texture;
class Camera;
class PointLight;
class DirLight;

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

	// Get the default engine textures
	Texture* GetEngineTexture(EENGINETEX EngineTex) const { return TextureStack[EngineTex]; }

	//get the default shader to apply to all models
	ShaderProgram* GetDefaultShader() const { return TexShader;  }

	//Create a point light
	PointLight* CreatePointLight(float Attenuation, glm::vec3 Colour = glm::vec3(1.0f), bool bDebug = false);

	//Create a directional light
	DirLight* CreateDirLight(glm::vec3 Ambience = glm::vec3(0.0f), glm::vec3 Colour = glm::vec3(1.0f));

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

	//hold all of the textures loaded into the game
	TArray<Texture*> TextureStack;

	//Current Rendering camera for the engine
	Camera* CurrentCamera;

	//store all models in the game
	TArray<Model*> ModelStack;

	//store all of the lights in the game
	//store the point lights
	TArray<PointLight*> PointLightStack;
	//store the dir lights
	TArray<DirLight*> DirLightStack;

};