/*
	author: S. M. Shahriar Nirjon
	last modified: August 8, 2008
*/
#include "iGraphics.h"

int pic_x, pic_y;
int idle_idx = 0;
char monster_idle[4][100];

void populate_monster_images(){
    for(int i=0;i<4;i++){
        sprintf(monster_idle[i], "spritedemo\\pinkmonster\\idleanim\\tile%03d.bmp", i);
        printf("%s\n", monster_idle[i]);
    }
}


void update_monster(){
    idle_idx = (idle_idx + 1) % 4;
    // 0 1 2 3 0 1 2 3
}
/*
	function iDraw() is called again and again by the system.
*/
void iDraw()
{
	//place your drawing codes here

	iClear();
    iShowBMP(pic_x, pic_y, monster_idle[idle_idx]);
	// iShowBMP(pic_x, pic_y, "wheel.bmp");

}

/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{
	//place your codes here
}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		//place your codes here
	}
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		//place your codes here
	}
}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key)
{
	if(key == 'x')
	{
		//do something with 'x'
		exit(0);
	}
	//place your codes for other keys here
}

/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/
void iSpecialKeyboard(unsigned char key)
{

	if(key == GLUT_KEY_END)
	{
		exit(0);
	}
	if(key == GLUT_KEY_LEFT)
	{
		pic_x--;
	}
	if(key == GLUT_KEY_RIGHT)
	{
		pic_x++;
	}
	if(key == GLUT_KEY_UP)
	{
		pic_y++;
	}
	if(key == GLUT_KEY_DOWN)
	{
		pic_y--;
	}
	//place your codes for other keys here
}

int main()
{
	//place your own initialization codes here.
	pic_x = 30;
	pic_y = 20;
    populate_monster_images();
    iSetTimer(100, update_monster);
	iInitialize(500, 400, "SpriteDemo");
	return 0;
}