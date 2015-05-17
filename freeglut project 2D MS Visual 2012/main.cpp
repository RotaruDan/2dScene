#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include <GL/freeglut.h>
#include "Group.h"
#include "Triangle.h"
#include "Image.h"
#include "TextureManagement.h"
//#include <GL/glut.h>

#include <iostream>
using namespace std;

// Freeglut parameters
// Flag telling us to keep processing events
// bool continue_in_main_loop= true; //(**)

// Viewport size
int WIDTH= 500, HEIGHT= 250;

int animationPeriod = 1000;

boolean animating = true;
// Scene visible area size
GLdouble xLeft= 0.0, xRight= 500.0, yBot= 0.0, yTop= 250.0;

Group root;
Group triangles;
Triangle * triangle;
Image image;

Mode mode;
GLuint textureID;

void intitGL(){

	glClearColor(1.0,1.0,1.0,1.0);
	glColor3f(1.0,0.0,0.0); 

	glPointSize(4.0);
	glLineWidth(2.0);

	// Viewport
    glViewport(0, 0, WIDTH, HEIGHT);
    
	// Model transformation
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Scene Visible Area
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(xLeft, xRight, yBot, yTop); 
 }


void display(void){
  glClear( GL_COLOR_BUFFER_BIT );

  root.render();

  glFlush();
  glutSwapBuffers();
}

void animate(int value){
	if(animating) {
		vector<Actor*> children = triangles.getChildren();
		unsigned int i, size = children.size();
		for(i = 0; i < size; ++i){
			Triangle* child = (Triangle*) children[i];
			(*child).move();
		}
	
		glutTimerFunc(animationPeriod, animate, 1);
		glutPostRedisplay();
	}
}

void resize(int newWidth, int newHeight){
  //GLdouble widthScale= WIDTH/(xRight-xLeft);
  //GLdouble heightScale= HEIGHT/(yTop-yBot);
  
  //Resize Scene Visible Area 
  //Width and height scale remain
  GLdouble newSVAWidth= newWidth*(xRight-xLeft)/WIDTH; //= newWidth/widthScale
  GLdouble newSVAHeight= newHeight*(yTop-yBot)/HEIGHT; //= newHeight/heightScale

  GLdouble xMiddle= ( xLeft+xRight )/2.0;
  xRight= xMiddle + newSVAWidth/2.0;
  xLeft=  xMiddle - newSVAWidth/2.0;
  
  GLdouble yMiddle= ( yBot+yTop )/2.0;
  yTop= yMiddle + newSVAHeight/2.0;
  yBot= yMiddle - newSVAHeight/2.0;

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(xLeft, xRight, yBot, yTop);

  //Resize Viewport
  WIDTH= newWidth;
  HEIGHT= newHeight;
  glViewport ( 0, 0, WIDTH, HEIGHT ) ;
  
  image.setSize((float) WIDTH, (float) HEIGHT);
}


void changeMode(Mode newMode) {
	mode = newMode;
	vector<Actor*> children = triangles.getChildren();
	unsigned int i, size = children.size();
	for(i = 0; i < size; ++i){
		Triangle* child = (Triangle*) children[i];
		(*child).setMode(newMode);
	}
}

void key(unsigned char key, int x, int y){
 
  bool need_redisplay = true;
  switch (key) {
  case 27:  /* Escape key */
    //continue_in_main_loop = false; // (**)
	glutLeaveMainLoop (); //Freeglut's sentence for stopping glut's main loop (*)
    break;

  case 'a' :
	changeMode(ANIMATE);
    image.setVisible(false);	
	if(animating) {
		animate(1);
	}
    break ;

  case 's' :
	  
    if(mode == ANIMATE) {
		animating = !animating;
		if(animating) {
			animate(1);
		}
	} else {
		changeMode(SELECT);
		image.setVisible(false);
	}
    break ;
	
  case 'd' :
    changeMode(DESIGN);
    image.setVisible(true);
    break ;

  default:
    need_redisplay = false;
    break;
  }//switch

  if (need_redisplay)
    glutPostRedisplay();
}


void mouse(int button, int state, int x, int y){
	if ((button==GLUT_LEFT_BUTTON) && (state==GLUT_DOWN)) {
		cout << "Screen: " << x << '\t' << y << endl;

	/*
	Area visible de la escena (virtual) -> X, Y
	Area de Vista -> X', Y'

	pasar de X', Y' a X, Y :

	X = xLeft + ((xRight-xLeft) / WIDTH) * X'

	El S.O. devuelve las coordenadas de la Y' teniendo el origen de coordenadas arriba a la izquierda
	Y = yTop - ((yTop-yBottom) / HEIGHT) * Y'
	*/
		GLfloat worldX, worldY;

		worldX = xLeft + ((xRight - xLeft) / (float) WIDTH) * x;
		worldY = yTop - ((yTop - yBot) / (float) HEIGHT) * y;
		
		cout << "World: " << worldX << '\t' << worldY << endl << endl;

		if(mode == DESIGN) {
			if(triangle != NULL) {
				triangle->firstVertex(worldX, worldY);
				triangle->computeTexCoords((float) WIDTH, (float) HEIGHT);
				triangle->computeBarycenter();
			}
		} else if(mode == SELECT) {
			vector<Actor*> children = triangles.getChildren();
			unsigned int i, size = children.size();
			boolean selected = false;
			for(i = 0; i < size; ++i){
				Triangle* child = (Triangle*) children[i];
				if(!selected && (*child).hit(worldX, worldY)) {
					selected = true;
					triangle = child;
					triangle->setSelected(true);
					break;
				} else {
					(*child).setSelected(false);
				}
			}
			if(!selected) {
				triangle = NULL;
			}
		} else if (mode == ANIMATE) {

		}
	}
}



int main(int argc, char *argv[]){
  cout<< "Starting console..." << endl;

  int my_window; //my window's identifier

  //Initialization
  glutInitWindowSize(WIDTH, HEIGHT);
  glutInitWindowPosition (140, 140);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE );
  glutInit(&argc, argv);

  //Window construction
  my_window = glutCreateWindow( "Pr�ctica 3" );
    
  //Callback registration
  glutReshapeFunc(resize);
  glutKeyboardFunc(key);
  glutDisplayFunc(display);
  glutMouseFunc(mouse);


  //OpenGL basic setting
  intitGL();

   /* initialize random seed: */
  srand (time(NULL));

  unsigned int width, heignt;
  initTexture(textureID, width, heignt, "ray.bmp");

  image.setSize((float) WIDTH, (float) HEIGHT);
  image.setTextureId(textureID);
  image.setColor(1, 0, 0, 1);

  root.addChildren(&image);

  vector<PV2D> vertex;
  PV2D v1(100, 100);
  vertex.push_back(v1);
  PV2D v2(200, 100);
  vertex.push_back(v2);
  PV2D v3(200, 150);
  vertex.push_back(v3);
  Triangle triang;
  triang.setVertex(vertex);
  triang.setColor(1, 0, 0, 1);
  triang.setTextureId(textureID);
  triang.computeTexCoords((float) WIDTH, (float) HEIGHT);
  triang.computeBarycenter();
  triang.setDirection(rand(), rand());
  triangle = &triang;

  triangles.addChildren(triangle);
  root.addChildren(&triangles);

  changeMode(DESIGN);
  


  // Freeglut's main loop can be stopped executing (**)
  //while ( continue_in_main_loop )
  //  glutMainLoopEvent();

  // Classic glut's main loop can be stopped after X-closing the window,
  // using the following freeglut's setting (*)
  glutSetOption ( GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION ) ;
    
  // Classic glut's main loop can be stopped in freeglut using (*)
  glutMainLoop(); 
  
  // We would never reach this point using classic glut
  system("PAUSE"); 
   
  return 0;
}
