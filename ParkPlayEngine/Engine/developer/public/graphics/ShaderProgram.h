#pragma once
#include "CoreMinimal.h"
#include "GLM/glm.hpp"

//Store the shader types
enum PPShaderTypes : PPUint{
	VERTEX = 0,
	FRAGMENT
};

//Store the Information needed to run shaders
//Takes two parameters, including the type of shader and the file path
struct PPShaderInfo {
	PPShaderInfo(PPShaderTypes InType, PPString InPath)
		: ShaderType(InType), FilePath(InPath) {

	}

	PPShaderTypes ShaderType;
	PPString FilePath;
};

class ShaderProgram {
public: //functions
	ShaderProgram();
	~ShaderProgram();

	//intialise the shader files
	//Vertex shader should be added first, then the fragment shader
	bool LoadShader(const TArray<PPShaderInfo>& Shaders);

	//activate shader as the current shader program for OpenGL
	void Run() const;

	//returns the OpenGL ID for the shader
	PPUint GetID() const { return ProgramID; }

	//this will change the "Transform" shader variable
	void SetUniformTransform(const char* TransformName, glm::mat4 Transform);

	//this will allow us to change the integer values in shaders
	//sampler2D takes an integer
	void SetUniformInt(const char* ShaderVariableName, int Value);

	//set a int in an array in the shader
	void SetUniformArrayInt(const char* ArrayName, PPUint Index, int Value);

	//set a float in the shader
	void SetUniformFloat(const char* ShaderVariableName, float Value);

	//set a float in an array in the shader
	void SetUniformArrayFloat(const char* ArrayName, PPUint Index, float Value);

	//set a vec3 in the shader
	void SetUniformVec3(const char* VarName, glm::vec3 Value);

public: //variables


private: //functions

	//Creates the individual shaders based on their type
	//vertex and frag shaders will be assigned seperately
	//returns 0 when it fails
	PPUint CreateShader(PPShaderTypes ShaderType, const PPString& FilePath);

	//read the GLSL format and convert it into a string for openGL
	PPString ConvertShaderFile(const PPString FilePath);

private: //variables
	PPUint ProgramID;
	TArray<PPUint> ShaderIDs;

};
