//---------------------------------------------------------------------------
// Dan Cristian, Rotaru
//---------------------------------------------------------------------------
#include "Actor.h"

	Actor::Actor(){
		r = 0.0;
		g = 0.0;
		b = 0.0; 
		a = 1.0;
		x = 0.0;
		y = 0.0;
		visible = true;
	}

	Actor::~Actor(){

	}

	GLdouble Actor::getX(){
		return x;
	}

	GLdouble Actor::getY(){
		return y;
	}

	void Actor::setColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a){
		Actor::r = r;
		Actor::g = g;
		Actor::b = b;
		Actor::a = a;
	}

	void Actor::setX(GLdouble x){
		Actor::x = x;
	}

	void Actor::setY(GLdouble y){
		Actor::y = y;
	}

	void Actor::render(){
		glPushMatrix();
		glColor4f(r, g, b, a);
		glTranslated(x, y, 0);
		draw();
		glPopMatrix();
	}

	void Actor::draw(){

	}

	void Actor::setVisible(boolean visible) {
		Actor::visible = visible;
	}

	boolean Actor::isVisible() {
		return visible;
	}