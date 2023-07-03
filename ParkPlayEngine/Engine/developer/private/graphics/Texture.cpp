#include "graphics/Texture.h"
#include "GLEW/glew.h"
#include "STBIMAGE/stb_image.h"

Texture::Texture()
{
	ID = 0;
	FilePath = "";
}

Texture::~Texture()
{
	glDeleteTextures(1, &ID);
}

bool Texture::ImportTexture(const char* FilePath)
{
	this->FilePath = FilePath;

	//create the variables to store the image data
	int Width, Height, nChannels;
	//stbi image imports images upside down...
	//so we need to run this function to load them in correctly
	stbi_set_flip_vertically_on_load(true);
	//load in the texture and fill in our data
	unsigned char* ImageData = stbi_load(FilePath, &Width, &Height, &nChannels, STBI_rgb_alpha);

	//if the image data didn't load then fail the function and log the error
	if (ImageData == nullptr) {
		PP_MSG_ERR("Texture", "Texture " << FilePath << " failed to import.");
		stbi_image_free(ImageData);

		return false;
	}

	//generate an ID for the texture
	glGenTextures(1, &ID);

	//make sure the ID was assigned
	if (ID == GL_INVALID_INDEX) {
		PP_MSG_ERR("Texture", "Texture " << FilePath << " failed to assign an ID in openGL.");
		stbi_image_free(ImageData);

		return false;
	}

	//bind the texture
	glBindTexture(GL_TEXTURE_2D, ID);

	//set the parameters of the texture
	//what happens when the texture is larger or smaller than the map size
	
	//setting what happens when the texture doesn't fit the x axis (S = X in textures)
	// it should repeat or copy itself over and over until it fits
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//do the same but for the Y axis (T = Y in textures)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//what happens if the texture resolution is scaled up and down
	//MIN_FILTER is when the texture scales down and MAG is scale up
	//LINEAR interpolates colours to create a blend to change the pixels
	//NEAREST copies the pixel next to it
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//create the texture information and store it in OpenGL
	//p1 = Type of Texture
	//p2 = irrelevant ()
	//p3 = format to read the texture file
	//p4 & p5 = width and height of the image
	//p6 = if we want a border (not for textures)
	//p7 = format to convert the file to
	//p8 = type of data to read (this is set by stbi image)
	//p9 = the stored image data to read
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, ImageData);

	//removes the image data from memory
	stbi_image_free(ImageData);

	GLenum Error = glGetError();
	if (Error != GL_NO_ERROR) {
		PP_MSG_ERR("Texture", "Texture " << FilePath << " failed to generate texture with error code: " << Error);

		return false;
	}

	PP_MSG_LOG("Texture", FilePath << " was loaded successfully.");

	//set the default texture as the current bound texture
	glBindTexture(GL_TEXTURE_2D, 0);

	return true;
}

void Texture::Bind(PPUint TextureSlot)
{
	//creates a texture unit for this texture to bind to
	glActiveTexture(TextureSlot);
	glBindTexture(GL_TEXTURE_2D, GetID());
}
