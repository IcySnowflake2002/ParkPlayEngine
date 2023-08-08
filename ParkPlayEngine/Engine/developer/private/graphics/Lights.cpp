#include "graphics/Lights.h"
#include "Game.h"
#include "graphics/Model.h"
#include "graphics/Material.h"
#include "graphics/ShaderProgram.h"

PointLight::PointLight(ShaderProgram* Shader, float Attenutation, glm::vec3 Colour, bool bDebug) 
	: Light(Shader, Colour), Attenuation(Attenutation)
{
	DebugModel = nullptr;

	//path to the primitive sphere
	PPString ModelPath = "Engine/developer/models/PrimitiveModels/Sphere.fbx";

	//If debug is not set, create a debug model
	if (bDebug)
		DebugModel = Game::GetGameInstance()->Import3DModel(ModelPath);

	//set the emissive of the model to look like a light
	//scale down the sphere so it doesn't take up too much space
	if (DebugModel != nullptr) {
		DebugModel->GetMaterialByIndex(0)->SetEmissiveOverride(Colour, 100.0f);
		Transform.Scale = glm::vec3(1.0f);
	}
}

void PointLight::Draw(PPUint Index)
{
	//Make sure the model follows the light
	if (DebugModel != nullptr)
		DebugModel->Transform = Transform;

	Shader->Run();

	//PointLights[Index].VariableName
	//create the prefix
	PPString Prefix = "PointLights[" + std::to_string(Index) + "]";

	//now we change the shader code
	//set the position
	Shader->SetUniformVec3((Prefix + ".Position").c_str(), Transform.Location);

	//set the colour of the light
	Shader->SetUniformVec3((Prefix + ".Colour").c_str(), Colour);

	//set the attenuation
	//how far the light can reach
	Shader->SetUniformFloat((Prefix + ".Attenuation").c_str(), Attenuation);
}

void DirLight::Draw(PPUint Index)
{
	Shader->Run();

	// DirLights[i].VariableName
	//create a prefix that finds the dirlight array and passes in the index
	PPString Prefix = "DirLights[" + std::to_string(Index) + "]";

	//now we change the shader code based on each variable
	//don't forget to add the period (.)
	//set the direction using the forward vector
	Shader->SetUniformVec3((Prefix + ".Direction").c_str(), Transform.GetDirections().Forward);

	//set the colour of the light
	Shader->SetUniformVec3((Prefix + ".Colour").c_str(), Colour);

	//set the ambient light value
	//this is the minimum light amount
	Shader->SetUniformVec3((Prefix + ".Ambience").c_str(), Ambience);

}
