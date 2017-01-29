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

int direction = 0; // 0=UP, 1=RIGHT, 2=DOWN, 3=LEFT

class Square {
	private:
    	double x, y;
    	int size;
  	public:
  		Square(double,double,int);
    	void set_values(double,double,int);
    	void draw();

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
	}
};

class Snake {
	private:
    	int direction;
    	int length;
    	int unit_length;
    	double grid[][];
  	public:
  		Snake(int, int);
    	void set_values(int);
    	void draw();

    Snake(int d, int ul, int l){
		direction=d
		unit_length=ul
		length=l
	}

	// set functions
	void set_Direction(int d) {direction = d;}
	void set_UnitLength(int ul) {unit_length = ul;}
	void set_Length(int l) {length = l;}

	// get functions
	int get_Direction() {return direction;}
	int set_UnitLength() {return unit_length;}
	int set_Length() {return length;}

	void draw(){
		glVertex3f(x, y, 0.0); 
		glVertex3f(x, y+size, 0.0); 
		glVertex3f(x+size, y+size, 0.0); 
		glVertex3f(x+size, y, 0.0);
	}
};

void display(void) { 
	glClear( GL_COLOR_BUFFER_BIT); 
	glColor3f(0.0, 1.0, 0.0); 
	glBegin(GL_POLYGON); 
	Square* r = new Square(0.0,0.0,10);
	r->draw();
	glEnd(); 
	glFlush(); 
}

void keySpecial(int key, int x, int y) {
	switch(key) {
		case 27 :      break;
		case 100 : 
			printf("GLUT_KEY_LEFT %d\n",key);
			direction=3;  
			break;
		case 102: 
			printf("GLUT_KEY_RIGHT %d\n",key);
			direction=1;  
			break;
		case 101: 
			printf("GLUT_KEY_UP %d\n",key);
			direction=0;
			break;
		case 103: 
			printf("GLUT_KEY_DOWN %d\n",key);
			direction=2;
			break;
	};
	glutPostRedisplay(); 
}

int main(int argc, char **argv) {
	printf("hello world\n"); 
	glutInit(&argc, argv); 
	glutInitDisplayMode ( GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

	// initialize window
	glutInitWindowPosition(100,100); 
	glutInitWindowSize(500,500); 
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