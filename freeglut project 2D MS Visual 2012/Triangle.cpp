//---------------------------------------------------------------------------
// Dan Cristian, Rotaru
//---------------------------------------------------------------------------
#include "Triangle.h"

	Triangle::Triangle() {
	}

	Triangle::~Triangle(){

	}

	void Triangle::draw(){		
		if(mode == DESIGN) {
			glBegin(GL_LINE_LOOP);
			for(unsigned int i = 0; i < vertex.size(); ++i) {
				glVertex2d(vertex[i].getX(), vertex[i].getY());
			}
			glEnd();
		} else if (mode == SELECT) {
			glBindTexture(GL_TEXTURE_2D, textureID);
			glBegin(GL_TRIANGLES);
			for(unsigned int i = 0; i < vertex.size(); ++i) {
				glTexCoord2f(texCoords[i].getX(), texCoords[i].getY());
				glVertex2d(vertex[i].getX(), vertex[i].getY());
			}
			glEnd();			
			glBindTexture(GL_TEXTURE_2D, 0);
			if(selected) {
				glBegin(GL_LINE_LOOP);
				for(unsigned int i = 0; i < vertex.size(); ++i) {
					glVertex2d(vertex[i].getX(), vertex[i].getY());
				}
				glEnd();
			}
		} else if (mode == ANIMATE) {
			glBindTexture(GL_TEXTURE_2D, textureID);
			glBegin(GL_TRIANGLES);
			for(unsigned int i = 0; i < vertex.size(); ++i) {
				glTexCoord2f(texCoords[i].getX(), texCoords[i].getY());
				glVertex2d(vertex[i].getX(), vertex[i].getY());
			}
			glEnd();
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}

	
	void Triangle::setVertex(vector<PV2D> vertex) {
		Triangle::vertex = vertex;
	}

	void Triangle::setTexCoords(vector<PV2D> texCoords) {
		Triangle::texCoords = texCoords;
	}

	void Triangle::computeTexCoords(GLfloat width, GLfloat height) {
		PV2D vertex1 = vertex[0];
		PV2D * texCoord1 = new PV2D(vertex1.getX()/width, vertex1.getY() / height);
		PV2D vertex2 = vertex[1];
		PV2D * texCoord2 = new PV2D(vertex2.getX()/width, vertex2.getY() / height);
		PV2D vertex3 = vertex[2];
		PV2D * texCoord3 = new PV2D(vertex3.getX()/width, vertex3.getY() / height);

		texCoords.clear();
		texCoords.push_back(*texCoord1);
		texCoords.push_back(*texCoord2);
		texCoords.push_back(*texCoord3);
	}
	
	void Triangle::computeBarycenter() {
		GLfloat third = 0.333;
		setBarycenter((vertex[0].getX() + vertex[1].getX() + vertex[2].getX()) * third,
			(vertex[0].getY() + vertex[1].getY() + vertex[2].getY()) * third);
	}
	
	bool Triangle::hit(GLfloat x, GLfloat y) {
		PV2D A = vertex[0];
		PV2D B = vertex[1];
		PV2D C = vertex[2];

		PV2D CP(x - C.getX(), y - C.getY());
		PV2D CB(B.getX() - C.getX(), B.getY() - C.getY());
		PV2D CA(A.getX() - C.getX(), A.getY() - C.getY());
		PV2D CAi = *(CA.normalIzquierda());
		PV2D CBi = *(CB.normalIzquierda());

		float a = CP.dot(&CBi) / CA.dot(&CBi);
		
		float b = CP.dot(&CAi) / CB.dot(&CAi);

		return (a >= 0  && b >= 0) && (a + b) <= 1;
		//int hits = 0;

		//unsigned int npoints = vertex.size();
  //      int lastx = vertex[npoints - 1].getX();
  //      int lasty = vertex[npoints - 1].getY();
  //      int curx, cury;

  //      // Walk the edges of the polygon
  //      for (int i = 0; i < npoints; lastx = curx, lasty = cury, i++) {
  //          curx = vertex[i].getX();
  //          cury = vertex[i].getY();

  //          if (cury == lasty) {
  //              continue;
  //          }

  //          int leftx;
  //          if (curx < lastx) {
  //              if (x >= lastx) {
  //                  continue;
  //              }
  //              leftx = curx;
  //          } else {
  //              if (x >= curx) {
  //                  continue;
  //              }
  //              leftx = lastx;
  //          }

  //          double test1, test2;
  //          if (cury < lasty) {
  //              if (y < cury || y >= lasty) {
  //                  continue;
  //              }
  //              if (x < leftx) {
  //                  hits++;
  //                  continue;
  //              }
  //              test1 = x - curx;
  //              test2 = y - cury;
  //          } else {
  //              if (y < lasty || y >= cury) {
  //                  continue;
  //              }
  //              if (x < leftx) {
  //                  hits++;
  //                  continue;
  //              }
  //              test1 = x - lastx;
  //              test2 = y - lasty;
  //          }

  //          if (test1 < (test2 / (lasty - cury) * (lastx - curx))) {
  //              hits++;
  //          }
  //      }

  //      return ((hits & 1) != 0);
	}

	void Triangle::setSelected(bool selected) {
		Triangle::selected = selected;
	}

	void Triangle::move(float width, float height) {
		
		if(!(barycenter.getX() >= 0 && barycenter.getX() < width)) {
			direction.setX(-direction.getX());	
		}
		if(!(barycenter.getY() >= 0 && barycenter.getY() < height)) {
			direction.setY(-direction.getY());
		}

		barycenter.trasladar(&direction);
		for(unsigned int i = 0; i < vertex.size(); ++i) {
			vertex[i].trasladar(&direction);
		}
	}

	void Triangle::setDirection(GLfloat x, GLfloat y) {
		direction.setX(x);
		direction.setY(y);
	}

	void Triangle::firstVertex(GLfloat x, GLfloat y) {
		PV2D point(x - vertex[0].getX(), y - vertex[0].getY());
		for(unsigned int i = 0; i < vertex.size(); ++i) {
			vertex[i].trasladar(&point);
		}
	}

	void Triangle::setBarycenter(GLfloat x, GLfloat y) {
		barycenter.setX(x);
		barycenter.setY(y);
	}

	
	void Triangle::setMode(Mode mode) {
		Triangle::mode = mode;
	}

	void Triangle::setTextureId(GLuint textureID) {
		Triangle::textureID = textureID;
	}
