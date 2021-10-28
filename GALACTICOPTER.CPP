#include<iostream.h>
#include<conio.h>
#include<dos.h>
#include<process.h>
#include<graphics.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<fstream.h>

int gd=DETECT,gm,y=8,base=115,count=0,y1,y2,y3,y4,y5,score=0;
int dif=100,color[5]={15,15,15,15,15},start=0;

union REGS in,out;


struct cord
 {
  int x1;
  int y;
 };

struct highscores
{
  char names[3][100];
  int scores[3];
}data;

int obsth[20][2],x=-48;
int obstd[20][2];

void main();
void reset();

void checkhigh()
{
 int diff=(100-dif)/20;
 if(score>data.scores[diff])
 {closegraph();
  gotoxy(32,5);
  cprintf("NEW HIGHSCORE!!!");
  gotoxy(1,8);
  cprintf("Enter your name for the Hall Of Fame: ");
  gets(data.names[diff]);
  data.scores[diff]=score;
 }
fstream dat("GC.dat",ios::out|ios::binary);
dat.write((char*)&data,sizeof(data));
dat.close();
}

int xcor()
{in.x.ax=3;
 int86(51,&in,&out);
 int a=out.x.cx/8;
return a+1;}
int ycor()
{in.x.ax=3;
 int86(51,&in,&out);
 int a=out.x.dx/8;
return a+1;
}

void opengraph()
{
 initgraph(&gd,&gm,"");
}

void help()
{
 closegraph();
 _setcursortype(_NOCURSOR);
 gotoxy(34,1);
 textcolor(RED);
 cprintf("INSTRUCTIONS");
 textcolor(MAGENTA);
 gotoxy(1,3);
 cprintf("How wonderful would it be if you could surf the space endlessly.We present you  ");
 gotoxy(1,5);
 cprintf("GALACTICOPTER which will offer you the same feel.But your ship is wrecked so be ");
 gotoxy(1,7);
 cprintf("careful.GOOD LUCK.The simplest controls are ready for you to use:");
 gotoxy(1,9);
 cout<<"\t\t\t\t";
 cprintf("Movement -Mouse Left Click ");
 gotoxy(1,11);
 cout<<"\t\t\t\t";
 cprintf("Pause - Space");
 gotoxy(1,13);
 cout<<"\t\t\t\t";
 cprintf("Exit - You have to crash the copter:(:(");
 gotoxy(1,15);
 cprintf("Tweak settings to your favorite in the settings menu.");
 gotoxy(1,19);
 textcolor(YELLOW);
 cout<<"\t\t\t\t";
 cprintf("ENJOY THE GAME!");
 gotoxy(38,22);
 textcolor(BLUE);
 cprintf("ABOUT");
 gotoxy(1,23);
 textcolor(LIGHTBLUE);
 cout<<"\t\t\t";
 cprintf("Devoloped by:GEEK'S PRODUCTIONS");
 getch();

 opengraph();
}


void settings()
{ closegraph();
  _setcursortype(_NOCURSOR);
  gotoxy(31,2);
  textcolor(5);
  cprintf("SETTINGS");
  in.x.ax=1;
  int86(51,&in,&out);
  gotoxy(30,6);
  cprintf("EASY");
  gotoxy(30,8);
  cprintf("MEDIUM");
  gotoxy(30,10);
  cprintf("HARD");
  while(1)
 {
  reset();
  for(int i=0;i<3;++i)
  {if(xcor()>29&&xcor()<36&&ycor()==6+(i*2))
  {color[i]=4;
  int86(51,&in,&out);
  if(out.x.bx==1)
  {dif=100-(i*20);
   return;
  }}}

  gotoxy(30,6);
  textcolor(color[0]);
  cprintf("EASY");
  gotoxy(30,8);
  textcolor(color[1]);
  cprintf("MEDIUM");
  gotoxy(30,10);
  textcolor(color[2]);
  cprintf("HARD");
 }
}

void highscores()
{
 closegraph();
   _setcursortype(_NOCURSOR);
 cout<<"\t\t\t\t";
 cprintf("HALL OF FAME");
 gotoxy(30,6);
 textcolor(CYAN);
 cprintf("Easy    :%s  -  %d",data.names[0],data.scores[0]);
 gotoxy(30,9);
 cprintf("Medium  :%s  -  %d",data.names[1],data.scores[1]);
 gotoxy(30,12);
 cprintf("Hard    :%s  -  %d",data.names[2],data.scores[2]);
 cout<<"\n\n\n\t\t\t";
 cprintf("BEAT THEM IF U CAN!!!");
 getch();
 opengraph();
}

void startup()
{ sleep(2);
  fstream high("GC.dat",ios::in|ios::binary);
  if(!high)
  {
   high.open("GC.dat",ios::out|ios::binary|ios::noreplace);
   for(int i=0;i<3;++i)
   {
    strcpy(data.names[i],"NONAME");
    data.scores[i]=0;
   }
    high.write((char*)&data,sizeof(data));
    high.close();
    high.open("GC.dat",ios::in|ios::binary);
   }
 high.read((char*)&data,sizeof(data));
char geek[5],ere[5];
  int tru=0;
 settextstyle(0,0,6);
 setlinestyle(0,0,3);
 geek[5]='\0';
  setcolor(4);
  rectangle(1,1,639,479);
  setfillstyle(1,4);
  floodfill(620,420,4);
  for(int m=0;m<=60;m++)
 {
  setcolor(14);
  outtextxy(200,100,geek);
  strcpy(ere,geek);
  for(int i=tru;i<=4;i++)
  geek[i]=random(91-65)+65;
  delay(50);
  setcolor(4);
  outtextxy(200,100,ere);
  switch(m)
  {case 20:geek[0]='G';tru++;break;
   case 30:geek[1]='E';tru++;break;
   case 40:geek[2]='E';tru++;break;
   case 50:geek[3]='K';tru++;break;
   case 60:geek[4]='S';tru++;break;
   }
  }
  setcolor(14);
  outtextxy(200,100,geek);
  fflush(stdin);
  setcolor(1);
  settextstyle(1,0,7);
  char prod[11]="PRODUCTIONS";
  for(int ord=0;ord<=5;++ord)
  {char pl[2]={prod[5-ord],'\0'};
   char ll[2]={prod[5+ord],'\0'};
   outtextxy(300-(ord*40),200,pl);
   outtextxy(300+(ord*40),200,ll);
   delay(400);}
   setcolor(9);
   settextstyle(1,0,4);
   outtextxy(235,280,"PRESENTS");
   sleep(4);
  cleardevice();
  int x=-100,x1=540,y=-25,s=7;
 long count=0;
 settextstyle(8,0,5);
 setbkcolor(0);
 while(count<100)
 {
 delay(5);
 cleardevice();
 setcolor(random(15)+7);
 if(x<100){++x;--x1;++y;}
 else ++count;
 outtextxy(x+10,200,"GALACTI");
 settextstyle(s,0,9);
 outtextxy(285,y+5,"C");
 settextstyle(s,0,5);
 outtextxy(x1-5,230,"OPTER");}
  while(x<640)
 {
 cleardevice();
 ++x;--x1;++y;
 outtextxy(x+10,200,"GALACTI");
 settextstyle(s,0,9);
 setcolor(random(15)+7);
 outtextxy(285,y+5,"C");
 settextstyle(s,0,5);
 outtextxy(x1-5,230,"OPTER");}
 }


void pause()
{
 pause:
 setcolor(YELLOW);
 settextstyle(2,0,6);
 outtextxy(100,400,"PAUSED");
 if(getch()!=32)
 goto pause;
 }

void init()
{
 for(int i=0;i<20;++i)
 {
  obsth[i][0]=random(8)+1;
  obsth[i][1]=random(15)+1;
  obstd[i][0]=random(8)+1;
  obstd[i][1]=random(15)+1;
 }
}

void restrict()
{in.x.ax=7;
 in.x.cx=0;
 in.x.dx=640;
 int86(51,&in,&out);
 in.x.ax=8;
 in.x.cx=0;
 in.x.dx=480;
 int86(51,&in,&out);
 }

void update()
{
 for (int i=1;i<20;++i)
 {
  obsth[i-1][0]=obsth[i][0];
  obsth[i-1][1]=obsth[i][1];
  obstd[i-1][0]=obstd[i][0];
  obstd[i-1][1]=obstd[i][1];
 }
 obsth[19][0]=random(8)+1;
 obsth[19][1]=random(15)+1;
 obstd[19][0]=random(8)+1;
 obstd[19][1]=random(15)+1;
}

void draw()
{ for(int i=0;i<20;++i)
 {
  setcolor(obsth[i][1]);
  //setfillstyle(1,obsth[i][1]);
  rectangle(40+(i*40)-(x*10),320,0+(i*40)-(x*10),320-(obsth[i][0]*10));
  //floodfill(40+(i*40)-(x*10)-2,315,obsth[i][1]);
  setcolor(obstd[i][1]);
  //setfillstyle(1,obstd[i][1]);
  rectangle(40+(i*40)-(x*10),120,0+(i*40)-(x*10),120+(obstd[i][0]*10));
 //floodfill(40+(i*40)-(x*10)-2,125,obstd[i][1]);
 }
}

void over()
{
 setcolor(YELLOW);
 settextstyle(1,0,6);
 outtextxy(150,400,"GAME OVER!!!");
 getch();
 checkhigh();
 main();
}

int getcol(cord c)
{
 return getpixel(c.x1,c.y);
}
void check()
{ static int sw=0;
  cord left={150,(base+(10*y))},up={155,(base+(10*y)-5)},right={160,(base+(10*y))},down={155,(base+(10*y)+5)},lu={150,(base+(10*y))-5},ld={150,(base+(10*y))+5},ru={160,(base+(10*y))-5},rd={160,(base+(10*y))+5};
  switch(sw)
  {
   case 1:if(getcol(down)!=0)
	  over();
	  break;
   case 2:if(getcol(left)!=0)
	  over();
	  break;
   case 3:if(getcol(up)!=0)
	  over();
	  break;
   case 4:if(getcol(ld)!=0)
	  over();
	  break;
   case 5:if(getcol(lu)!=0)
	  over();
	  break;
  }
  sw=0;
  if(getcol(up)!=0)
    sw=1;
  if(getcol(right)!=0)
    sw=2;
  if(getcol(down)!=0)
    sw=3;
  if(getcol(ru)!=0&&getcol(up)==0&&getcol(right)==0)
    sw=4;
  if(getcol(rd)!=0&&getcol(down)==0&&getcol(right)==0)
    sw=5;
}

void dispscore()
{
 gotoxy(75,1);
 cout<<"Score";
 gotoxy(77,2);
 cout<<score;
}

void reset()
{
 for(int i=0;i<5;++i)
  color[i]=14;
}

int menu()
{
 restrict();
 settextstyle(1,0,4);
 in.x.ax=1;
 int86(51,&in,&out);
 in.x.ax=3;
 outtextxy(200,100,"Start");
 outtextxy(200,140,"Help");
 outtextxy(200,180,"Settings");
 outtextxy(200,220,"Hall Of Fame");
 outtextxy(200,260,"Exit");
 while(1)
 {
 int86(51,&in,&out);
 reset();
 for(int i=0;i<5;++i)
 {
 if(out.x.dx<100+(40*(i+1))&&out.x.dx>100+(40*i)&&out.x.cx>200&&out.x.cx<400)
{ color[i]=4;
 if(out.x.bx==1)
 return i;}
 }
 setcolor(color[0]);
 outtextxy(200,100,"Start");
 setcolor(color[1]);
 outtextxy(200,140,"Help");
 setcolor(color[2]);
 outtextxy(200,180,"Settings");
 setcolor(color[3]);
 outtextxy(200,220,"Hall Of Fame");
 setcolor(color[4]);
 outtextxy(200,260,"Exit");
 }

}

void game();

void  main()
{

 randomize();
 init();
 x=-48;
 score=0;
 y=8;
 opengraph();
 if(start<1)
 startup();
 start++;
 while(1){
 int cmd=menu();
 switch(cmd)
 {case 0:game();
	 break;
  case 1:help();
	 break;
  case 2:settings();
	 opengraph();
	 break;
  case 3:highscores();
	 break;
  case 4:exit(0);
 }
}
}
void game(){
 setlinestyle(0,0,0);
 in.x.ax=2;
 int86(51,&in,&out);
 in.x.ax=3;
 int86(51,&in,&out);
 cleardevice();
 rectangle(0,120,638,320);
 settextstyle(2,0,4);
 outtextxy(0,20,"right click to start the game");
 wait:
 int86(51,&in,&out);
 if(out.x.bx!=2)
 goto wait;
 while(1)
 {

  int86(51,&in,&out);
  setcolor(WHITE);
  rectangle(149,(base+(10*y))-4,159,(base+(10*y))+4);
  setcolor(BLACK);
 if(kbhit()){
   char com=getch();
   switch(com)
   {
    case 32:pause();
	    break;
   }
  }
   y5=y4;
   y4=y3;
   y3=y2;
   y2=y1;
 y1=y;
  setcolor(7);
  rectangle(139,(base+(10*(y2)))-4,149,(base+(10*(y2)))+4);
  setcolor(7);
  rectangle(129,(base+(10*(y3)))-4,139,(base+(10*(y3)))+4);
  setcolor(8);
  rectangle(119,(base+(10*(y4)))-4,129,(base+(10*(y4)))+4);
  setcolor(8);
  rectangle(109,(base+(10*(y5)))-4,119,(base+(10*(y5)))+4);
  check();

   if(out.x.bx==1)
 {--y;
  delay(dif/2);
 count+=dif/2;
 setcolor(0);
 rectangle(149,(base+(10*(y+1)))-4,159,(base+(10*(y+1)))+4);
 rectangle(139,(base+(10*(y2)))-4,149,(base+(10*(y2)))+4);
 rectangle(129,(base+(10*(y3)))-4,139,(base+(10*(y3)))+4);
 rectangle(119,(base+(10*(y4)))-4,129,(base+(10*(y4)))+4);
 rectangle(109,(base+(10*(y5)))-4,119,(base+(10*(y5)))+4);

 }
 else{ delay(dif);
 ++y;
 count+=dif;
 setcolor(0);
 rectangle(149,(base+(10*(y-1)))-4,159,(base+(10*(y-1)))+4);
 rectangle(139,(base+(10*(y2)))-4,149,(base+(10*(y2)))+4);
 rectangle(129,(base+(10*(y3)))-4,139,(base+(10*(y3)))+4);
 rectangle(119,(base+(10*(y4)))-4,129,(base+(10*(y4)))+4);
 rectangle(109,(base+(10*(y5)))-4,119,(base+(10*(y5)))+4);
 }
 if(y<1||y>20)over();
 if(count>dif)
 {cleardevice();
  count=0;
  draw();
  setcolor(WHITE);
  rectangle(0,120,638,320);
  ++x;
 if(x>3)
 {
 x=0;
 update();
 ++score;
 }
dispscore();
 }
 }
}
//150,(base+(10*y))-4,160,(base+(10*y))+4 these are the co-ordinates of the player

