#pragma once
#include "CoreMinimal.h"


class Texture {
public: //functions
	Texture();
	~Texture();

	//import a texture file from a file path location and save it to openGL
	bool ImportTexture(const char* FilePath);

	//get the ID Location of the texture in openGL
	PPUint GetID() const { return ID; }

	//used to test if there is already a texture loaded
	const char* GetFilePath() const { return FilePath;  }

	//Activate the texture for use in openGL
	void Bind(PPUint TextureSlot);


public: //variables


private: //functions


private: //variables
	//the ID location of the texture in OpenGL
	PPUint ID;

	//we can use this to test if we already have loaded the texture
	const char* FilePath;

};