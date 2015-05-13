#ifndef TEXTURE_MANAGEMENT_H
#define TEXTURE_MANAGEMENT_H

#include <Windows.h>
#include <gl/GL.h>
#include <string>
//////////////////////////
// Texture management
void initTexture(GLuint & myTexture,
	             unsigned int & textureWidth, unsigned int & textureHeight,
				 const std::string BMP_Name);

void releaseTexture(GLuint & myTexture);

#endif //TEXTURE_MANAGEMENT_H