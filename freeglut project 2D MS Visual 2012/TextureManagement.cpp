#include "TextureManagement.h"
#include "TextureLoader.h"


void initTexture(GLuint & myTexture,
	             unsigned int & textureWidth, unsigned int & textureHeight,
				 const std::string BMP_Name){
	glEnable(GL_TEXTURE_2D);	
	glGenTextures(1, &myTexture);
	glBindTexture(GL_TEXTURE_2D, myTexture);

	
	//Filters and clamping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	

	//Load the BMP into pixMap
	bool flipY= false;
	unsigned char* pixMap= loadBMPRaw(BMP_Name.c_str(), textureWidth, textureHeight, flipY);

	//Upload the image inside pixMap to the GPU, and bind it to active texture name
	GLint level= 0; //Base image level
	GLint border= 0; //No border
	glTexImage2D(GL_TEXTURE_2D, level, GL_RGB, textureWidth, textureHeight, border, GL_RGB, GL_UNSIGNED_BYTE, pixMap);

	//Textures and ilumination
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	delete[] pixMap;
}

void releaseTexture(GLuint & myTexture){
	glDeleteTextures(1, &myTexture);
}