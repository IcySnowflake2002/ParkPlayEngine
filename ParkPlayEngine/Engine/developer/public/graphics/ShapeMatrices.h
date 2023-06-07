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
			//x		//y		//z
			0.5f,	0.5f,	0.0f,	//0 - top of the triangle
			-0.5f,	-0.5f,	0.0f,	//1 - bottom left
			0.5f,	-0.5f,	0.0f,	//2 - bottom right
		},
		{
			0, 1, 2 //triangle 1
		}
	);
}
