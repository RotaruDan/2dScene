//---------------------------------------------------------------------------
// Dan Cristian, Rotaru
//---------------------------------------------------------------------------
#ifndef ActorH
#define ActorH

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

class Actor{

	private:
		GLdouble x, y;
		boolean visible;

	protected:
		GLfloat r, g, b, a;

	public:
		Actor();
		~Actor();

		GLint getAngle();
		GLdouble getAngleX();
		GLdouble getAngleY();

		GLdouble getX();
		GLdouble getY();
		
		void setColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a);

		void setX(GLdouble x);
		void setY(GLdouble y);

		void render();

		virtual void draw();
		void setVisible(boolean visible);
		boolean isVisible();
};

#endif