#include "graphics/VertexArrayObject.h"
#include "graphics/ShapeMatrices.h"
#include "CoreMinimal.h"
#include "GLEW/glew.h"

#define VERTEX_SIZE 8

VertexArrayObject::VertexArrayObject(const TArray<PPVertex>& vertexData, const TArray<PPUint>& indexData)
	: VertexData(vertexData), IndexData(indexData)
{
	VaoID = VboID = EabID = 0;

	//ask openGL to generate an ID for this VAO
	glGenVertexArrays(1, &VaoID);

	//If VAO fails to generate ID, delete the class
	if (VaoID == GL_INVALID_VALUE) {
		PP_MSG_ERR("Vertex Array Object", "VAO failed to generate an OpenGL ID.");
		delete this;
		return;
	}

	//activate the VAO so we can work on it
	Bind();

	//set the id's and buffers for the vbo (vertex positions) and eab (vertex indices)
	GenerateAndSetBuffers();

	// save the data in the vertex matrix to a readable format for shaders
	//point to the positions in the vertex matix
	//find the positions in the vertex
	SetAttributePointer(0, 3, GL_FLOAT, VERTEX_SIZE * sizeof(float), 0);

	//store the normal value of the vertex inside the shader
	SetAttributePointer(1, 3, GL_FLOAT, VERTEX_SIZE * sizeof(float), (void*)(3 * sizeof(float)));

	//store the texture coordinates for the shader
	SetAttributePointer(2, 2, GL_FLOAT, VERTEX_SIZE * sizeof(float), (void*) (6 * sizeof(float)));

	//Once everything is set clear the VAO from the VAO slot
	Unbind();
}

VertexArrayObject::~VertexArrayObject()
{
	//no need to delete anytthing if it never worked
	if (VaoID == GL_INVALID_VALUE) {
		return;
	}

	glDeleteVertexArrays(1, &VaoID);
	glDeleteBuffers(1, &VboID);
	glDeleteBuffers(1, &EabID);
}

void VertexArrayObject::SetAttributePointer(PPUint index, PPUint size, PPUint type, int stride, const void* pointer)
{
	//create a slot in the attribute pointer array for this data
	glEnableVertexAttribArray(index);

	//we can add the data into the array element
	glVertexAttribPointer(index, size, type, GL_FALSE, stride, pointer);
}
void VertexArrayObject::Bind()
{
	glBindVertexArray(VaoID);
}

void VertexArrayObject::Unbind()
{
	glBindVertexArray(0);
}

void VertexArrayObject::GenerateAndSetBuffers()
{
	//generate an ID for the VBO
	glGenBuffers(1, &VboID);

	//set up the positions buffer so that openGL understands how to read our vertices
	//bind this buffer
	glBindBuffer(GL_ARRAY_BUFFER, VboID);
	//set the values
	glBufferData(GL_ARRAY_BUFFER,
		VertexData.size() * sizeof(PPVertex), //size of the buffer
		VertexData.data(), //the data to use in the buffer
		GL_STATIC_DRAW);
	
	//// set up the index matrix

	// generate and ID for the EAB
	glGenBuffers(1, &EabID);

	// ditto above but for indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EabID);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		IndexData.size() * sizeof(PPUint),
		IndexData.data(),
		GL_STATIC_DRAW);

}

void VertexArrayObject::Draw()
{
	Bind();
	glDrawElements(GL_TRIANGLES, IndexData.size(), GL_UNSIGNED_INT, 0);

	//PP_MSG_LOG("Vertex Array Object", "Draw Working!");
	Unbind();
}

TArray<PPVertex> PPVertex::ConvertShapeMatrix(ShapeMatrices Shape)
{
	//create a local array
	TArray<PPVertex> VertexArray;

	// loop every 3 positions since we know a vertex is made up of 3 numbers (x, y, z)
	for (PPUint i = 0; i < Shape.Positions.size(); i++) {
		// assign the number based on the index + its relevant value
		//this will get position
		glm::vec3 vPosition = glm::vec3(
			Shape.Positions[i].x, 
			Shape.Positions[i].y, 
			Shape.Positions[i].z);
		//this will get colour
		glm::vec2 vTexCoords = glm::vec2(
			Shape.TexCoords[i].x,
			Shape.TexCoords[i].y);

		// add the position into the vertex array
		VertexArray.push_back(PPVertex(vPosition, vTexCoords));
	}

	return VertexArray;
}
