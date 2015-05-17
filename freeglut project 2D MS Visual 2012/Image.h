//---------------------------------------------------------------------------
// Dan Cristian, Rotaru
//---------------------------------------------------------------------------
#ifndef ImageH
#define ImageH

#include "Actor.h"


class Image : public Actor {

	private:
		GLfloat width, height;

	public:
		GLuint textureID;
		Image();
		~Image();
		void draw();
		void setTextureId(GLuint textureID);
		void setSize(GLfloat width, GLfloat height);
};

#endif