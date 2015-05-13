//---------------------------------------------------------------------------
// Dan Cristian, Rotaru
//---------------------------------------------------------------------------
#include "Triangle.h"

	Triangle::Triangle() {

	}

	Triangle::~Triangle(){

	}

	void Triangle::draw(){		
	  glBegin(GL_LINE_LOOP);
	  for(int i = 0; i < vertex.size; ++i) {
		  glVertex2d(vertex[i].getX(), vertex[i].getY());
	  }
	  glEnd();
	}

	
	void Triangle::setVertex(vector<PV2D> vertex) {
		Triangle::vertex = vertex;
	}

	void Triangle::setTexCoords(vector<PV2D> texCoords) {
		Triangle::texCoords = texCoords;
	}

	bool Triangle::hit(GLfloat x, GLfloat y) {

	}

	void Triangle::setSelected(bool selected) {
		Triangle::selected = selected;
	}

	void Triangle::move() {

	}

	void Triangle::setDirection(GLfloat x, GLfloat y) {
		direction.setX(x);
		direction.setY(y);
	}


	void Triangle::setBarycenter(GLfloat x, GLfloat y) {
		barycenter.setX(x);
		barycenter.setY(y);
	}
