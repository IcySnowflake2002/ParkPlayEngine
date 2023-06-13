#include "graphics/ShaderProgram.h"
#include "GLEW/glew.h"

// give us the ability to convert text file into a string
#include <fstream>
#include <sstream>


ShaderProgram::ShaderProgram() 
	: ProgramID(0)
{
}

ShaderProgram::~ShaderProgram()
{
	//Remove the program
	if (ProgramID != 0) {
		glDeleteProgram(ProgramID);
	}

	//remove the shaders
	for (PPUint ShaderID : ShaderIDs) {
		glDeleteShader(ShaderID);
	}
}

bool ShaderProgram::LoadShader(const TArray<PPShaderInfo>& Shaders)
{
	//generate an ID for the shader program
	ProgramID = glCreateProgram();

	//singular version of the array item : the array itself
	//will run for the amount of items in the array
	for (const PPShaderInfo& Shader : Shaders) {
		PPUint ShaderID = CreateShader(Shader.ShaderType, Shader.FilePath);

		//error log in the low chance that the file is read but not loaded correctly
		if (ShaderID == 0) {
			PP_MSG_ERR("ShaderProgram", "Shader failed to load: \n" << Shader.FilePath);
			return false;                  
		}

		PP_MSG_LOG("ShaderProgram", "Shader Loaded: \n" << Shader.FilePath);

		//in OpenGL attach the shader to the relevant program
		glAttachShader(ProgramID, ShaderID);
	}

	//compile the program
	glLinkProgram(ProgramID);

	//error check if linking failed
	//see the similar code in CreateShader for comments
	int LinkStatus = 0;
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &LinkStatus);

	//If it fails run error log
	if (LinkStatus == GL_FALSE) {
		int InfoLogLength = 0;
		glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);

		PPString InfoLog(InfoLogLength, ' ');
		glGetProgramInfoLog(ProgramID, InfoLogLength, nullptr, &InfoLog[0]);

		PP_MSG_ERR("Shader Program", "Shader linking error: \n" << InfoLog);

		glDeleteProgram(ProgramID);
		ProgramID = 0;
		return false;                                                       

	}

	return true;
}

void ShaderProgram::Run() const
{
	if (ProgramID != 0) {
		glUseProgram(ProgramID);
	}
	else {
		PP_MSG_ERR("Shader Program", "Cannot run shader as it doesn't exist.");                        
	}
}

PPUint ShaderProgram::CreateShader(PPShaderTypes ShaderType, const PPString& FilePath)
{
	PPString ShaderCode = ConvertShaderFile(FilePath);
	
	//make sure the file exists
	if (ShaderCode.empty()) {
		PP_MSG_ERR("ShaderProgram", "Failed to read shader file: \n" << FilePath);
		return 0;
	}

	//find the shader type and get the correct OpenGL enum value
	GLenum GLShaderType = GL_INVALID_ENUM;

	switch (ShaderType) {
	case VERTEX:
		GLShaderType = GL_VERTEX_SHADER;
		break;
	case FRAGMENT:
		GLShaderType = GL_FRAGMENT_SHADER;
		break;
	default:
		GLShaderType = GL_INVALID_ENUM;
		break;
	}

	//create the relevant shader
	//generate the shader id based on the type of shader
	PPUint ShaderID = glCreateShader(GLShaderType);
	
	//convert code into const char* format so glew can read the text
	const char* ShaderCodeChar = ShaderCode.c_str();

	//creating the openGL version of the shader code
	glShaderSource(ShaderID, 1, &ShaderCodeChar, nullptr);

	//compile the shader and error if anything is wrong
	//compiling basically means to check for problems
	glCompileShader(ShaderID);

	//error handle any issues with the compile
	int CompileStatus = 0;
	//update our local variable with the compile status
	glGetShaderiv(ShaderID, GL_COMPILE_STATUS, &CompileStatus);

	//if the compile failed it will return GL_FALSE
	if (CompileStatus == GL_FALSE) {
		//get the length of the compile error
		//how many characters are in the error
		int InfoLogLength = 0;
		glGetShaderiv(ShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);

		//create an empty string with the size of the log length
		PPString CompilerMsg( InfoLogLength, ' ');
		//get the message and add it to the above variable
		glGetShaderInfoLog(ShaderID, InfoLogLength, nullptr, &CompilerMsg[0]);

		PP_MSG_ERR("ShaderProgram", "Shader compilation message: \n" << CompilerMsg);
		glDeleteShader(ShaderID);

		return 0;
	}

	//adds the shader into the program shaders array
	ShaderIDs.push_back(ShaderID);

	return ShaderID;
}

PPString ShaderProgram::ConvertShaderFile(const PPString FilePath)
{
	//ifstream type stores file paths as actual paths
	std::ifstream ShaderFile(FilePath);

	std::stringstream ShaderStream;

	//read the file in file path and add the text inside the file to a string
	ShaderStream << ShaderFile.rdbuf();

	//convert into a C++ string
	PPString ReadableString( ShaderStream.str() );

	return ReadableString;
}
