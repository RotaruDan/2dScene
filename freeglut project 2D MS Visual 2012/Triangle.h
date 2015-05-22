//---------------------------------------------------------------------------
// Dan Cristian, Rotaru
//---------------------------------------------------------------------------
#ifndef TriangleH
#define TriangleH

#include "Actor.h"
#include "PV2D.h"
#include <vector>

using namespace std;

enum Mode { 
	DESIGN, SELECT, ANIMATE
};

class Triangle : public Actor {

	

	private:
		GLuint textureID;
		vector<PV2D> vertex;
		vector<PV2D> texCoords;
		bool selected;
		Mode mode;

	public:
		PV2D barycenter, direction;
		Triangle();
		~Triangle();
		void draw();
		void setVertex(vector<PV2D> vertex);
		void setTexCoords(vector<PV2D> texCoords);
		void computeTexCoords(GLfloat width, GLfloat height);
		bool hit(GLfloat x, GLfloat y);
		void setSelected(bool selected);
		void move(float width, float height);
		void setDirection(GLfloat x, GLfloat y);
		void setBarycenter(GLfloat x, GLfloat y);
		void computeBarycenter();
		void firstVertex(GLfloat x, GLfloat y);
		void setMode(Mode mode);
		void setTextureId(GLuint textureID);
};

#endif