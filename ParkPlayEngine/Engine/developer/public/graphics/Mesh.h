#pragma once
#include "CoreMinimal.h";
#include "PPTransform.h"

struct PPVertex;
class VertexArrayObject;
class ShaderProgram;
struct ShapeMatrices;
class Texture;

class Mesh {
public: //functions
	Mesh(ShaderProgram* Shader);
	~Mesh();

	//turn the shape into a VAO mesh
	bool InitaliseVAO(ShapeMatrices Shape);

	//turn the data into a VAO mesh 
	bool InitaliseVAO(TArray<PPVertex> Vertices, TArray<PPUint> Indices);

	// Draw all the required draws for the mesh
	//shader
	//vao
	void Draw(PPTransform Transform);

public: //variables
	//store the texture
	Texture* BaseColor;

private: //functions


private: //variables
	//store the VAO
	VertexArrayObject* VAO;

	//store the shader
	ShaderProgram* Shader;

	//store and change the transformations of the mesh
	PPTransform Transform;
};
