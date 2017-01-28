// Include standard headers
#include <stdio.h>
#include <stdlib.h>

#ifdef __APPLE__
	#  include <OpenGL/gl.h>
	#  include <OpenGL/glu.h>
	#  include <GLUT/glut.h>
	#else
	#  include <GL/gl.h>
	#  include <GL/glu.h>
	#  include <GL/glut.h>
	#endif


void display(void) 
{ 
	glClear( GL_COLOR_BUFFER_BIT); 
	glColor3f(0.0, 1.0, 0.0); 
	glBegin(GL_POLYGON); 
	glVertex3f(20.0, 40.0, 0.0); 
	glVertex3f(80.0, 40.0, 0.0); 
	glVertex3f(80.0, 60.0, 0.0); 
	glVertex3f(20.0, 60.0, 0.0); 
	glEnd(); 
	glFlush(); 
}

int main(int argc, char **argv) 
{ 
	printf("hello world\n"); 
	glutInit(&argc, argv); 
	glutInitDisplayMode ( GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

	// initialize window
	glutInitWindowPosition(100,100); 
	glutInitWindowSize(500,500); 
	glutCreateWindow ("SNAKE 2000");

	glClearColor(0.0, 0.0, 0.0, 0.0);         // black background 
	glMatrixMode(GL_PROJECTION);              // setup viewing projection 
	glLoadIdentity();                           // start with identity matrix 
	glOrtho(0.0, 500.0, 0.0, 500.0, 0.0, 500.0);   // setup a 10x10x2 viewing world

	glutDisplayFunc(display); 
	glutMainLoop();

	return 0; 
}