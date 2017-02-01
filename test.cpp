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
#define INIT_LENGTH		10	// initial length of snake (when game begins)
#define INIT_SPEED		150 // initial speed of snake (when game begins)
#define INIT_DIRECTION	0	// initial direction of snake (when game begins)

int food_x = 0;
int food_y = 0;

int score = 0;
int speed = INIT_SPEED;
int snake_length=INIT_LENGTH; // total length of snake
int length_increase = 1;
int direction=0; // 0=UP, 1=RIGHT, 2=DOWN, 3=LEFT
bool first = true;

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
			if(snake) {glColor3f(0.0, 1.0, 0.0);}
			else if(food) {glColor3f(1.0, 0.0, 0.0);}
			else{glColor3f(0.0, 0.0, 1.0);}
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
	if(first){
		printf("\n\n\n");
		printf(" .oooooo..o ooooo      ooo       .o.       oooo    oooo oooooooooooo \n");
		printf("d8P'    `Y8 `888b.     `8`      .888.      `888   .8P`  `888`     `8 \n");
		printf("Y88bo.       8 `88b.    8      .8`888.      888  d8`     888    \n");
		printf(" ``Y8888o.   8   `88b.  8     .8` `888.     88888[       888oooo8    \n");
		printf("     ``Y88b  8     `88b.8    .88ooo8888.    888`88b.     888    `   \n");
		printf("oo     .d8P  8       `888   .8'     `888.   888  `88b.   888       o \n");
		printf("8``88888P`  o8o        `8  o88o     o8888o o888o  o888o o888ooooood8 \n");
		printf("\n\n\n");
		printf("                      PRESS ~ENTER~ TO PLAY!\n\n\n");
		first = false;
	}
 
	glutTimerFunc(200.0, timer, 0);
}

void gameInitialize(){
	score = 0;
	snake_length = INIT_LENGTH; 
	direction = INIT_DIRECTION;
	speed = INIT_SPEED;
	for(int i=0; i<GAME_SIZE; i++){
		for(int j=0; j<GAME_SIZE; j++){
			GAME_GRID[i][j] = Square(i*GAME_SIZE,j*GAME_SIZE,SQUARE_UNIT);
		}
	}
	GAME_GRID[GAME_SIZE/2][GAME_SIZE/2] = Snake(GAME_SIZE/2*SQUARE_UNIT, GAME_SIZE/2*SQUARE_UNIT,SQUARE_UNIT);
	GAME_GRID[GAME_SIZE/2][GAME_SIZE/2].set_Number(GAME_GRID[GAME_SIZE/2][GAME_SIZE/2].get_Number()+1);

	srand(time(NULL));
	food_x = rand()%GAME_SIZE;
	food_y = rand()%GAME_SIZE;

	GAME_GRID[food_y][food_x] = Comida(food_x*SQUARE_UNIT, food_y*SQUARE_UNIT,SQUARE_UNIT);

	glEnd(); 
	glFlush(); 
	glutTimerFunc(speed, timer, 0);
	GAME_STATE = 2;	
}

void foodEaten() {
	if(score%5 == 0) {length_increase+=1;}
	score += 1;
	snake_length += length_increase;
	if(speed>10 && score%3 == 0) {speed -= 5;}
}

void playGame(){
	//std::cout << direction << std::endl;
	glColor3f(0.0, 1.0, 0.0); 
	glBegin(GL_POLYGON); 
	for(int i=0; i<GAME_SIZE; i++){
		bool up = false;
		for(int j=0; j<GAME_SIZE; j++){
			if(GAME_GRID[i][j].is_Snake()) {
				if(GAME_GRID[i][j].is_Head()==true){
					if(direction==0){ // UP
						//std::cout << "SQUARE ABOVE" << std::endl;
						if(!GAME_GRID[i+1][j].is_Snake() && (i+1)<GAME_SIZE) {
							if(GAME_GRID[i+1][j].is_Food()){
								foodEaten();

								food_x = rand()%GAME_SIZE;
								food_y = rand()%GAME_SIZE;

								GAME_GRID[food_y][food_x] = Comida(food_x*SQUARE_UNIT, food_y*SQUARE_UNIT,SQUARE_UNIT);
							}
							GAME_GRID[i+1][j]=Snake(j*SQUARE_UNIT,(i+1)*SQUARE_UNIT,SQUARE_UNIT);
							GAME_GRID[i+1][j].set_Head(true);
							GAME_GRID[i][j].set_Head(false);
						}
						else {GAME_STATE=3;} // GAME OVER
						up = true;
						break;
					}
					else if(direction==1){ // RIGHT
						//std::cout << "SQUARE RIGHT" << std::endl;
						if(!GAME_GRID[i][j+1].is_Snake() && (j+1)<GAME_SIZE) {
							if(GAME_GRID[i][j+1].is_Food()){
								foodEaten();

								srand(time(NULL));
								food_x = rand()%GAME_SIZE;
								food_y = rand()%GAME_SIZE;

								GAME_GRID[food_y][food_x] = Comida(food_x*SQUARE_UNIT, food_y*SQUARE_UNIT,SQUARE_UNIT);
							}
							GAME_GRID[i][j+1]=Snake((j+1)*SQUARE_UNIT,i*SQUARE_UNIT,SQUARE_UNIT);
							GAME_GRID[i][j+1].set_Head(true);
							GAME_GRID[i][j].set_Head(false);
						}
						else {GAME_STATE=3;} // GAME OVER
						break;
					}
					else if(direction==2){ // LEFT
						//std::cout << "SQUARE DOWN" << std::endl;
						if(!GAME_GRID[i-1][j].is_Snake() && (i-1)>=0) {
							if(GAME_GRID[i-1][j].is_Food()){
								foodEaten();

								food_x = rand()%GAME_SIZE;
								food_y = rand()%GAME_SIZE;

								GAME_GRID[food_y][food_x] = Comida(food_x*SQUARE_UNIT, food_y*SQUARE_UNIT,SQUARE_UNIT);
							}
							GAME_GRID[i-1][j]=Snake(j*SQUARE_UNIT,(i-1)*SQUARE_UNIT,SQUARE_UNIT);
							GAME_GRID[i-1][j].set_Head(true);
							GAME_GRID[i][j].set_Head(false);
						}
						else {GAME_STATE=3;} // GAME OVER
						break;
					}
					else if(direction == 3){ // DOWN
						//std::cout << "SQUARE LEFT" << std::endl;
						if(!GAME_GRID[i][j-1].is_Snake() && (j-1)>=0) {
							if(GAME_GRID[i][j-1].is_Food()){
								foodEaten();
								food_x = rand()%GAME_SIZE;
								food_y = rand()%GAME_SIZE;

								GAME_GRID[food_y][food_x] = Comida(food_x*SQUARE_UNIT, food_y*SQUARE_UNIT,SQUARE_UNIT);
							}
							GAME_GRID[i][j-1]=Snake((j-1)*SQUARE_UNIT,i*SQUARE_UNIT,SQUARE_UNIT);
							GAME_GRID[i][j-1].set_Head(true);
							GAME_GRID[i][j].set_Head(false);
						}
						else {GAME_STATE=3;} // GAME OVER
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
		}
	}		
	glEnd(); 
	glFlush(); 
	glutTimerFunc(speed, timer, 0);
}

void gameOver(){
	printf("                    ╔═╗╔═╗╔╦╗╔═╗  ╔═╗╦  ╦╔═╗╦═╗ \n");
	printf("                    ║ ╦╠═╣║║║║╣   ║ ║╚╗╔╝║╣ ╠╦╝\n");
	printf("                    ╚═╝╩ ╩╩ ╩╚═╝  ╚═╝ ╚╝ ╚═╝╩╚═\n");
	printf("                           SCORE: %d\n\n",score);

	/*char play_again = NULL;
	while(play_again!='y' && play_again!='n'){
		std::cout << "PLAY AGAIN? ('y' or 'n'): ";
		std::cin >> play_again; 
		std::cout << std::endl << std::endl << std::endl;
	}
	if(play_again == 'y') {GAME_STATE=0;}
	else {exit(1);}
	first=true;*/
	exit(1);
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
		case 3: // GAME OVER
			gameOver();
			break;
	} 
}

/***************************************************************/
/************************ KEYBOARD INPUT ***********************/
/***************************************************************/

void keySpecial(int key, int x, int y) {
	switch(key) {
		case 100 : 
			//printf("GLUT_KEY_LEFT %d\n",key);
			if(direction==0 || direction==2) {direction=3;}
			break;
		case 102: 
			//printf("GLUT_KEY_RIGHT %d\n",key);
			if(direction==0 || direction==2) {direction=1;}
			break;
		case 101: 
			//printf("GLUT_KEY_UP %d\n",key);
			if(direction==1 || direction==3) {direction=0;}
			break;
		case 103: 
			//printf("GLUT_KEY_DOWN %d\n",key);
			if(direction==1 || direction==3) {direction=2;}
			break;
	};
}

void keyNormal(unsigned char key, int x, int y) {
	switch(key) {
		case 13:
			//printf("GLUT_KEY_ENTER\n");
			if(GAME_STATE==0) GAME_STATE=1;
		break;
	}
}

int main(int argc, char **argv) {
	glutInit(&argc, argv); 
	glutInitDisplayMode ( GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

	// initialize window
	glutInitWindowPosition(0,0); 
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