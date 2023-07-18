#include "graphics/Model.h"
#include "graphics/Mesh.h"
#include "graphics/ShapeMatrices.h"
#include "graphics/ShaderProgram.h"
#include "graphics/Texture.h"
#include "Game.h"
#include "graphics/VertexArrayObject.h"

//assimp headers
#include "ASSIMP/Importer.hpp"
#include "ASSIMP/scene.h"
#include "ASSIMP/postprocess.h"


Model::Model() : Shader(nullptr), BaseColor(nullptr) {}

Model::~Model()
{
	//clean up and delete meshes from memory
	for (Mesh* LMesh : MeshStack) {
		if (LMesh != nullptr) 
			delete LMesh;
	}

	MeshStack.clear();

	BaseColor = nullptr;
	Shader = nullptr;
}

bool Model::CreateSimpleShape(ShapeMatrices Shape, ShaderProgram* Shader)
{
	//if shader equals nullptr, apply the default shader
	if (Shader == nullptr) {
		Shader = Game::GetGameInstance()->GetDefaultShader();
	}

	//If it does not equal nullptr, add the approriate shader to the current mesh
	this->Shader = Shader;

	Mesh* NewMesh = new Mesh(Shader);

	if (!NewMesh->InitaliseVAO(Shape)) {
		PP_MSG_ERR("GE", "Mesh VAO could not be created.");

		return false;
	}

	//if mesh for some reason returns nullptr then fail
	if (NewMesh == nullptr) {
		return false;
	}

	//add our new mesh into the mesh stack
	MeshStack.push_back(NewMesh);

	//Add the default texture to the meshes
	AddTexture(Game::GetGameInstance()->GetDefaultTexture());

	return true;
}

bool Model::ImportFromFile(PPString& FilePath, ShaderProgram* Shader)
{
	//create an assimp importer
	Assimp::Importer AImporter;

	//read the file path and find the mesh
	//also triangulate any quad-based meshes
	const aiScene* AScene = AImporter.ReadFile(FilePath, aiProcess_Triangulate);

	//did the file import anything
	//did the file corrupt or error
	//was there anything in the scene at all
	if (AScene == nullptr || AScene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !AScene->mRootNode) {
		PP_MSG_ERR("Model",
			"Error importing model from file " << FilePath.c_str() << " - " << AImporter.GetErrorString());
		return false;
	}

	//store the file path
	this->FilePath = FilePath;

	//assign the default shader if no custom shader is set
	if (Shader == nullptr) {
		Shader = Game::GetGameInstance()->GetDefaultShader();
	}
	
	//store the shader
	this->Shader = Shader;

	//find all the meshes in the scene and convert them to parkplay meshes
	//and add them to the model meshstack
	ProcessMeshes(AScene->mRootNode, AScene);

	//assign default texture to all meshes
	AddTexture(Game::GetGameInstance()->GetDefaultTexture());

	return true;
}

void Model::Draw()
{
	//draw all of the meshes as long as they are not null
	for (Mesh* LMesh : MeshStack) {
		//draw the mesh and update the transforms if it's not null
		if (LMesh != nullptr) 
			LMesh->Draw(Transform);
	}
}

void Model::AddTexture(Texture* NewTexture)
{
	BaseColor = NewTexture;

	for (Mesh* LMesh : MeshStack) {
		LMesh->BaseColor = BaseColor;
	}
}

void Model::ProcessMeshes(aiNode* Node, const aiScene* Scene)
{
	for (PPUint i = 0; i < Node->mNumMeshes; i++) {
		//find the index of this mesh
		PPUint MIndex = Node->mMeshes[i];
		//get the mesh from the scene
		aiMesh* AMesh = Scene->mMeshes[MIndex];

		//convert the mesh to the parkplay engine
		Mesh* ConvMesh = ConvertMesh(AMesh, Scene);

		//make sure the mesh didn't fail
		if (ConvMesh != nullptr)
			MeshStack.push_back(ConvMesh);
	}

	//each mesh might have other meshes group inside it
	//look through those meshes and process them as well
	for (PPUint i = 0; i < Node->mNumChildren; i++) {
		ProcessMeshes(Node->mChildren[i], Scene);
	}
}

Mesh* Model::ConvertMesh(aiMesh* AMesh, const aiScene* Scene)
{
	TArray<PPVertex> Vertices;
	TArray<PPUint> Indices;

	//loop through all vertices in the imported mesh
	for (PPUint i = 0; i < AMesh->mNumVertices; i++) {
		//create a local vertex
		PPVertex Vertex;

		//find the positions
		Vertex.position = glm::vec3(
			AMesh->mVertices[i].x,
			AMesh->mVertices[i].y,
			AMesh->mVertices[i].z
		);

		//find the normals
		Vertex.normal = glm::vec3(
			AMesh->mNormals[i].x,
			AMesh->mNormals[i].y,
			AMesh->mNormals[i].z
		);

		//find the tex coords
		Vertex.texcoords = glm::vec2(
			AMesh->mTextureCoords[0][i].x,
			AMesh->mTextureCoords[0][i].y
		);

		//add the vertex data into the vertices array
		Vertices.push_back(Vertex);
	}

	//if the mesh has less than 3 vertices then it doesn't have enough to render a mesh
	if (Vertices.size() < 3) {
		PP_MSG_ERR("Model", "Imported Mesh contains less than 3 vertices, skipping mesh");
		return nullptr;
	}

	//we can find the indices using the faces
	//a face is a triangle
	for (PPUint i = 0; i < AMesh->mNumFaces; i++) {
		//get the face
		aiFace Face = AMesh->mFaces[i];

		//loop through all of the indices in the face
		for (PPUint j = 0; j < Face.mNumIndices; j++) {
			//add the indices to the array
			Indices.push_back(Face.mIndices[j]);
		}
	}

	//create a mesh and assign the models shader
	Mesh* ConvMesh = new Mesh(Shader);

	//if creating the VAO fails for some reason
	if (!ConvMesh->InitaliseVAO(Vertices, Indices)) {
		PP_MSG_ERR("Model", "VAO failed to initialise for model: " << FilePath.c_str());
		return nullptr;
	}

	return ConvMesh;
}
