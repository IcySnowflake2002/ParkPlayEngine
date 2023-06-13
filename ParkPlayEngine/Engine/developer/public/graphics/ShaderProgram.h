#pragma once
#include "CoreMinimal.h"

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
