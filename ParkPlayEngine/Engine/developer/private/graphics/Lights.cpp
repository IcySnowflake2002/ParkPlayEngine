#include "graphics/Lights.h"
#include "Game.h"
#include "graphics/Model.h"
#include "graphics/Material.h"

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

}
