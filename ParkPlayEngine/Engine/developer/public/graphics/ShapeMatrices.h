#pragma once
#include "CoreMinimal.h"

//This will allow us to store any 2 value numbers in a similar format. Used mostly to read textures.
struct float2 {
	float2(float x, float y) :
		x(x), y(y) {}

	float x, y;
};

//This will allows us to store any 3 value numbers in a simpler format. Used mostly for positions.
struct float3 {
	float3(float x, float y, float z)
		: x(x), y(y), z(z) {}

	float x, y, z;
};

struct ShapeMatrices {
	ShapeMatrices(TArray<float3> positions, TArray<float2> texcoords, TArray<PPUint> indices) 
		: Positions(positions), TexCoords(texcoords), Indices(indices) {}

	TArray<float3> Positions;
	TArray<float2> TexCoords;
	TArray<PPUint> Indices;
};

namespace ppsm {
	static const ShapeMatrices Triangle(
		{
			//Storing the triangle positions
			//x		//y		//z		
			float3(0.0f, 0.5f, 0.0f),
			float3(-0.5f, -0.5f, 0.0f),
			float3(0.5f, -0.5f, 0.0f)
		},
		{
			//x //y
			float2(0.5f, 1.0f), // 0
			float2(0.0f, 0.0f), // 1
			float2(1.0f, 0.0f)  // 2
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
			float3(-0.5f, 0.5f, 0.0f),
			float3(0.5f, 0.5f, 0.0f),
			float3(-0.5f, -0.5f, 0.0f),
			float3(0.5f, -0.5f, 0.0f)
		},
		{
				   //x    //y
			float2(0.0f, 1.0f), // 0
			float2(1.0f, 1.0f), // 1
			float2(0.0f, 0.0f), // 2
			float2(1.0f, 0.0f)  // 3
		},
		{
			//Creating the triangles/square
			0, 1, 2,	//triangle 1
			1, 2, 3		//triangle 2
		}
	);

	static const ShapeMatrices Parallel(
		{
			//storing the circle positions
			//x		//y		//z		
			float3(-0.10f, 0.2f, 0.0f),
			float3(0.4f, 0.2f, 0.0f),
			float3(-0.4f, -0.4f, 0.0f),
			float3(0.10f, -0.4f, 0.0f)
		},
		{
				   //x   //y
			float2(0.3f, 1.0f),
			float2(1.0f, 1.0f),
			float2(0.3f, 0.3f),
			float2(1.0f, 0.3f)

		},
		{
			//creatimg the parallelogram
			0, 1, 2,	//triangle 1
			1, 2, 3		//triangle 2
		}
	);
}

//rgb colour values for later

//1.0f, 0.5, 0.0f - Orange
//0.0f, 1.0f, 1.0f - Teal
//1.0f, 0.0f, 1.0f - Purple