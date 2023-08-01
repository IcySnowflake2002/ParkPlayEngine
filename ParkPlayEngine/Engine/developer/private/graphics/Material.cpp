#include "graphics/Material.h"
#include "graphics/ShaderProgram.h"
#include "graphics/Texture.h"
#include "PPTransform.h"
#include "GLM/gtc/matrix_transform.hpp"


Material::Material(ShaderProgram* Shader, Texture* DefaultTex, Texture* DefaultNormal) 
	: Shader(Shader)
{
	// Update all textures to use the default texture
	for (PPUint i = 0; i < TEXTYPES_NUM; i++) {
		Textures[i] = DefaultTex;
	}

	EmissiveOverride = glm::vec3(0.0f);
}

void Material::Run(PPTransform Transform)
{
	//set the shader for this mesh as the active shader
	Shader->Run();

	//Loop through all of the textures and beind them to the shader
	for (PPUint i = 0; i < TEXTYPES_NUM; i++) {
		Textures[i]->Bind(i);

		//Update the texture to the relevant slot and variable in the shader
		Shader->SetUniformArrayInt("Textures", i, i);

		//Update the Shader Multiplier
		Shader->SetUniformArrayFloat("TMultipliers", i, Multipliers[i]);

	}

	Shader->SetUniformVec3("EmissiveOverride", EmissiveOverride);

	//Update the shader with the transforms based on the model
	UpdateShaderTransforms(Transform);
}

void Material::SetTexture(ETEXTYPES Type, Texture* NewTex, float Multiplier)
{
	//error log if TextureType overloads
	if (Type >= TEXTYPES_NUM) {
		PP_MSG_ERR("Material", "No texture type exists on that index");
		return;
	}

	//change the texture relevant to the texture type
	Textures[Type] = NewTex;

	//update the multiplier
	SetMultiplier(Type, Multiplier);
}

void Material::SetMultiplier(ETEXTYPES Type, float Multiplier)
{
	//error log if TextureType overloads
	if (Type >= TEXTYPES_NUM) {
		PP_MSG_ERR("Material", "No texture multiplier exists on the index");
		return;
	}

	//Update the multiplier relevant to the texture type
	Multipliers[Type] = Multiplier;

}

void Material::SetEmissiveOverride(glm::vec3 Colour, float Multiplier) 
{
	EmissiveOverride = Colour * Multiplier;
}

void Material::UpdateShaderTransforms(PPTransform Transform)
{

	//Update the shader with transforms based on the model
	glm::mat4 ShaderTransform = glm::mat4(1.0f);

	//translate the mesh based on the location
	ShaderTransform = glm::translate(ShaderTransform, Transform.Location);

	//handle rotations
	// rotate the x axis based on the x value in rotation
	ShaderTransform = glm::rotate(ShaderTransform, glm::radians(Transform.Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	// rotate the y axis based on the y value in rotation
	ShaderTransform = glm::rotate(ShaderTransform, glm::radians(Transform.Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	//rotate the z axis based on the z value in rotation
	ShaderTransform = glm::rotate(ShaderTransform, glm::radians(Transform.Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

	//Scale the mesh based on the transform scale
	ShaderTransform = glm::scale(ShaderTransform, glm::vec3(Transform.Scale));

	// update the shader with the new transforms
	Shader->SetUniformTransform("Model", ShaderTransform);
}
