#pragma once
#include "CoreMinimal.h";
#include "PPTransform.h"

struct PPVertex;
class VertexArrayObject;
class ShaderProgram;
struct ShapeMatrices;

class Mesh {
public: //functions
	Mesh(ShaderProgram* Shader);
	~Mesh();

	//turn the mesh into a VAO mesh
	bool InitaliseVAO(ShapeMatrices Shape);

	// Draw all the required draws for the mesh
	//shader
	//vao
	void Draw();

	//store and change the transformations of the mesh
	PPTransform Transform;

public: //variables


private: //functions


private: //variables
	//store the VAO
	VertexArrayObject* VAO;

	//store the shader
	ShaderProgram* Shader;


};
