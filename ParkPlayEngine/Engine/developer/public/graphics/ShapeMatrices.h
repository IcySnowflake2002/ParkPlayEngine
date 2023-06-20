#pragma once
#include "CoreMinimal.h"

struct ShapeMatrices {
	ShapeMatrices(TArray<float> positions, TArray<PPUint> indices, PPUint rowsize) 
		: Data(positions), Indices(indices), RowSize(rowsize) {}

	TArray<float> Data;
	TArray<PPUint> Indices;
	PPUint RowSize;
};

namespace ppsm {
	static const ShapeMatrices Triangle(
		{
			//Storing the triangle positions
			//x		//y		//z		//colour rgb
			0.0f,	0.5f,	0.0f,	1.0f, 0.0f, 0.0f,	//0 - top of triangle - red 
			-0.5f,	-0.5f,	0.0f,	0.0f, 1.0f, 0.0f,	//1 - bottom left of the triangle - green
			0.5f,	-0.5f,	0.0f,	0.0f, 0.0f, 1.0f	//2 - bottom right of the triangle - blue
		}, 
		{
			//creating the triangle
			0, 1, 2		//triangle 1
		},
		6
	);

	static const ShapeMatrices Polygon(
		{
			//Storing the triangle positions
			//x		//y		//z		//colour rgb
			-0.5f,	0.5f,	0.0f, 	1.0f, 1.5f, 0.0f,	//0 - top left - yellow
			0.5f,	0.5f,	0.0f,	1.0f, 1.0f, 0.0f,	//1 - top right - yellow
			-0.5f,	-0.5f,	0.0f,	1.0f, 1.0f, 0.0f,	//2 - bottom left - yellow
			0.5f,	-0.5f,	0.0f,	1.0f, 1.0f, 0.0f	//3 - bottom right - yellow
		},
		{
			//Creating the triangles/square
			0, 1, 2,	//triangle 1
			1, 2, 3		//triangle 2
		},
		6
	);

	static const ShapeMatrices Parallel(
		{
			//storing the circle positions
			//x		//y		//z		//colour rgb
			-0.10,	0.2,	0.0,	1.0f, 1.0f, 0.0f,	//0 - top left - orange
			0.4,	0.2,	0.0,	2.0f, 0.0f, 1.0f,	//1 - top right - purple
			-0.4,	-0.4,	0.0,	1.0f, 1.0f, 0.0f,	//2 - bottom left - orange
			0.10,	-0.4,	0.0,	2.0f, 0.0f, 1.0f	//3 - bottom right - purple
		},
		{
			//creatimg the parallelogram
			0, 1, 2,	//triangle 1
			1, 2, 3		//triangle 2
		},
		6
	);
}

//rgb colour values for later

//1.0f, 0.5, 0.0f - Orange
//0.0f, 1.0f, 1.0f - Teal
//1.0f, 0.0f, 1.0f - Purple