# include "iGraphics.h"

enum PlayerState {ground, jump, fall, on_block};
enum GameState {main_menu, pause, play, game_over, settings, leaderboards};

int Time = 0;
int playerX = 400;
int playerY = 200;
int playerW = 60;
int playerH = 60;
int onblockNo;
PlayerState playerstate = ground;
GameState gamestate = pause;

int dy = 60;
int dyfall = 10;
int gnd_1st_x = 10; int gnd_1st_width = 220;
int gnd_2nd_x = 230;
int gamespeed = 30;

typedef struct{
	int x;
	int y;
	int ti;
	int w;
	int h;
}RecObstacles;


int recLP = 0;
int recRP = 0;
RecObstacles rec_obs[] = {
    {1850,800,0,0,0},
	{1850,200,8,60,60},
	//{1850,200,30,120,120}, // gamespeed = 30. obs width = 60. so, 2 unit time gap taken
	{1850,200,30,120,60},
	{1850,200,34,120,120},
	{1850,200,70,400,60},
	{1850,200,90,60,200},
	{1850,260,50,400,60}
	
};


typedef struct{
	double x[3];
	double y[3];
	int ti;

}TriObs;

int triLP = 0;
int triRP = 0;
TriObs tri_obs[] = {
	{{1850, 1850, 1850},{800, 800, 800},0},
	{{1850, 1880,1910},{200,254,200},5}
	

};


void updateRecObstacle();
void drawRecObstacle();
void checkRecCollision();

void updateTriObstacle();
void drawTriObs();
void checkTriCollision();

void updateGround();
void drawGround();
void updatePlayerPos();
void updateTimers();
void removeObs();



void iDraw() {

	iClear();
	switch(gamestate){
		case play:  drawGround();
					drawRecObstacle();
					drawTriObs();
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
		if(playerstate == ground || playerstate == on_block){
			playerstate = jump;
		}
		
	}
	//place your codes for other keys here
}


int main() {
	//place your own initialization codes here.
	iSetTimer(50, updatePlayerPos);
	iSetTimer(50, updateGround);
	iSetTimer(50, updateRecObstacle);
	iSetTimer(50, updateTriObstacle);
	iSetTimer(25, checkRecCollision);
	iSetTimer(25, checkTriCollision);
	iSetTimer(25, updateTimers);
	
	iInitialize(1850, 950, "Geometry Dash");
	return 0;
}


void updatePlayerPos(){
	switch(playerstate){

	case jump:
		playerY += dy;
		dy -= 10;
				
		if(playerY < 200){
			dy = 60;
			playerY = 200;
			playerstate = ground;
		}
		break;

	case on_block:
		if(playerX > rec_obs[onblockNo].x + rec_obs[onblockNo].w){
			dy = -10;
			playerstate = jump;

		}

		break;
	}


	// if(state == fall){

	// }
}


void updateRecObstacle(){

	// update left pointer
	if(rec_obs[recLP].x < 0) recLP++;

	// update right pointer
	if(rec_obs[recRP+1].ti <= Time) recRP++;

	// update obstacles within left and right pointers 
	int i;
	for(i = recLP; i <= recRP; i++){
		rec_obs[i].x -= gamespeed;
	}

	Time += 1;

}


void drawRecObstacle(){

	int i;
	iSetColor(252, 3, 65);
	for(i = recLP; i <= recRP; i++){
		iFilledRectangle(rec_obs[i].x, rec_obs[i].y, rec_obs[i].w, rec_obs[i].h);
	}

}

void updateTriObstacle(){
	// update left pointer
	if(tri_obs[triLP].x[0] < 0) triLP++;

	// update right pointer
	if(tri_obs[triRP+1].ti <= Time) triRP++;

	// update obstacles within left and right pointers 
	int i, j;
	for(i = triLP; i <= triRP; i++){
		for(j = 0; j <3; j++){
			tri_obs[i].x[j] -= gamespeed;
		}
	}
}

void drawTriObs(){
	int i;
	iSetColor(252, 3, 65);
	for(i = triLP; i <= triRP; i++){
		iFilledPolygon(tri_obs[i].x, tri_obs[i].y, 3);
	}
}


void checkRecCollision(){
	// there is some glitch. i managed to collide with first 3 obstacles on a run, yet game was on
	// also, if i keep up pressed, the ground obstacles are not detected

	// checks collision as well as landing
	int i;
	for(i = recLP; i < recRP; i++){

		// collision with floating blocks left

		// overlapping widths
		if(playerX < rec_obs[i].x + rec_obs[i].w 
			&& playerX + playerW > rec_obs[i].x){

				// landing
				if(dy < 0 && playerY <= rec_obs[i].y + rec_obs[i].h &&
                    rec_obs[i].y < playerY){
					
					playerstate = on_block;
					onblockNo = i;
					playerY = rec_obs[i].y + rec_obs[i].h;
					dy = 60;
				}

				else if(playerY < rec_obs[i].y + rec_obs[i].h 
						&& playerY + playerH > rec_obs[i].y){
						gamestate = game_over;
				}

		}

	}
}

void checkTriCollision(){
	int i; 
	for(i = triLP; i < triRP; i++){
		if(playerX < tri_obs[i].x[2] &&
			playerX + playerW > tri_obs[i].x[0] &&
			playerY < tri_obs[i].y[1] && 
            tri_obs[i].y[0] <= playerY){

				// printf("condition 1 : %d\n", playerX < tri_obs[i].x[2]);
				// printf("condition 2 : %d\n", playerX + playerW > tri_obs[i].x[0]);
				gamestate = game_over;
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