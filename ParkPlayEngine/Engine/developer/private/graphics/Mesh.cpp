#include "graphics/Mesh.h"
#include "graphics/VertexArrayObject.h"
#include "graphics/ShaderProgram.h"
#include "GLM/gtc/matrix_transform.hpp"
#include "graphics/ShapeMatrices.h"

Mesh::Mesh(ShaderProgram* Shader) : Shader (Shader)
{
	VAO = nullptr;
}

Mesh::~Mesh()
{
	if (VAO != nullptr) {
		delete VAO;
	}
}

bool Mesh::InitaliseVAO(ShapeMatrices Shape)
{
	//Convert the shape data into an array of vertices
	TArray<PPVertex> ShapeData = PPVertex::ConvertShapeMatrix(Shape);

	//create the vao using the shape
	VAO = new VertexArrayObject(ShapeData, Shape.Indices, Shape.RowSize);

	//if it was successful return true
	return VAO != nullptr;
}

void Mesh::Draw()
{
	//set the shader for this mesh as the active shader
	Shader->Run();

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
	Shader->SetUniformTransform(ShaderTransform);

	VAO->Draw();
}
