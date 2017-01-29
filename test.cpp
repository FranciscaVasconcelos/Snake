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

#define GAME_STATE 		1	// 0=splash page, 1=play game
#define GAME_SIZE 		50	// # of squares in game
#define SQUARE_UNIT 	10	// size of sqaure in terms of pixels

/***************************************************************/
/*************************** CLASSES ***************************/
/***************************************************************/

class Square {
	private:
    	double x, y;
    	int size;
  	public:
	    // constructor
	    Square(double x1, double y1, int size1){
			x = x1;
			y = y1;
			size = size1;
		}

		// set functions
		void set_X(double x1) {x = x1;}
		void set_Y(double y1) {y = y1;}
		void set_Size(int s1) {size = s1;}

		// get functions
		double get_X() {return x;}
		double set_Y() {return y;}
		int set_Size() {return size;}

		void draw(){
			glVertex3f(x, y, 0.0); 
			glVertex3f(x, y+size, 0.0); 
			glVertex3f(x+size, y+size, 0.0); 
			glVertex3f(x+size, y, 0.0);
			glutPostRedisplay();
		}
};

class Snake : public Square{
	private:
    	int number; // number in snake queue, when block is at tail, value is 0
  	public:
	  	// constructor
	    Snake(double x1, double y1, int s1, int num):Square(x1,y1,s1){
			number = num;
		}

		// set functions
		void set_Number(int n) {number = n;}

		// get functions
		int get_Number() {return number;}

};

class Comida : public Square{
  	public:
  		// constructor
	    Comida(double x1, double y1, int s1):Square(x1,y1,s1){
		}
};


/***************************************************************/
/************************** GAME CODE **************************/
/***************************************************************/



Square *GAME_GRID[GAME_SIZE][GAME_SIZE] = {NULL};

void display(void) { 
	glClear( GL_COLOR_BUFFER_BIT); 
	glColor3f(0.0, 1.0, 0.0); 
	switch(GAME_STATE){
		case 0: // SPLASH
			break;
		case 1: // PlAY GAME
			break;
	} 
	glutPostRedisplay();
	glEnd(); 
	glFlush();
}

void keySpecial(int key, int x, int y) {
	switch(key) {
		case 100 : 
			printf("GLUT_KEY_LEFT %d\n",key);
			break;
		case 102: 
			printf("GLUT_KEY_RIGHT %d\n",key);
			break;
		case 101: 
			printf("GLUT_KEY_UP %d\n",key);
			break;
		case 103: 
			printf("GLUT_KEY_DOWN %d\n",key);
			break;
	};
}

int main(int argc, char **argv) {
	printf("hello world\n"); 
	glutInit(&argc, argv); 
	glutInitDisplayMode ( GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

	// initialize window
	glutInitWindowPosition(100,100); 
	glutInitWindowSize(GAME_SIZE*SQUARE_UNIT,GAME_SIZE*SQUARE_UNIT); 
	glutCreateWindow ("SNAKE 2000");

	glutSpecialFunc(keySpecial);
   
	glClearColor(0.0, 0.0, 0.0, 0.0);         // black background 
	glMatrixMode(GL_PROJECTION);              // setup viewing projection 
	glLoadIdentity();                           // start with identity matrix 
	glOrtho(0.0, 500.0, 0.0, 500.0, 0.0, 500.0);   // setup a 10x10x2 viewing world
	 

	glutDisplayFunc(display); 
	glutMainLoop();

	return 0; 
}