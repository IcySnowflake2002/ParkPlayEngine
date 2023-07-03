#pragma once
#include "CoreMinimal.h"
#include "GLM/glm.hpp"

struct ShapeMatrices;

struct PPVertex {

	PPVertex(glm::vec3 inposition, glm::vec2 intexcoords) : position(inposition), texcoords (intexcoords) {}

	glm::vec3 position; // x,y,z position in world space of the vertex
	glm::vec2 texcoords; // x,y or (u,v) position on the texture map for the vertex

	static TArray<PPVertex> ConvertShapeMatrix(ShapeMatrices Shape);

};

class VertexArrayObject {
public: //functions
	VertexArrayObject(const TArray<PPVertex>& vertexData, const TArray<PPUint>& indexData);
	~VertexArrayObject();

	// save the vertex data into a format that is readable by OpenGL shaders, that format is called an attribute pointer
	// @param 1 - index to assign this attribute pointer in the opengl attribute pointer array
	// @param 2 - how many numbers are in this pointer [e.g. 3 for as vertex position]
	// @param 3 - the data type that will be read for these numbers [e.g. float, int, etc....]
	// @param 4 - size of each row of numbers in bits [e.g. sizeof(datatype) * all the numbers in each row]
	// @param 5 - amount of numbers to skip to get to the row that is in the vertex matrix [e.g. (void*)(sizeof(datatype) * number of elements)]
	void SetAttributePointer(PPUint index, PPUint size, PPUint type, int stride, const void* pointer);

	//activate this VAO in openGL
	void Bind();

	//deactive this VAO
	void Unbind();

	//set up the IDs for this VAO
	void GenerateAndSetBuffers();

	// run every frame to draw it to the screen
	void Draw();

public: //variables


private: //functions


private: //variables
	TArray<PPVertex> VertexData;
	TArray<PPUint> IndexData;

	//VAO ID - Vertex Matrix ID - Index Matrix ID
	PPUint VaoID, VboID, EabID;
};