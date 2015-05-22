//---------------------------------------------------------------------------
// Dan Cristian, Rotaru
//---------------------------------------------------------------------------
#include "Image.h"

	Image::Image() {

	}

	Image::~Image(){

	}

	void Image::draw(){		
		glBindTexture(GL_TEXTURE_2D, textureID);
		glBegin(GL_QUADS);
		glTexCoord2f(0, 0);
		glVertex2f(0, 0); // Upper left

		glTexCoord2f(1, 0);
		glVertex2f(width, 0); // Upper right

		glTexCoord2f(1, 1);
		glVertex2f(width, height); // Lower right

		glTexCoord2f(0, 1);
		glVertex2f(0, height); // Lower left
		glEnd();		
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Image::setSize(GLfloat w, GLfloat h) {
		width = w;
		height = h;
	}

	
	void Image::setTextureId(GLuint textureID) {
		Image::textureID = textureID;
	}



	
