#include "iGraphics.h"
#include "bitmap_loader.h"
#include "game.h"


extern int NumberOfBalloon;
extern int dead;


//function iDraw() is called again and again by the system.
void iDraw()
{
	//place your drawing codes here
    iClear();

	if (level==0) Home_page();
	else if(level==1) Level1();
    else if(level==2) Level2();
	else if(level==3) Help_Page();
	else if(level==4) Game_Over();
	else if(level==5) win();
	else if(level==6) High_scores();
}

void CycleCircleUpdate()
{

}

/*
function iMouseMove() is called when the user presses and drags the mouse.
(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{

}

/*
function iMouse() is called when the user presses/releases the mouse.
(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{
    printf("x:%d  y:%d\n", mx, my);
	if(level==0)
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && 1075<mx && mx<1200 && 445>my && my>373){
			Initialize_Level_One=0;
			level = 1;}
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && 1040<mx && mx<1190 && 190>my && my>120)
			level = 3;
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && 835<mx && mx<1200 && 335>my && my>265)
			level = 6;
	}
	if(level==3)//Help Page
	{
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && 95<mx && mx<233 && 105>my && my>60)
			level=0;
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && 1150<mx && mx<1280 && 105>my && my>60){
			Initialize_Level_One=0;
			level=1;}
	}
	if(level==4)//Game over page
	{	
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && 850<mx && mx<1275 && 215>my && my>165){
			level=0;}
	}
	if(level==5)//Winning page
	{
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && 1035<mx && mx<1295 && 145>my && my>105){
			level=0;}
	}
	if(level==6)//High Score
	{	
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && 975<mx && mx<1260 && 235>my && my>190){
			level=0;}
	}
}


/*
function iKeyboard() is called whenever the user hits a key in keyboard.
key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key)
{
	if (key == ' '){
        arrow_flag=1;
    }
	if(key == 'a')
		level=2;
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
	if(level==1)
	{
		if(key ==  GLUT_KEY_LEFT)
			arrow.x = arrow.x-20;
		if (key ==  GLUT_KEY_RIGHT)
			arrow.x = arrow.x+20;
	} 
	if(level==2)
	{
		if( key == GLUT_KEY_UP)
			arrow.y += 15;

		if( key == GLUT_KEY_DOWN)
			arrow.y -= 15;
	}
}


int main()
{
    int id=iSetTimer(100,CycleCircleUpdate);
	//iPauseTimer(id);
	//place your own initialization codes here.
	PlaySound("music", NULL, SND_LOOP | SND_ASYNC);
	iInitialize(wide, height, "Balloon Shooting");
    return 0;
}