#pragma once
#include "CoreMinimal.h"

//Only the 0 enum needs defining, the enum operator will automatically assign values when needed based on the list order
enum ETEXTYPES : PPUint {
	//params:	   //tex color					//enum order (AO definition)
	BaseColor = 0, //color map					0
	Metalness,	   // Black and White (B&W),	1
	Roughness,     // B&W,						2
	AO,			   // B&W,						3			 (Ambient Occulsion)
	Normal		   // B&W,						4
};

#define TEXTYPES_NUM 5

class Texture;
class ShaderProgram;
struct PPTransform;

class Material {
public: //functions
	Material(ShaderProgram* Shader, Texture* DefaultTex);

	//Run the shader logic for the material
	void Run(PPTransform Transform);

	// change the texture using the texture type
	void SetTexture(ETEXTYPES Type, Texture* NewTex, float Multiplier = 1.0f);

	//Change the multiplier for the texture type
	void SetMultiplier(ETEXTYPES Type, float Multiplier = 1.0f);

	//get the shader assigned to the material
	ShaderProgram* GetShader() const { return Shader; }

	//Update transforms for the shader
	void UpdateShaderTransforms(PPTransform Transform);

public: //variables


private: //functions


private: //variables

	//This will hold all of the textures
	Texture* Textures[TEXTYPES_NUM] = { nullptr };

	//This will hold the multipliers for each of the textures
	float Multipliers[TEXTYPES_NUM] = { 1.0f };

	//Store the shader assigned to this material
	ShaderProgram* Shader;

};