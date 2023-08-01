#pragma once
#include "CoreMinimal.h"
#include "PPTransform.h"

class ShaderProgram;
class Model;

//normal lights
class Light {
public: //functions
	Light(ShaderProgram* Shader, glm::vec3 Colour = glm::vec3(1.0f)) : Shader(Shader), Colour(Colour) {}

	//Draw the lights to the shader
	virtual void Draw(PPUint Index) {}

public: //variables

	//Transforms of the Light in the viewport
	PPTransform Transform;

	//colour of the light
	glm::vec3 Colour;

private: //functions


private: //variables


protected: //functions
	

protected: //variables
	ShaderProgram* Shader;

};

//directional light
class DirLight :
	public Light {
public: //functions
	DirLight(ShaderProgram* Shader, glm::vec3 Ambience = glm::vec3 (0.0f), glm::vec3 Colour = glm::vec3(1.0f))
		: Light(Shader, Colour), Ambience(Ambience) {}

public: //variables

	//minimum light for all areas that have no light 
	glm::vec3 Ambience;

private: //functions


private: //variables


protected: //functions


protected: //variables


};

//point light
class PointLight
	: public Light {

public: //functions
	PointLight(ShaderProgram* Shader, float Attenutation, glm::vec3 Colour = glm::vec3(1.0f), bool bDebug = false);

	//Draw the light to the shader and draw a debug model if required
	virtual void Draw(PPUint Index) override;

public: //variables

	//falloff distance of the light
	float Attenuation; //how far the light goes until you can't see it anymore | falloff

private: //functions


private: //variables


protected: //functions


protected: //variables

	//A model that is only used if debugging the light
	Model* DebugModel;

};