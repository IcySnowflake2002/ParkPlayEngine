#pragma once
#include "CoreMinimal.h"
#include "PPTransform.h"

class ShaderProgram;
class Texture;
class Mesh;
class ShapeMatrices;

//assimp importer types
struct aiNode;
struct aiScene;
struct aiMesh;


class Model {
public: //functions
	Model();
	~Model();

	//create a simple shape on the 3D model
	bool CreateSimpleShape(ShapeMatrices Shape, ShaderProgram* Shader = nullptr);

	//import a 3D model file
	bool ImportFromFile(PPString& FilePath, ShaderProgram* Shader = nullptr);

	//draw all meshes to the viewport
	void Draw();

	//add a texture to the model
	void AddTexture(Texture* NewTexture);

public: //variables
	//updaste the transforms of the model in the world space
	PPTransform Transform;

private: //functions
	// find all of the meshes in the assimp scene and process them
	void ProcessMeshes(aiNode* Node, const aiScene* Scene);

	//convert a assimp mesh to a parkplay mesh
	Mesh* ConvertMesh(aiMesh* AMesh, const aiScene* Scene);

private: //variables
	//store all of the models meshes
	TArray<Mesh*> MeshStack;

	//store the file path for an imported model
	PPString FilePath;

	//Store the texture that's applied to the meshes
	Texture* BaseColor;

	//store the shader program
	ShaderProgram* Shader;
	
};