//---------------------------------------------------------------------------
// Dan Cristian, Rotaru
//---------------------------------------------------------------------------
#include "Triangle.h"

	Triangle::Triangle(){
		width = height = 45.0;
	}

	Triangle::Triangle(GLdouble width, GLdouble height){
		Triangle::width = width;
		Triangle::height = height;
	}

	Triangle::~Triangle(){

	}

	void Triangle::draw(){		
	  glBegin ( GL_LINE_LOOP ) ;
	  glVertex2d( 0, 0 );
      glVertex2d( width, 0 );
	  glVertex2d( width, height );
	  glEnd () ;
	}