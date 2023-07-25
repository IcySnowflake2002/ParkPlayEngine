#pragma once
#include "CoreMinimal.h";
#include "PPTransform.h"

struct PPVertex;
class VertexArrayObject;
struct ShapeMatrices;

class Mesh {
public: //functions
	Mesh();
	~Mesh();

	//turn the shape into a VAO mesh
	bool InitaliseVAO(ShapeMatrices Shape);

	//turn the data into a VAO mesh 
	bool InitaliseVAO(TArray<PPVertex> Vertices, TArray<PPUint> Indices);

	// Draw all the required draws for the mesh
	//shader
	//vao
	void Draw();

	//set the material index for use in the model class
	void SetMaterialIndex(PPUint Index) { MaterialIndex = Index; }

	//gets the material index
	PPUint GetMaterialIndex() const { return MaterialIndex; }

public: //variables


private: //functions


private: //variables

	//hold the index for the material in the model
	PPUint MaterialIndex;

	//store the VAO
	VertexArrayObject* VAO;

	//store and change the transformations of the mesh
	PPTransform Transform;
};
