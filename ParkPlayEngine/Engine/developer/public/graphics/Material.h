#pragma once
#include "CoreMinimal.h"
#include "GLM/glm.hpp"

//Only the 0 enum needs defining, the enum operator will automatically assign values when needed based on the list order
enum ETEXTYPES : PPUint {
	//params:	   //tex color								//enum order
	BaseColor = 0, //color map								0
	Specular,	   //Black and White (B&W) = 0 and 1		1
	Normal,		   //Color map								2
	Emissive	   //Fake Lighting, used for glowing		3
};

#define TEXTYPES_NUM 4

class Texture;
class ShaderProgram;
struct PPTransform;

class Material {
public: //functions
	Material(ShaderProgram* Shader, Texture* DefaultTex, Texture* DefaultNormal);

	//Run the shader logic for the material
	void Run(PPTransform Transform);

	// change the texture using the texture type
	void SetTexture(ETEXTYPES Type, Texture* NewTex, float Multiplier = 1.0f);

	//Change the multiplier for the texture type
	void SetMultiplier(ETEXTYPES Type, float Multiplier = 1.0f);

	//get the shader assigned to the material
	ShaderProgram* GetShader() const { return Shader; }

	//set the emissive override colour and override the emissive
	//power/strengthen the emissive with the multipler
	void SetEmissiveOverride(glm::vec3 Colour, float Multiplier);

	//Update transforms for the shader
	void UpdateShaderTransforms(PPTransform Transform);

public: //variables


private: //functions


private: //variables

	//This will hold all of the textures
	Texture* Textures[TEXTYPES_NUM] = { nullptr };

	//This will hold the multipliers for each of the textures
	float Multipliers[TEXTYPES_NUM] = { 1.0f, 1.0f, 1.0f, 1.0f };

	//Emissive colour to override the default or map
	glm::vec3 EmissiveOverride;

	//Store the shader assigned to this material
	ShaderProgram* Shader;

};