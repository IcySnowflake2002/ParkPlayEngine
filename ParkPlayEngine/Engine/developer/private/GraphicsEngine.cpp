#include "GraphicsEngine.h"
#include "SDL2/SDL.h"
#include "GLEW/glew.h"
#include "CoreMinimal.h"
#include "graphics/Mesh.h"
#include "graphics/ShaderProgram.h"
#include "graphics/Texture.h"

//DEBUG INCLUDES
#include "graphics/ShapeMatrices.h"
#include "PPTransform.h"


GraphicsEngine::GraphicsEngine()
{
	Window = nullptr;
	Renderer = nullptr;
	VCShader = nullptr;
	TexShader = nullptr;
	DefaultEngineTexture = nullptr;

	//debug
	TriMesh = nullptr;
	PolyMesh = nullptr;
	ParaMesh = nullptr;
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
		800,
		800,
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
	
	InitEngineShaders();

	//set the default texture
	DefaultEngineTexture = GetTexture("Engine/developer/textures/default_texBLU.png");

	//intialise with shapes filled
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//DEBUG - Initalise meshes
	TriMesh = CreateShapeMesh(ppsm::Triangle, TexShader);
	PolyMesh = CreateShapeMesh(ppsm::Polygon, TexShader);
	ParaMesh = CreateShapeMesh(ppsm::Parallel, TexShader);

	//Set the textures
	TriMesh->BaseColor = DefaultEngineTexture;
	PolyMesh->BaseColor = GetTexture("Engine/developer/textures/default_texGRN.png");
	ParaMesh->BaseColor = DefaultEngineTexture;

	//Triangle Mesh Transforms
	if (TriMesh != nullptr) {
		TriMesh->Transform.Location.x = 0.5f;
		TriMesh->Transform.Location.y = 0.5f;
		TriMesh->Transform.Scale = glm::vec3(0.8f);
	}

	//Polygon Mesh Transforms
	if (PolyMesh != nullptr) {
		PolyMesh->Transform.Location.x = -0.5f;
		PolyMesh->Transform.Location.y = 0.4f;
		PolyMesh->Transform.Scale = glm::vec3(0.5f);
		PolyMesh->Transform.Rotation.z = 45.0f;
	}

	//Parallelogram Mesh Transforms
	if (ParaMesh != nullptr) {
		ParaMesh->Transform.Location.y = -0.4f;
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
	
	//Make the Parallelogram rotate forever
	if (ParaMesh != nullptr) {
		ParaMesh->Transform.Rotation.z += 0.01f;
	}

	// loop through all of the mesh stack elements
	for (Mesh* LMesh : MeshStack) {
		LMesh->Draw();
	}
}

void GraphicsEngine::PresentGraphics()
{
	//present the opengl renderer to the window
	SDL_GL_SwapWindow(Window);
}

Mesh* GraphicsEngine::CreateShapeMesh(ShapeMatrices Shape, ShaderProgram* Shader)
{
	Mesh* NewMesh = new Mesh(Shader);

	if (!NewMesh->InitaliseVAO(Shape)) {
		PP_MSG_ERR("GE", "Mesh VAO could not be created.");

		return nullptr;
	}

	//add our new mesh into the mesh stack
	MeshStack.push_back(NewMesh);

	return NewMesh;
}

Texture* GraphicsEngine::GetTexture(const char* FilePath)
{
	//loop through the textures and see if one already exists with the same path
	for (Texture* LTexture : TextureStack) {
		//if the filepath is the same then just exit the function and return the texture
		//strcmp is the better way to compare const char* of strings and returns a 0 if its a match
		if (strcmp(LTexture->GetFilePath(), FilePath) == 0) {
			return LTexture;
		}
	}

	//if there is no texture found then create a new one
	Texture* NewTexture = new Texture();

	//import the texture but delete it if it doesn't work
	if (!NewTexture->ImportTexture(FilePath)) {
		delete NewTexture;
		return nullptr;
	}

	//if all is successful, add the texture to the texture stack to make sure we don't get another
	TextureStack.push_back(NewTexture);

	return NewTexture;
}

bool GraphicsEngine::InitEngineShaders()
{
	VCShader = new ShaderProgram();

	//Importing the shaders from their files
	//vertex shader
	PPShaderInfo VShader(
		PPShaderTypes::VERTEX,
		"Engine/developer/shaders/VColour/VColor.ppvshader"
	);
	//fragment shader
	PPShaderInfo FShader(
		PPShaderTypes::FRAGMENT,
		"Engine/developer/shaders/VColour/VColor.ppfshader"
	);

	//load the shader
	if (!VCShader->LoadShader({ VShader, FShader })) {
		delete VCShader;
		PP_MSG_ERR("Graphics Engine", "Vertex Colour Shader failed");
		return false;
	}

	TexShader = new ShaderProgram();
	
	//import the vertex shader
	VShader = PPShaderInfo(
		PPShaderTypes::VERTEX,
		"Engine/developer/shaders/Texture/Texture.ppvshader"
	);

	//import the fragment shader
	FShader = PPShaderInfo(
		PPShaderTypes::FRAGMENT,
		"Engine/developer/shaders/Texture/Texture.ppfshader"
	);

	if (!TexShader->LoadShader({ VShader, FShader })) {
		delete TexShader;
		PP_MSG_ERR("Graphics Engine", "Texture Shader Failed");

		return false;
	}

	return true;
}
