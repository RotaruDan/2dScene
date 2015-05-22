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

		for(unsigned int i = 0, n = vertex.size(); i < n; ++i) {
			PV2D a = vertex[i];
			PV2D b = vertex[(i+1) % n];
			PV2D affineSegment(b.getX() - a.getX(), b.getY() - a.getY());
			PV2D affinePoint(x - a.getX(), y - a.getY());

			GLfloat xProduct = affineSegment.getX() * affinePoint.getY() - affineSegment.getY() * affinePoint.getX();

			if(xProduct <= 0) {
				return false;
			}
		}

		return true;
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
