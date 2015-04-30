#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include <GL/freeglut.h>
//#include <GL/glut.h>

#include <iostream>
using namespace std;

// Freeglut parameters
// Flag telling us to keep processing events
// bool continue_in_main_loop= true; //(**)

// Viewport size
int WIDTH= 500, HEIGHT= 250;

// Scene visible area size
GLdouble xLeft= 0.0, xRight= 500.0, yBot= 0.0, yTop= 250.0;

// Scene variables
GLdouble xTriangle= 100.0, yTriangle= 100.0;
GLdouble triangleWidth= 100.0, triangleHeight= 50.0;


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

  // Scene rendering
  glBegin ( GL_TRIANGLES ) ;
       glVertex2d( xTriangle, yTriangle );
       glVertex2d( xTriangle + triangleWidth, yTriangle );
       glVertex2d( xTriangle + triangleWidth, yTriangle + triangleHeight );
  glEnd () ;

  glFlush();
  glutSwapBuffers();
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

}


void key(unsigned char key, int x, int y){
 
  bool need_redisplay = true;

  switch (key) {
  case 27:  /* Escape key */
    //continue_in_main_loop = false; // (**)
	glutLeaveMainLoop (); //Freeglut's sentence for stopping glut's main loop (*)
    break;

  case '+' :
    xTriangle += 10.0;
    break ;

  case '-' :
    xTriangle -= 10.0;
    break ;

  default:
    need_redisplay = false;
    break;
  }//switch

  if (need_redisplay)
    glutPostRedisplay();
}


void mouse(int button, int state, int x, int y){
	if ((button==GLUT_LEFT_BUTTON) && (state==GLUT_DOWN))
		cout << x << '\t' << y << endl;
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
  my_window = glutCreateWindow( "Freeglut 2D-project" );
    
  //Callback registration
  glutReshapeFunc(resize);
  glutKeyboardFunc(key);
  glutDisplayFunc(display);
  glutMouseFunc(mouse);


  //OpenGL basic setting
  intitGL();


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
