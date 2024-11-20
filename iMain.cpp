# include "iGraphics.h"

enum PlayerState {ground, jump, fall, on_block};
enum GameState {main_menu, pause, play, game_over, settings, leaderboards};

int Time = 0;
int playerX = 400;
int playerY = 200;
int playerW = 60;
int playerH = 60;
PlayerState playerstate = ground;
GameState gamestate = pause;

int dy = 60;
int gnd_1st_x = 10; int gnd_1st_width = 220;
int gnd_2nd_x = 230;
int gamespeed = 30;

typedef struct{
	int x;
	int y;
	
	int ti;
	int done;

	int w;
	int h;
}RecObstacles;

int RecObsNo = 4;
RecObstacles rec_obs[] = {
	{1850,200,10,0,60,60},
	{1850,200,30,0,120,120}, // gamespeed = 30. obs width = 60. so, 2 unit time gap taken
	
	{1850,200,70,0,400,60},
	{1850,200,90,0,60,400},
	
	
};

void updateObstacle();
void drawObstacle();
void updateGround();
void drawGround();
void updatePos();
void checkCollision();
void updateTimers();
void removeObs();


void iDraw() {

	iClear();
	switch(gamestate){
		case play:  drawGround();
					drawObstacle();
					iSetColor(252, 231, 3);	
					iFilledRectangle(playerX, playerY, 60, 60);


					
	}
}

/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
	*/
void iMouseMove(int mx, int my) {
	
	//place your codes here
}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
	*/
void iMouse(int button, int state, int mx, int my) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		//place your codes here
		//	printf("x = %d, y= %d\n",mx,my);
		
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		//place your codes here
		
	}
}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
	*/
void iKeyboard(unsigned char key) {
	if (key == 'q') {
		exit(0);
	}
	if(key == 'p'){
		gamestate = pause; 
	}
	if(key == 'r'){
		gamestate = play;
	}
	
	//place your codes for other keys here
}

// check iMainCopy.cpp if needed
void iSpecialKeyboard(unsigned char key) {

	if (key == GLUT_KEY_END) {
		exit(0);
	}
	if (key == GLUT_KEY_UP) {
		if(playerstate == ground){
			playerstate = jump;
		}
	}
	//place your codes for other keys here
}




int main() {
	//place your own initialization codes here.
	iSetTimer(50, updatePos);
	iSetTimer(50, updateGround);
	iSetTimer(50, updateObstacle);
	iSetTimer(50, checkCollision);
	iSetTimer(50, updateTimers);
	iInitialize(1850, 950, "Geometry Dash");
	return 0;
}

void updatePos(){
	switch(playerstate){

	case jump:
		playerY += dy;
		dy -= 10;
				
		if(playerY < 260){
			dy = 60;
			playerstate = ground;
		}
		break;

	case on_block:
		dy = 60;
		break;
	}


	// if(state == fall){

	// }
}


void updateObstacle(){
	int i;
	for(int i = 0; i < RecObsNo; i++){
		if(rec_obs[i].ti <= Time && !rec_obs[i].done) {
			rec_obs[i].x -= gamespeed;
		}
		if(rec_obs[i].x < 0) rec_obs[i].done = 1;
	}

	Time += 1;

}

void drawObstacle(){
	int i;
	iSetColor(252, 3, 65);
	for(i = 0; i < RecObsNo; i++){ // this condition can be made better using 1) done and 2) time
		if(rec_obs[i].ti <= Time && !rec_obs[i].done) {
			iFilledRectangle(rec_obs[i].x, rec_obs[i].y, rec_obs[i].w, rec_obs[i].h);
		}
	}
}


void checkCollision(){
	// there is some glitch. i managed to collide with first 3 obstacles on a run, yet game was on
	// also, if i keep up pressed, the ground obstacles are not detected

	// checks collision as well as landing
	int i;
	for(i = 0; i < RecObsNo; i++){
		// if(dy < 0 ){ // playerstate == jump is redundant
		// 	if(playerX + playerW >= rec_obs[i].x && playerX <= rec_obs[i].x + rec_obs[i].w && playerY <= rec_obs[i].y+rec_obs[i].h) {
		// 		playerstate = on_block; 
		// 		printf("onblock");
		// 	}
		// }

		// else if(playerstate == ground && playerX + playerW >= rec_obs[i].x && playerX <= rec_obs[i].x &&
		// 	playerY == rec_obs[i].y) {
		// 	gamestate = game_over;
		// 	printf("crashed");
		// }

		// else if(playerstate == ground && playerX + playerW >= rec_obs[i].x && playerX <= rec_obs[i].x && playerY <= rec_obs[i].y + rec_obs[i].h && playerY > rec_obs[i].y ) {
		// 	gamestate = game_over;
		// 	printf("crashed");
		// }

		// collision with floating blocks left

		// overlapping widths
		if(playerX < rec_obs[i].x + rec_obs[i].w 
			&& playerX + playerW > rec_obs[i].x){

				// landing
				if(dy < 0 && playerY <= rec_obs[i].y + rec_obs[i].h){
					playerstate = on_block;
					dy = 60;
				}

				else if(playerY < rec_obs[i].y + rec_obs[i].h 
						&& playerY + playerH > rec_obs[i].y){
						gamestate = game_over;
				}

				
		}


		

		
	}
}

void removeObs(){

}


void updateTimers(){
	switch(gamestate){
	case pause:
				iPauseTimer(0);
				iPauseTimer(1);
				iPauseTimer(2);
				iPauseTimer(3);
				break;
	case play:
				iResumeTimer(0);
				iResumeTimer(1);
				iResumeTimer(2);
				iResumeTimer(3);
				break;
	case game_over:
				iPauseTimer(0);
				iPauseTimer(1);
				iPauseTimer(2);
				iPauseTimer(3);
				break;
	
	}
}


void updateGround(){
	gnd_1st_x -= gamespeed;
	gnd_2nd_x -= gamespeed;
	gnd_1st_width -= gamespeed; 
	if(gnd_2nd_x <= 10){
		gnd_1st_x = 10;
		gnd_2nd_x = 230;
		gnd_1st_width = 220;
	}
}

void drawGround(){
	iSetColor(3, 169, 252);
	iFilledRectangle(0, 0, 1920,200);

	
	iSetColor(3, 11, 252);
	iFilledRectangle(0, 10, gnd_1st_width, 180);

	
	int cnt;
	for(cnt = 0; cnt <= 7 ; cnt++){
		iFilledRectangle(gnd_2nd_x + cnt * 230, 10, 220, 180);
	}
}