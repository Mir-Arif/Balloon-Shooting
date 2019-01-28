int level=0;
int life;
int NumberOfBalloon;
int Initialize_Level_One=0;
int Initialize_Level_Two=0;
int arrow_flag=0;
int b_flag=0;
int wide=1350, height=700;
int showspecial;
int dead;
int point=0;
int deads_flag;
char points[4];
char lifes[2];
int LEVEL_TWO_deads_cordent=0;
int level_two_collison_return;
int LEVEL_TWO_b_flag=0;

FILE *from;
int scores[5];
char show[6][6];

void High_scores();
void GameOver();

struct dead_balloon_type
{
    int x;
    int y;
    int point;
    char color;
} dead_baloon[15];

struct special_balloon_type
{
    int x;
    int y;
    int point;
    char color;
} sp__baloon[10];

struct arrow_type
{
    int x;
    int y;
} arrow;

struct balloon_type
{
    int x;
    int y;
    int point;
    char color;
} b[20];

void showBallon(char ball,int x,int y)
{
    switch(ball)
    {
    case 'r':
        iShowBMP2(x,y,"Aquas.bmp",0);
        break;
    case 'g':
        iShowBMP2(x,y,"Blue.bmp",0);
        break;
    case 'b':
        iShowBMP2(x,y,"Green.BMP",0);
        break;
    case 'n':
        iShowBMP2(x,y,"White.BMP",0);
        break;
    case 'y':
        iShowBMP2(x,y,"Yellow.BMP",0);
        break;
    case 'd':
        iShowBMP(x,y,"Dead.BMP");
        break;
    }
}

void colorPoints(int i)
{
	if(level==1)
	{
		if(b[i].color=='g')
			b[i].point=3;
		else if(b[i].color=='b')
			b[i].point=9;
		else if(b[i].color=='r')
			b[i].point=10;
		else if(b[i].color=='y')
			b[i].point=5;
		else if(b[i].color=='n')
			b[i].point=5;
	}
    else if(level==2)
	{
		if(b[i].color=='n')
			b[i].point=2;
		else if(b[i].color=='g')
			b[i].point=10;
		else if(b[i].color=='b')
			b[i].point=8;
		else if(b[i].color=='r')
			b[i].point=5;
		 else if(b[i].color=='y')
			b[i].point=5;
	}
}


//This function check that, is balloon collited or not.
int Collision_Checker(int x,int y)
{
	if(((arrow.x+20)>=x) && ((arrow.x+20)<=(x+96)) && ((arrow.y+40)>=y) && ((arrow.y+40)<=y+96))
	{
		arrow_flag=0;
		return 1;
	}
    else
        return 0;
}


//Delete the collited balloon
void Delete_Balloon(int position)
{
    for(int i=position; i<NumberOfBalloon; i++)
        b[i]=b[i+1];
}

void delete_DeadBallon(int position)
{
    for(int i=position; i<dead; i++)
        dead_baloon[i]=dead_baloon[i+1];
}


void dead_baloon_hasColited()
{
    for(int k=0; k<dead; k++)
    {
        int dead_collite = Collision_Checker(dead_baloon[k].x,dead_baloon[k].y);
        if(dead_collite == 1)
        {
            delete_DeadBallon(k);
            dead--;
			life--;
            break;
        }
    }
}

void Bio_Collite()
{
	for(int i=0; i<NumberOfBalloon; i++)
    {
        int collite = Collision_Checker(b[i].x,b[i].y);
        if(collite==1)
        {
			point = point + b[i].point;
            Delete_Balloon(i);
            NumberOfBalloon--;
            break;
        }
    }
}

int store_special_baloon = 0;
void  special_baloon_hascolited()
{
	store_special_baloon = Collision_Checker(sp__baloon[0].x,sp__baloon[0].y);

	if(store_special_baloon==1)
	{
        showspecial=1;
        point = point + 40;
        dead=0;
        NumberOfBalloon=0;

        sp__baloon[0].x= 2500;
        sp__baloon[0].y= 2500;
	}
}


void Home_page(){
	iShowBMP(0,0,"Home.bmp");
}

void Help_Page(){
	iShowBMP(0,0,"Help.bmp");
}

void Game_Over(){
	iSetColor(255, 255, 255);
	iShowBMP(0,0,"gameover.bmp");
	iText(550,350,"# YOUR FINAL SCORE :",GLUT_BITMAP_TIMES_ROMAN_24);
	sprintf(points,"%d",point);
	iText(810,350,points,GLUT_BITMAP_TIMES_ROMAN_24);
}

void win(){
	iShowBMP(0, 0, "win.bmp");
	iText(700,320,"# YOUR FINAL SCORE :",GLUT_BITMAP_TIMES_ROMAN_24);
	sprintf(points,"%d",point);
	iText(970,320,points,GLUT_BITMAP_TIMES_ROMAN_24);
}

void Level1()
{
	iShowBMP(0,0,"Level1.bmp");
	iSetColor(255,255,255);

	iShowBMP(1120, 55, "coin.bmp");
	sprintf(points, "%d", point);
	iText(1150, 60,"Point: ", GLUT_BITMAP_TIMES_ROMAN_24);
	iText(1220, 60, points, GLUT_BITMAP_TIMES_ROMAN_24);

	iShowBMP(1120,25,"life.bmp");
	sprintf( lifes, "%d", life);
	iText(1150, 30, "Life: ", GLUT_BITMAP_TIMES_ROMAN_24);
	iText(1220, 30, lifes, GLUT_BITMAP_TIMES_ROMAN_24);

	//initial position of balloons
	Initialize_Level_One++;
    if(Initialize_Level_One == 1)
    {
        dead=5;
        NumberOfBalloon=15;
		life=3;
		point=0;

		arrow_flag=0;
        deads_flag=0;
        showspecial=0;

        arrow.x=430;
        arrow.y=33;

        b[0].color = 'b';
        b[1].color = 'g';
        b[2].color = 'n';
        b[3].color = 'r';
        b[4].color = 'y';
        b[5].color = 'b';
        b[6].color = 'g';
        b[7].color = 'b';
        b[8].color = 'r';
        b[9].color = 'y';
        b[10].color = 'n';
        b[11].color = 'g';
        b[12].color = 'b';
        b[13].color = 'r';
        b[14].color = 'y';

		for(int i=0 ; i<NumberOfBalloon; i++){
			b[i].x = -135 + i;
			b[i].y = 600;
			colorPoints(i);
		}
		for(int i=0; i<dead; i++){
			dead_baloon[i].x = (i+1)*270;
			dead_baloon[i].y = 350;
			dead_baloon[i].color = 'd';
		}
	}

	//BALLOON REPEATION
    for(int i=0; i<NumberOfBalloon; i++)
    {
        if(b[i].x >= wide)
            b_flag=1;

        if(b_flag==1)
            b[i].x=-200;

        b_flag=0;
    }

	//ARROW REPEATION
	if(arrow_flag == 0){
		arrow.y = 0;
		iShowBMP(arrow.x,arrow.y,"arrow.bmp");
	}
    else if(arrow_flag==1)
	{
        arrow.y=arrow.y+50;
		iShowBMP(arrow.x,arrow.y,"arrow.bmp");

		if(arrow.y>=700)
			arrow_flag=0;
    }

    Bio_Collite();
    dead_baloon_hasColited();

	for(int i=0; i<NumberOfBalloon; i++){
		if(i==3 || i==8 || i==13)
			iShowBMP2(b[i].x, b[i].y,"Aquas.bmp",0);
		else if(i==1 || i==6 || i==11)
			iShowBMP2(b[i].x, b[i].y,"Blue.BMP",0);
		else if(i==0 || i==5 || i==7 || i==12)
			iShowBMP2(b[i].x, b[i].y,"Green.BMP",0);
		else if(i==2 || i==10)
			iShowBMP2(b[i].x, b[i].y,"White.BMP",0);
		else if(i==1 || i==6 || i==11)
			iShowBMP2(b[i].x, b[i].y,"Yellow.BMP",0);
	}
	
    for(int i=0; i<dead; i++){
        showBallon(dead_baloon[i].color,dead_baloon[i].x,dead_baloon[i].y);
		dead_baloon[i].x = dead_baloon[i].x+5;

        if(dead_baloon[i].x >= 1350)
            deads_flag = 1;

        if(deads_flag == 1)
            dead_baloon[i].x = 0;

        deads_flag = 0;
	}

    b[0].x=b[0].x+12;
    b[1].x=b[1].x+11;
    b[2].x=b[2].x+24;
    b[3].x=b[3].x+26;
    b[4].x=b[4].x+18;
    b[5].x=b[5].x+10;
    b[6].x=b[6].x+12;
    b[7].x=b[7].x+14;
    b[8].x=b[8].x+16;
    b[9].x=b[9].x+18;
    b[10].x=b[10].x+32;
    b[11].x=b[11].x+32;
    b[12].x=b[12].x+34;
    b[13].x=b[13].x+36;
    b[14].x=b[14].x+38;

    if(point == 100){
		Initialize_Level_Two=0;
		level = 2;
        iDelayMS(200);
	}
    
	if(life == 0){
		GameOver();
		level = 4;
	}
    iDelayMS(20);
}



void Level2()
{   
	iShowBMP(0,0,"level2.bmp");
	iSetColor(0,0,0);

	iShowBMP(1120, 55, "coin.bmp");
	sprintf(points, "%d", point);
	iText(1150, 60,"Point: ", GLUT_BITMAP_TIMES_ROMAN_24);
	iText(1220, 60, points, GLUT_BITMAP_TIMES_ROMAN_24);

	iShowBMP(1120,25,"life.bmp");
	sprintf( lifes, "%d", life);
	iText(1150, 30, "Life: ", GLUT_BITMAP_TIMES_ROMAN_24);
	iText(1220, 30, lifes, GLUT_BITMAP_TIMES_ROMAN_24);

    Initialize_Level_Two++;
    if(Initialize_Level_Two == 1)
    {        NumberOfBalloon=15;
        dead=8;
		life++;

        deads_flag=0;
		arrow_flag=0;
        showspecial=0;

        arrow.x=15;
        arrow.y=300;

		b[0].x=1150;
        b[1].x=450;
        b[2].x=550;
        b[3].x=370;
        b[4].x=650;
        b[5].x=750;
        b[6].x=950;
        b[7].x=1050;
        b[8].x=1150;
        b[9].x=1250;
        b[10].x=110;
        b[11].x=135;
        b[12].x=870;
        b[13].x=999;
        b[14].x=50;
		for(int i=0; i<15; i++)
			b[i].y = 900;

        b[0].color='n';
        b[1].color='g';
        b[2].color='b';
        b[3].color='r';
        b[4].color='y';
		b[5].color='n';
        b[6].color='g';
        b[7].color='b';
        b[8].color='r';
        b[9].color='y';
		b[10].color='n';
        b[11].color='g';
        b[12].color='b';
        b[13].color='r';
        b[14].color='y';

        sp__baloon[0].x=0;
        sp__baloon[0].y=0;

        dead_baloon[0].x=220;
        dead_baloon[1].x=300;        dead_baloon[2].x=400;
        dead_baloon[3].x=500;
        dead_baloon[4].x=920;
        dead_baloon[5].x=860;        dead_baloon[6].x=690;
        dead_baloon[7].x=1110;
		for(int i=0; i<dead; i++){
			dead_baloon[i].y = 1350;
			dead_baloon[i].color = 'd';
		}
	}

    if(point>=150)
    {
        if(showspecial==0)
        {
			iShowBMP2(sp__baloon[0].x-48, sp__baloon[0].y-28, "Dead.BMP", 0);
            iCircle(sp__baloon[0].x,sp__baloon[0].y,150,150);
			
            sp__baloon[0].x=sp__baloon[0].x+2;
            sp__baloon[0].y=sp__baloon[0].y+2;
        }
    }

	//REPEAT OF BALLOON
    for(int i=0; i<NumberOfBalloon; i++)
    {
        if(b[i].y<=0)
            LEVEL_TWO_b_flag=1;
		
		if(LEVEL_TWO_b_flag==1)
			b[i].y=900;

        LEVEL_TWO_b_flag=0;
    }

	
    if(arrow_flag==1)
    {
        iShowBMP(arrow.x,arrow.y,"LEVEL_TWO_arrow.bmp");
		arrow.x = arrow.x + 100;
    }

    if(arrow.x >= 1350)
        arrow_flag = 0;
	
	if(arrow_flag == 0)
        arrow.x = 0;

	if(arrow_flag == 0)
         iShowBMP(arrow.x,arrow.y,"LEVEL_TWO_arrow.bmp");

    Bio_Collite();
    dead_baloon_hasColited();
        
	for(int i=0; i<NumberOfBalloon; i++)
        showBallon(b[i].color,b[i].x,b[i].y);


    for(int zz=0; zz<dead; zz++)
        showBallon(dead_baloon[zz].color,dead_baloon[zz].x,dead_baloon[zz].y);

    dead_baloon[0].y = dead_baloon[0].y-12;
    dead_baloon[1].y = dead_baloon[1].y-14;
    dead_baloon[2].y = dead_baloon[2].y-6;
    dead_baloon[3].y = dead_baloon[3].y-8;
    dead_baloon[4].y = dead_baloon[4].y-22;
    dead_baloon[5].y = dead_baloon[5].y-4;
    dead_baloon[6].y = dead_baloon[6].y-16;
    dead_baloon[7].y = dead_baloon[7].y-18;

    for(int i=0; i<dead; i++)
    {
        if(dead_baloon[i].y<=0)
            LEVEL_TWO_deads_cordent=1;
		
		if(LEVEL_TWO_deads_cordent==1)
            dead_baloon[i].y=1350;

        LEVEL_TWO_deads_cordent=0;
    }

	Bio_Collite ();
    dead_baloon_hasColited();

    level_two_collison_return = Collision_Checker(sp__baloon[0].x,sp__baloon[0].y);

    for(int i=0; i<NumberOfBalloon; i++)
		Collision_Checker(b[i].x,b[i].y);

    if(level_two_collison_return==1)
    {
        //special_point=1;
        dead=0;
    }

    b[0].y=b[0].y-20;
    b[1].y=b[1].y-5;
    b[2].y=b[2].y-4;
    b[3].y=b[3].y-3;
    b[4].y=b[4].y-2;
    b[5].y=b[5].y-13;
    b[6].y=b[6].y-5;
    b[7].y=b[7].y-4;
    b[8].y=b[8].y-23;
    b[9].y=b[9].y-2;
	b[10].y=b[10].y-2;
    b[11].y=b[11].y-15;
    b[12].y=b[12].y-9;
    b[13].y=b[13].y-13;
    b[14].y=b[14].y-16;

	special_baloon_hascolited();

	for(int i=0; i<=NumberOfBalloon; i++)
		colorPoints(i);

	if(point>=189){
		GameOver();
		level=5;
	}

	if(life == 0)
	{
		NumberOfBalloon=0;
		GameOver();
		level=4;
    }
    iDelayMS(20);
}


void High_scores()
{
	if((from = fopen( "HIGHSCORE.txt" , "r" )) == NULL)
	{
		from = fopen( "HIGHSCORE.txt" , "w" );
		for (int i=0; i<5; i++)
		{
			scores[i]=0;
			fprintf( from,"%d\n", scores[i] );
		}
		fclose(from);
	}

	from = fopen( "HIGHSCORE.txt" , "r" );
	int i=0;
	while (!feof(from))
	{
		fgets(show[i],5,from);
		i++;
	}
	fclose(from);

	iShowBMP(0,0,"hs.bmp");
	
	iSetColor(0,0,0);

	iText(600,500,"1.",GLUT_BITMAP_TIMES_ROMAN_24);
	iText(600,440,"2.",GLUT_BITMAP_TIMES_ROMAN_24);
	iText(600,380,"3.",GLUT_BITMAP_TIMES_ROMAN_24);
	iText(600,320,"4.",GLUT_BITMAP_TIMES_ROMAN_24);
	iText(600,260,"5.",GLUT_BITMAP_TIMES_ROMAN_24);

	for (int i=0; i<5; i++)	
		iText(630,500-i*60,show[i],GLUT_BITMAP_TIMES_ROMAN_24);
}

void GameOver(){

	if ((from = fopen( "HIGHSCORE.txt" , "r")) == NULL)
	{
		from = fopen( "HIGHSCORE.txt" , "w" );
		for (int i=0; i<5; i++)
		{
			scores[i]=0;
			fprintf( from, "%d\n", scores[i] );
		}
		fclose(from);
	}

	from = fopen( "HIGHSCORE.txt" , "r" );
	int i=0;
	while (!feof(from))
	{
		fscanf(from,"%d",&scores[i]);
		i++;
	}
	fclose(from);
	
	for (i=0; i<5; i++){
		if (point>scores[i])
		{
			for (int j=4; j>i; j--)
				scores[j]=scores[j-1];

			scores[i]=point;
			break;
		}
	}

	from = fopen( "HIGHSCORE.txt" , "w" );
	for (int i=0; i<5; i++)
		fprintf( from, "%d\n", scores[i] );
	fclose(from);
}