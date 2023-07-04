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

namespace ppsm2D {
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

namespace ppsm3D {
	static const ShapeMatrices Cube(
		{
			// x	// y	// z	
			float3(-0.5f, -0.5f, 0.5f),		// back - bot - left 0
			float3(0.5f, -0.5f, 0.5f),		// back - bot - right 1
			float3(0.5f, 0.5f, 0.5f),		// back - top - right 2
			float3(-0.5f, 0.5f, 0.5f),		// back - top - left 3
			float3(-0.5f, 0.5f, -0.5f),		// front - top - left 4
			float3(0.5f, 0.5f, -0.5f),		// front - top - right 5
			float3(0.5f, -0.5f, -0.5f),		// front - bot - right 6
			float3(-0.5f, -0.5f, -0.5f),	// front - bot - left 7
			float3(-0.5f, 0.5f, -0.5f),		// left - top - right 8
			float3(-0.5f, 0.5f, 0.5f),		// left - top - left 9
			float3(-0.5f, -0.5f, 0.5f),		// left - bot - left 10
			float3(-0.5f, -0.5f, -0.5f),	// left - bot - right 11
			float3(0.5f, 0.5f, -0.5f),		// right - top - right 12
			float3(0.5f, 0.5f, 0.5f),		// right - top - left 13
			float3(0.5f, -0.5f, 0.5f),		// right - bot - left 14
			float3(0.5f, -0.5f, -0.5f),		// right - bot - right 15
			float3(-0.5f, 0.5f, 0.5f),		// top - bot - left 16
			float3(0.5f, 0.5f, 0.5f),		// top - bot - right 17
			float3(0.5f, 0.5f, -0.5f),		// top - top - right 18
			float3(-0.5f, 0.5f, -0.5f),		// top - top - left 19
			float3(-0.5f, -0.5f, 0.5f),		// bot - top - left 20
			float3(0.5f, -0.5f, 0.5f),		// bot - top - right 21
			float3(0.5f, -0.5f, -0.5f),		// bot - bot - right 22
			float3(-0.5f, -0.5f, -0.5f)		// bot - bot - left 23
		},
		{
			// tex coords
			float2(0.0f, 0.0f), // 0
			float2(1.0f, 0.0f), // 1
			float2(1.0f, 1.0f), // 2
			float2(0.0f, 1.0f), // 3
			float2(0.0f, 1.0f), // 4
			float2(1.0f, 1.0f), // 5
			float2(1.0f, 0.0f), // 6
			float2(0.0f, 0.0f), // 7
			float2(1.0f, 1.0f), // 8
			float2(0.0f, 1.0f), // 9
			float2(0.0f, 0.0f), // 10
			float2(1.0f, 0.0f), // 11
			float2(1.0f, 1.0f), // 12
			float2(0.0f, 1.0f), // 13
			float2(0.0f, 0.0f), // 14
			float2(1.0f, 0.0f), // 15
			float2(0.0f, 0.0f), // 16
			float2(1.0f, 0.0f), // 17
			float2(1.0f, 1.0f), // 18
			float2(0.0f, 1.0f), // 19
			float2(0.0f, 1.0f), // 20
			float2(1.0f, 1.0f), // 21
			float2(1.0f, 0.0f), // 22
			float2(0.0f, 0.0f)	// 23
		},
		{
			0,	1,	2,	// front tri 1
			2,	3,	0,	// front tri 2
			12, 13, 15,	// right tri 1
			15, 14, 13,	// right tri 2
			8,	9,	10,	// left tri 1
			10,	11,	8,	// left tri 2
			20,	21,	22,	// bot tri 1
			22,	23,	20,	// bot tri 2
			16,	17,	18,	// top tri 1
			18,	19,	16,	// top tri 2
			4,	5,	6,	// back tri 1
			6,	7,	4	// back tri 2
		}
		);
}