// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#ifdef __APPLE__
	#  include <OpenGL/gl.h>
	#  include <OpenGL/glu.h>
	#  include <GLUT/glut.h>
	#else
	#  include <GL/gl.h>
	#  include <GL/glu.h>
	#  include <GL/glut.h>
	#endif

int GAME_STATE=1;
#define GAME_SIZE 		50	// # of squares in game
#define SQUARE_UNIT 	10	// size of sqaure in terms of pixels

int snake_length; // total length of snake
int direction=0; // 0=UP, 1=RIGHT, 2=DOWN, 3=LEFT

/***************************************************************/
/*************************** CLASSES ***************************/
/***************************************************************/

class Square {
	private:
    	double x, y;
    	int size;
    	bool empty;
  	public:
	    // constructors
	    Square(){}
	    Square(double x1, double y1, int size1){
			x = x1;
			y = y1;
			size = size1;
			empty = true;
		}

		// set functions
		void set_X(double x1) {x = x1;}
		void set_Y(double y1) {y = y1;}
		void set_Size(int s1) {size = s1;}
		void setEmpty(bool e) {empty = e;}

		// get functions
		double get_X() {return x;}
		double set_Y() {return y;}
		int set_Size() {return size;}
		bool isEmpty(){return empty;}

		void draw(){
			glClearColor(0.0, 50.0, 0.0, 0.0);
			glVertex3f(x, y, 0.0); 
			glVertex3f(x, y+size, 0.0); 
			glVertex3f(x+size, y+size, 0.0); 
			glVertex3f(x+size, y, 0.0);
		}

};

class Snake : public Square{
	private:
    	int number; // number in snake queue, when block is at tail, value is 0
    	bool head; // head of snake
    	bool tail; // tail of snake
  	public:
	  	// constructor
	    Snake(double x1, double y1, int s1, int num):Square(x1,y1,s1){
			number = num;
			setEmpty(false);
			set_Head(true);
			set_Tail(false);
		}

		// set functions
		void set_Number(int n) {number = n;}
		void set_Head(bool h) {head = h;}
		void set_Tail(bool t) {tail = t;}

		// get functions
		int get_Number() {return number;}
		bool is_Head() {return head;}
		bool is_Tail() {return tail;}
};

class Comida : public Square{
  	public:
  		// constructor
	    Comida(double x1, double y1, int s1):Square(x1,y1,s1){
	    	setEmpty(false);
		}
};


/***************************************************************/
/************************** GAME CODE **************************/
/***************************************************************/


Square GAME_GRID[GAME_SIZE][GAME_SIZE]; 

void timer(int)
{
    /* update animation */
    glutPostRedisplay();
}


// MAIN FUNCTION FOR GRAPHICS
void display(void) { 
	glClear( GL_COLOR_BUFFER_BIT); 
	switch(GAME_STATE){
		case 0: // SPLASH
			glColor3f(0.0, 1.0, 0.0); 
			glBegin(GL_POLYGON); 
			GAME_GRID[GAME_SIZE/2][GAME_SIZE/2] = Snake(GAME_SIZE/2*SQUARE_UNIT+30, GAME_SIZE/2*SQUARE_UNIT+30,SQUARE_UNIT,0);
			GAME_GRID[GAME_SIZE/2][GAME_SIZE/2].draw();
			glEnd(); 
			glFlush(); 
			GAME_STATE=1;
			glutTimerFunc(1000.0, timer, 0);
			break;
		case 1: // PLAY GAME
			std::cout << direction << std::endl;
			glColor3f(0.0, 1.0, 0.0); 
			glBegin(GL_POLYGON); 
			for(int i=0; i<GAME_SIZE; i++){
				bool down = false;
				for(int j=0; j<GAME_SIZE; j++){
					if(!GAME_GRID[i][j].isEmpty()) {
						//GAME_GRID[i][j].draw();
							if(direction==0){
								std::cout << "SQUARE ABOVE" << std::endl;
								GAME_GRID[i+1][j]=Snake(j*SQUARE_UNIT,i*SQUARE_UNIT+SQUARE_UNIT,SQUARE_UNIT,0);
								GAME_GRID[i][j].setEmpty(true);
								down = true;
								break;
							}
							else if(direction==1){
								std::cout << "SQUARE RIGHT" << std::endl;
								GAME_GRID[i][j+1]=Snake(j*SQUARE_UNIT+SQUARE_UNIT,i*SQUARE_UNIT,SQUARE_UNIT,0);
								GAME_GRID[i][j].setEmpty(true);
								break;
							}
							else if(direction==2){
								std::cout << "SQUARE DOWN" << std::endl;
								GAME_GRID[i-1][j]=Snake(j*SQUARE_UNIT,i*SQUARE_UNIT-SQUARE_UNIT,SQUARE_UNIT,0);
								GAME_GRID[i][j].setEmpty(true);
								
								break;
							}
							else{
								std::cout << "SQUARE LEFT" << std::endl;
								GAME_GRID[i][j-1]=Snake(j*SQUARE_UNIT-SQUARE_UNIT,i*SQUARE_UNIT,SQUARE_UNIT,0);
								GAME_GRID[i][j].setEmpty(true);
								break;
							}
					}
				}
				if(down==true){break;}
			}
			for(int i=0; i<GAME_SIZE; i++){
				for(int j=0; j<GAME_SIZE; j++){
					if(!GAME_GRID[i][j].isEmpty()) {
						GAME_GRID[i][j].draw();
					}
				}
			}		
			//GAME_GRID[GAME_SIZE/2][GAME_SIZE/2].draw();
			glEnd(); 
			glFlush(); 
			//GAME_STATE=1;
			glutTimerFunc(200.0, timer, 0);
			break;
	} 
}

void keySpecial(int key, int x, int y) {
	switch(key) {
		case 100 : 
			printf("GLUT_KEY_LEFT %d\n",key);
			if(direction==0 || direction==2) {direction=3;}
			break;
		case 102: 
			printf("GLUT_KEY_RIGHT %d\n",key);
			if(direction==0 || direction==2) {direction=1;}
			break;
		case 101: 
			printf("GLUT_KEY_UP %d\n",key);
			if(direction==1 || direction==3) {direction=0;}
			break;
		case 103: 
			printf("GLUT_KEY_DOWN %d\n",key);
			if(direction==1 || direction==3) {direction=2;}
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

	for(int i=0; i<GAME_SIZE; i++){
		for(int j=0; j<GAME_SIZE; j++){
			GAME_GRID[i][j] = Square(i*GAME_SIZE,j*GAME_SIZE,SQUARE_UNIT);
		}
	}
	GAME_GRID[GAME_SIZE/2][GAME_SIZE/2] = Snake(GAME_SIZE/2*SQUARE_UNIT, GAME_SIZE/2*SQUARE_UNIT,SQUARE_UNIT,0);

	glutDisplayFunc(display); 
	glutMainLoop();

	return 0; 
}