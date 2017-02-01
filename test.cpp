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

int GAME_STATE=0;
#define GAME_SIZE 		50	// # of squares in game
#define SQUARE_UNIT 	10	// size of sqaure in terms of pixels

int snake_length=10; // total length of snake
int direction=0; // 0=UP, 1=RIGHT, 2=DOWN, 3=LEFT

int food_x = 0;
int food_y = 0;

/***************************************************************/
/*************************** CLASSES ***************************/
/***************************************************************/

class Square {
	private:
    	double x, y;
    	int size;
    	bool snake;
    	bool food;
    	int number; // number in snake queue, when block is at tail, value is 0
    	bool head;
  	public:
	    // constructors
	    Square(){}
	    Square(double x1, double y1, int size1){
			x = x1;
			y = y1;
			size = size1;
			snake = false;
			number = 0;
			head = false;
			food = false;
		}

		// set functions
		void set_X(double x1) {x = x1;}
		void set_Y(double y1) {y = y1;}
		void set_Size(int s1) {size = s1;}
		void set_Snake(bool s) {snake = s;}
		void set_Food(bool f) {food = f;}
		void set_Head(bool h) {head = h;}
		void set_Number(int n) {number = n;}

		// get functions
		double get_X() {return x;}
		double get_Y() {return y;}
		int get_Size() {return size;}
		bool is_Snake(){return snake;}
		bool is_Food(){return food;}
		bool is_Head(){return head;}
		int get_Number() {return number;}

		void draw(){
			glBegin(GL_POLYGON);
			if(snake) {glClearColor(0.0, 50.0, 0.0, 0.0);}
			else if(food) {glClearColor(50.0, 0.0, 0.0, 0.0);}
			else{glClearColor(0.0, 0.0, 0.0, 50.0);}
			glVertex2f(x, y); 
			glVertex2f(x, y+size); 
			glVertex2f(x+size, y+size); 
			glVertex2f(x+size, y);	
			glEnd();
		}

};

class Snake : public Square{
  	public:
	  	// constructor
	    Snake(double x1, double y1, int s1):Square(x1,y1,s1){
			set_Number(0);
			set_Snake(true);
			set_Head(true);
			set_Food(false);
		}
};

class Comida : public Square{
  	public:
  		// constructor
	    Comida(double x1, double y1, int s1):Square(x1,y1,s1){
	    	set_Snake(false);
	    	set_Food(true);
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

void splashPage(){
	glEnd(); 
	glFlush(); 
	printf("%d %d\n", food_x,food_y);
	glutTimerFunc(200.0, timer, 0);
}

void gameInitialize(){
	glColor3f(0.0, 1.0, 0.0);
	direction = 0;
	for(int i=0; i<GAME_SIZE; i++){
		for(int j=0; j<GAME_SIZE; j++){
			GAME_GRID[i][j] = Square(i*GAME_SIZE,j*GAME_SIZE,SQUARE_UNIT);
		}
	}
	GAME_GRID[GAME_SIZE/2][GAME_SIZE/2] = Snake(GAME_SIZE/2*SQUARE_UNIT, GAME_SIZE/2*SQUARE_UNIT,SQUARE_UNIT);
	GAME_GRID[GAME_SIZE/2][GAME_SIZE/2].set_Number(GAME_GRID[GAME_SIZE/2][GAME_SIZE/2].get_Number()+1);
	//GAME_GRID[GAME_SIZE/2][GAME_SIZE/2].draw();
	//GAME_GRID[food_y][food_x].draw();
	srand(time(NULL));
	food_x = rand()%GAME_SIZE;
	food_y = rand()%GAME_SIZE;

	GAME_GRID[food_y][food_x] = Comida(food_x*SQUARE_UNIT, food_y*SQUARE_UNIT,SQUARE_UNIT);

	glEnd(); 
	glFlush(); 
	glutTimerFunc(200.0, timer, 0);
	GAME_STATE = 2;	
}

void playGame(){
	std::cout << direction << std::endl;
	glColor3f(0.0, 1.0, 0.0); 
	glBegin(GL_POLYGON); 
	for(int i=0; i<GAME_SIZE; i++){
		bool up = false;
		for(int j=0; j<GAME_SIZE; j++){
			if(GAME_GRID[i][j].is_Snake()) {
				//std::cout << GAME_GRID[i][j].get_Number() << " ?= " << snake_length << std::endl;
				if(GAME_GRID[i][j].is_Head()==true){
					if(direction==0){ // UP
						std::cout << "SQUARE ABOVE" << std::endl;
						if(!GAME_GRID[i+1][j].is_Snake() && (i+1)<GAME_SIZE) {
							if(GAME_GRID[i+1][j].is_Food()){
								snake_length += 1;
								food_x = rand()%GAME_SIZE;
								food_y = rand()%GAME_SIZE;

								GAME_GRID[food_y][food_x] = Comida(food_x*SQUARE_UNIT, food_y*SQUARE_UNIT,SQUARE_UNIT);
							}
							GAME_GRID[i+1][j]=Snake(j*SQUARE_UNIT,(i+1)*SQUARE_UNIT,SQUARE_UNIT);
							GAME_GRID[i+1][j].set_Head(true);
							GAME_GRID[i][j].set_Head(false);
						}
						else{
							std::cout << "GAME OVER" << std::endl;
							GAME_STATE=0;
						}
						up = true;
						break;
					}
					else if(direction==1){ // RIGHT
						std::cout << "SQUARE RIGHT" << std::endl;
						if(!GAME_GRID[i][j+1].is_Snake() && (j+1)<GAME_SIZE) {
							if(GAME_GRID[i][j+1].is_Food()){
								snake_length += 1;
								srand(time(NULL));
								food_x = rand()%GAME_SIZE;
								food_y = rand()%GAME_SIZE;

								GAME_GRID[food_y][food_x] = Comida(food_x*SQUARE_UNIT, food_y*SQUARE_UNIT,SQUARE_UNIT);
							}
							GAME_GRID[i][j+1]=Snake((j+1)*SQUARE_UNIT,i*SQUARE_UNIT,SQUARE_UNIT);
							GAME_GRID[i][j+1].set_Head(true);
							GAME_GRID[i][j].set_Head(false);
						}
						else{
							std::cout << "GAME OVER" << std::endl;
							GAME_STATE=0;
						}
						break;
					}
					else if(direction==2){ // LEFT
						std::cout << "SQUARE DOWN" << std::endl;
						if(!GAME_GRID[i-1][j].is_Snake() && (i-1)>=0) {
							if(GAME_GRID[i-1][j].is_Food()){
								snake_length += 1;
								food_x = rand()%GAME_SIZE;
								food_y = rand()%GAME_SIZE;

								GAME_GRID[food_y][food_x] = Comida(food_x*SQUARE_UNIT, food_y*SQUARE_UNIT,SQUARE_UNIT);
							}
							GAME_GRID[i-1][j]=Snake(j*SQUARE_UNIT,(i-1)*SQUARE_UNIT,SQUARE_UNIT);
							GAME_GRID[i-1][j].set_Head(true);
							GAME_GRID[i][j].set_Head(false);
						}
						else{
							std::cout << "GAME OVER" << std::endl;
							GAME_STATE=0;
						}
						break;
					}
					else if(direction == 3){ // DOWN
						std::cout << "SQUARE LEFT" << std::endl;
						if(!GAME_GRID[i][j-1].is_Snake() && (j-1)>=0) {
							if(GAME_GRID[i][j-1].is_Food()){
								snake_length += 1;
								food_x = rand()%GAME_SIZE;
								food_y = rand()%GAME_SIZE;

								GAME_GRID[food_y][food_x] = Comida(food_x*SQUARE_UNIT, food_y*SQUARE_UNIT,SQUARE_UNIT);
							}
							GAME_GRID[i][j-1]=Snake((j-1)*SQUARE_UNIT,i*SQUARE_UNIT,SQUARE_UNIT);
							GAME_GRID[i][j-1].set_Head(true);
							GAME_GRID[i][j].set_Head(false);
						}
						else{
							std::cout << "GAME OVER" << std::endl;
							GAME_STATE=0;
						}
						break;
					}
				}
			}
		}
		if(up==true){break;}
	}
	for(int i=0; i<GAME_SIZE; i++){
		for(int j=0; j<GAME_SIZE; j++){
			if(GAME_GRID[i][j].is_Snake() || GAME_GRID[i][j].is_Food()) {
				GAME_GRID[i][j].draw();
			}
			if(GAME_GRID[i][j].get_Number()==snake_length) {
				GAME_GRID[i][j] = Square(j*SQUARE_UNIT,i*SQUARE_UNIT,SQUARE_UNIT);\
				GAME_GRID[i][j].set_Snake(false);
			}
			if(GAME_GRID[i][j].is_Snake()) {GAME_GRID[i][j].set_Number(GAME_GRID[i][j].get_Number()+1);}
			if(GAME_GRID[i][j].get_Number() != 0) {std::cout << GAME_GRID[i][j].get_Number();}
			//std::cout << GAME_GRID[i][j].get_Number() << std::endl;
		}
	}		
	//GAME_GRID[GAME_SIZE/2][GAME_SIZE/2].draw();
	//GAME_STATE=1;
	glEnd(); 
	glFlush(); 
	glutTimerFunc(100.0, timer, 0);
}

// MAIN FUNCTION FOR GRAPHICS
void display(void) { 
	glClear( GL_COLOR_BUFFER_BIT); 
	switch(GAME_STATE){
		case 0: // SPLASH
			splashPage();
			break;
		case 1: // INITIALIZE GAME
			gameInitialize();
			break;
		case 2: // PLAY GAME
			playGame();
			break;
	} 
}

/***************************************************************/
/************************ KEYBOARD INPUT ***********************/
/***************************************************************/

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

void keyNormal(unsigned char key, int x, int y) {
	switch(key) {
		case 13:
			printf("GLUT_KEY_ENTER\n");
			if(GAME_STATE==0) GAME_STATE=1;
		break;
	}
}

int main(int argc, char **argv) {
	printf("hello world\n"); 
	glutInit(&argc, argv); 
	glutInitDisplayMode ( GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

	// initialize window
	glutInitWindowPosition(GAME_SIZE*SQUARE_UNIT,GAME_SIZE*SQUARE_UNIT); 
	glutInitWindowSize(GAME_SIZE*SQUARE_UNIT,GAME_SIZE*SQUARE_UNIT); 
	glutCreateWindow ("SNAKE 2000");

	glutSpecialFunc(keySpecial);
	glutKeyboardFunc(keyNormal);
   
	glClearColor(0.0, 0.0, 0.0, 0.0);         // black background 
	glMatrixMode(GL_PROJECTION);              // setup viewing projection 
	glLoadIdentity();                           // start with identity matrix 
	glOrtho(0.0, 500.0, 0.0, 500.0, 0.0, 500.0);   // setup a 10x10x2 viewing world

	glutDisplayFunc(display); 
	glutMainLoop();

	return 0; 
}