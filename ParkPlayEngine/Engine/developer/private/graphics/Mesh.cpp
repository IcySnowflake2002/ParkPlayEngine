#include "graphics/Mesh.h"
#include "graphics/VertexArrayObject.h"
#include "graphics/ShaderProgram.h"
#include "GLM/gtc/matrix_transform.hpp"
#include "graphics/ShapeMatrices.h"
#include "graphics/Texture.h"
#include "Game.h"

Mesh::Mesh(ShaderProgram* Shader) : Shader (Shader)
{
	VAO = nullptr;
	BaseColor = nullptr;
}

Mesh::~Mesh()
{
	if (VAO != nullptr) 
		delete VAO;

	// if statements don't need braces if the logic is only on one line
	if (BaseColor != nullptr) 
		BaseColor = nullptr;
}

bool Mesh::InitaliseVAO(ShapeMatrices Shape)
{
	//Convert the shape data into an array of vertices
	TArray<PPVertex> ShapeData = PPVertex::ConvertShapeMatrix(Shape);

	//create the vao using the shape
	VAO = new VertexArrayObject(ShapeData, Shape.Indices);

	//assign the default engine texture if the VAO was successful
	if (VAO != nullptr)
		BaseColor = Game::GetGameInstance()->GetDefaultTexture();

	//if it was successful return true
	return VAO != nullptr;
}

bool Mesh::InitaliseVAO(TArray<PPVertex> Vertices, TArray<PPUint> Indices)
{
	//create the vao using the shape
	VAO = new VertexArrayObject(Vertices, Indices);

	//assign the default engine texture if the VAO was successful
	if (VAO != nullptr)
		BaseColor = Game::GetGameInstance()->GetDefaultTexture();

	//if it was successful return true
	return VAO != nullptr;

	return false;
}

void Mesh::Draw(PPTransform Transform)
{
	//Ensure the transforms are updated every frame
	this->Transform = Transform;

	//set the shader for this mesh as the active shader
	Shader->Run();

	//set the texture in the shader
	if (BaseColor != nullptr) {
		BaseColor->Bind(0);
		Shader->SetUniformInt("Texture", 0);
	}

	glm::mat4 ShaderTransform = glm::mat4(1.0f);
	
	//translate the mesh based on the location
	ShaderTransform = glm::translate(ShaderTransform, Transform.Location);
		
	//handle rotations
	// rotate the x axis based on the x value in rotation
	ShaderTransform = glm::rotate(ShaderTransform, glm::radians(Transform.Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	// rotate the y axis based on the y value in rotation
	ShaderTransform = glm::rotate(ShaderTransform, glm::radians(Transform.Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	//rotate the z axis based on the z value in rotation
	ShaderTransform = glm::rotate(ShaderTransform, glm::radians(Transform.Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

	//Scale the mesh based on the transform scale
	ShaderTransform = glm::scale(ShaderTransform, glm::vec3(Transform.Scale));

	// update the shader with the new transforms
	Shader->SetUniformTransform("Model", ShaderTransform);

	VAO->Draw();
}
