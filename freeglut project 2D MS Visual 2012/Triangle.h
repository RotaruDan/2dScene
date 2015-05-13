//---------------------------------------------------------------------------
// Dan Cristian, Rotaru
//---------------------------------------------------------------------------
#ifndef SphereH
#define SphereH

#include "Actor.h"

class Triangle : public Actor {

	private:
		GLdouble width, height;

	public:
		Triangle();
		Triangle(GLdouble width, GLdouble height);
		~Triangle();
		void draw();
};

#endif