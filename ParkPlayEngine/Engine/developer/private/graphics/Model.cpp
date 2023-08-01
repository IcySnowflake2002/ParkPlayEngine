#include "graphics/Model.h"
#include "graphics/Mesh.h"
#include "graphics/ShapeMatrices.h"
#include "graphics/ShaderProgram.h"
#include "graphics/Material.h"
#include "Game.h"
#include "graphics/VertexArrayObject.h"

//assimp headers
#include "ASSIMP/Importer.hpp"
#include "ASSIMP/scene.h"
#include "ASSIMP/postprocess.h"


Model::Model() : Shader(nullptr) {}

Model::~Model()
{
	//clean up and delete the material stack
	for (Material* LMat : MatStack) {
		if (LMat != nullptr)
			delete LMat;
	}

	MatStack.clear();

	//clean up and delete meshes from memory
	for (Mesh* LMesh : MeshStack) {
		if (LMesh != nullptr) 
			delete LMesh;
	}

	MeshStack.clear();

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

	//create a new mesh object
	Mesh* NewMesh = new Mesh();

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

	//Add a single material to the model for our simple shapes
	SetMaterialStack(1);

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

	SetMaterialStack(AScene->mNumMaterials);

	//find all the meshes in the scene and convert them to parkplay meshes
	//and add them to the model meshstack
	ProcessMeshes(AScene->mRootNode, AScene);

	return true;
}

void Model::Draw()
{
	//draw all of the meshes as long as they are not null
	for (Mesh* LMesh : MeshStack) {
		//draw the mesh and update the transforms if it's not null
		if (LMesh != nullptr) {
			//running the material based on the assigned material index
			MatStack[LMesh->GetMaterialIndex()]->Run(Transform);
			//drawing the VAO
			LMesh->Draw();
		}
	}
}

Material* Model::GetMaterialByIndex(PPUint Index)
{
	//make sure there is a material slot AND that material slot is not nullptr
	if (MatStack.size() <= Index) {
		//if there is no material but there is a slot
		PP_MSG_ERR("Model", "Material has no valid slot at that index");
		return nullptr;
	}

	if (MatStack[Index] == nullptr) {
		PP_MSG_ERR("Model", "Material has no valid material at that index");
		return nullptr;
	}

	return MatStack[Index];
}

void Model::SetTextureByMaterial(PPUint MaterialIndex, ETEXTYPES TexType, Texture* NewTexture, float Multiplier)
{
	//validate check that the texture exists
	if (GetMaterialByIndex(MaterialIndex) == nullptr) {
		PP_MSG_ERR("Model", "Can't Change Texture");
		return;
	}

	//change the texture
	GetMaterialByIndex(MaterialIndex)->SetTexture(TexType, NewTexture, Multiplier);
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
	Mesh* ConvMesh = new Mesh();

	//if creating the VAO fails for some reason
	if (!ConvMesh->InitaliseVAO(Vertices, Indices)) {
		PP_MSG_ERR("Model", "VAO failed to initialise for model: " << FilePath.c_str());
		return nullptr;
	}
	
	//Assign the material index to the mesh
	ConvMesh->SetMaterialIndex(AMesh->mMaterialIndex);

	return ConvMesh;
}

void Model::SetMaterialStack(PPUint NumMaterials)
{
	MatStack.resize(NumMaterials);

	for (PPUint i = 0; i < NumMaterials; i++) {
		MatStack[i] = new Material(Shader, Game::GetGameInstance()->GetEngineTexture(ETGrey50),
			Game::GetGameInstance()->GetEngineTexture(ETBlue));
	}
}
