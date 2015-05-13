//---------------------------------------------------------------------------
// Dan Cristian, Rotaru
//---------------------------------------------------------------------------
#ifndef SphereH
#define SphereH

#include "Actor.h"
#include "PV2D.h"
#include <vector>

using namespace std;

class Triangle : public Actor {

	private:
		vector<PV2D> vertex;
		vector<PV2D> texCoords;
		PV2D barycenter, direction;
		bool selected;

	public:
		Triangle();
		~Triangle();
		void draw();
		void setVertex(vector<PV2D> vertex);
		void setTexCoords(vector<PV2D> texCoords);
		bool hit(GLfloat x, GLfloat y);
		void setSelected(bool selected);
		void move();
		void setDirection(GLfloat x, GLfloat y);
		void setBarycenter(GLfloat x, GLfloat y);
};

#endif