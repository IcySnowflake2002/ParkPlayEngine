#pragma once
#include "CoreMinimal.h"

struct ShapeMatrices {
	ShapeMatrices(TArray<float> positions, TArray<PPUint> indices) 
		: Positions(positions), Indices(indices) {}

	TArray<float> Positions;
	TArray<PPUint> Indices;
};

namespace ppsm {
	static const ShapeMatrices Triangle(
		{
			//Storing the triangle positions
			//x		//y		//z
			0.5f,	0.5f,	0.0f,	//0 - top of triangle
			-0.5f,	-0.5f,	0.0f,	//1 - bottom left of the triangle
			0.5f,	-0.5f,	0.0f	//2 - bottom right of the triangle
		}, 
		{
			//creating the triangle
			0, 1, 2		//triangle 1
		}
	);

	static const ShapeMatrices Polygon(
		{
			//Storing the triangle positions
			//x		//y		//z
			-0.5f,	0.5f,	0.0f,	//0 - top left
			0.5f,	0.5f,	0.0f,	//1 - top right
			-0.5f,	-0.5f,	0.0f,	//2 - bottom left
			0.5f,	-0.5f,	0.0f	//3 - bottom right
		},
		{
			//Creating the triangles/square
			0, 1, 2,	//triangle 1
			1, 2, 3		//triangle 2
		}
	);
}