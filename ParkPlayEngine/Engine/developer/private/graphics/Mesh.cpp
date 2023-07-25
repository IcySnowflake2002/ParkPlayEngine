#include "graphics/Mesh.h"
#include "graphics/VertexArrayObject.h"
#include "graphics/ShapeMatrices.h"
#include "Game.h"

Mesh::Mesh() : VAO(nullptr), MaterialIndex(0) {}

Mesh::~Mesh()
{
	if (VAO != nullptr) 
		delete VAO;
}

bool Mesh::InitaliseVAO(ShapeMatrices Shape)
{
	//Convert the shape data into an array of vertices
	TArray<PPVertex> ShapeData = PPVertex::ConvertShapeMatrix(Shape);

	//create the vao using the shape
	VAO = new VertexArrayObject(ShapeData, Shape.Indices);

	//if it was successful return true
	return VAO != nullptr;
}

bool Mesh::InitaliseVAO(TArray<PPVertex> Vertices, TArray<PPUint> Indices)
{
	//create the vao using the shape
	VAO = new VertexArrayObject(Vertices, Indices);

	//if it was successful return true
	return VAO != nullptr;

	return false;
}

void Mesh::Draw()
{
	//draw the VAO to the screen
	VAO->Draw();
}
