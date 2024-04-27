#include<GL/glut.h>
#include<math.h>
#include<iostream>
#include<time.h>
#include<random>
#define PI  3.14159265358979323846

//inicializa
void init();
void display();

using namespace std;
typedef enum 
{
  TRIANGULAR =0,
  ROUND =1,
  TRIROUND=2
}FOLLTYPE;

//forma basicas
void square();//feito
void circle();//feito
void filledCircle();//feito
void triangle();//feito
void rectangularTriangle();//feito

//estrutura dos objetos
void houseGroundLevel();//feito
void houseRoof();//feito
void garage();//feito
void wheel();//feito
void blade();//feito
void mountainSnow();//feito

//Objetos
void ground();//feito
void hill();
void windmill();//feito
void mountain();//feito
void tree(FOLLTYPE leaf);//feito
void house();//feito
void cloud();//feito
void plane();
void car();//feito
void sun();//feito
void bird();
void coin();//feito
void heart();//feito
void diamond();//feito

//gameLogic
void keyboardControls(unsigned char key,GLint x, GLint y);//feito
void drop_coin();//feito
void drop_diamond();
void drop_heart();
void restart();

void game_over();
void animation(GLint v);//feito

GLint frameNumber=0;

GLfloat frameTime = 0.0;

GLfloat posx =0 , posy=-58.0;

GLfloat velx =100.0 , vely =100.0;

GLfloat coin_posx =10, coin_posy =50;

GLfloat diamond_posx=0, diamond_posy=300;

GLfloat heart_posx =0, heart_posy =500;



//acelaracao!
GLfloat axel=1.0;

bool falling=false;

GLint max_score = 0;
GLint current_lives = 3;
GLint current_score = 0;

GLint old_time = 0;
GLint current_time;
GLint delta_time;
GLfloat time_seconds;
//time for the bonus

clock_t health_time;

//mountain positions
GLfloat mountain1_posx = -100;
GLfloat mountain2_posx = 27;

//house positions
GLfloat house1_posx = 70;
GLfloat house2_posx  = - 30;

GLfloat hill_posx = -40;

GLfloat tree1_posx = -40;
GLfloat tree2_posx = 20;
GLfloat tree3_posx = 110;

//Cloud position
GLfloat cloud1_posx = 0;
GLfloat cloud2_posx = -60;
GLfloat cloud3_posx = 60;

//windmill position
GLfloat windmill1_posx = -50;
GLfloat windmill2_posx = 140;

//Angulos
GLfloat sunAngle=0;
GLfloat wheelAngle=0;
GLfloat bladeAngle=0;

//booleanos
bool run_left  = false;
bool run_right = false;
bool jump = false;
bool coin_collected = false;
bool diamond_collected = false;
bool heart_collected = false;

bool want_to_restart = false;
bool paused =false;


void init()
{
  glClearColor(0.565, 0.933, 0.98, 1.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-100,100, -100,100, -100,100);
}


void display()
{
  glClear(GL_COLOR_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  
  
  glPushMatrix();
    ground();
  glPopMatrix();

  glPushMatrix();
    glTranslatef(80,80,0);
    glRotatef(sunAngle,0,0,1);
    glScalef(10,10,1);
    sun();
  glPopMatrix();

  glPushMatrix();
    glTranslatef(mountain1_posx,-60,0);  
    glScalef(20,40*sqrt(3),1);
    mountain();
  glPopMatrix();
  
  glPushMatrix();
    glTranslatef(mountain2_posx,-60,0);
    glScalef(30,50,1);
    mountain();
  glPopMatrix();


  glPushMatrix();
    glTranslatef(house1_posx,-55,1);
    house();
  glPopMatrix();

  glPushMatrix();
    glTranslatef(hill_posx,-60,0);
    glScalef(30,20,1);
    hill();
  glPopMatrix();

  glPushMatrix();
    glTranslatef(house2_posx,-40,0);
    glScalef(0.5,0.5,1);
    house();
  glPopMatrix();

  glPushMatrix();
    glTranslatef(tree1_posx,-40,0);
    tree(TRIROUND);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(tree2_posx,-85,0);
    glScalef(3,3,1);
    tree(ROUND);
  glPopMatrix();

  glPushMatrix();
      glTranslatef(tree3_posx,-50,0);
      glScalef(2,2,1);
     tree(TRIANGULAR);
  glPopMatrix();

   
  glPushMatrix();
    glTranslatef(windmill1_posx,-33,0);
    glScalef(0.5,0.5,1);
    windmill();
  glPopMatrix();
  
  glPushMatrix();
    glTranslatef(windmill2_posx,-40,0);
    windmill();
  glPopMatrix();
  
  glPushMatrix();
    glTranslatef(cloud1_posx,50,0);
    glScalef(10,5,1);
    cloud();
  glPopMatrix();

  glPushMatrix();
    glTranslatef(cloud2_posx,70,1);
    glScalef(12,10,1);
    cloud();
  glPopMatrix();
  
  glPushMatrix();
    glTranslatef(cloud3_posx,20,1);
    glScalef(8,5,1);
    cloud();
  glPopMatrix();
  
  glPushMatrix();
    glTranslatef(coin_posx,coin_posy,0);
    coin();
  glPopMatrix();

  glPushMatrix();
    glTranslatef(diamond_posx,diamond_posy,0);
    glScalef(10,10,1);
    diamond();
  glPopMatrix();

  glPushMatrix();
    glTranslatef(heart_posx,heart_posy,0);
    glScalef(10,10,1);
    heart();
  glPopMatrix();


  glPushMatrix();
    glTranslatef(posx,posy,0);
    glScalef(1.5,1.5,0);
    car();
  glPopMatrix();
  
  

  glutSwapBuffers();

  current_time=glutGet(GLUT_ELAPSED_TIME);

  delta_time = current_time-old_time;
  old_time = current_time;

  time_seconds = delta_time/1000.0;
	//cout<<current_score<<"\n";

  if(run_left==true)
  {
    posx-=velx*time_seconds;
    run_left=false;
    glutPostRedisplay();
  }
  if(run_right==true)
  {
    posx +=velx*time_seconds +pow(time_seconds,2) *(axel) ;
    run_right=false;
    glutPostRedisplay();
  }

  if(jump == true)
  {
    if(falling==false)
    {
    posy += time_seconds* vely + pow(time_seconds,2) *(axel);
    vely+= time_seconds*axel;
      if(posy>=20.0)
      {
        falling =true;
      }
    }
    else
    {
      posy += (-time_seconds)*vely + pow(time_seconds,2) *(axel);
      vely+= 1*time_seconds*axel;
      if(posy<=-58.0)
      {
        posy=-58.0;
        jump = false;
        falling = false;
      }
    }  
  }
  if( (posx-2.5)<=coin_posx && (posx+2.5)>=coin_posx && (posy-2.5)<=coin_posy && (posy+2.5)>=coin_posy )
  {
    if(coin_collected==false)
    {
      current_score +=1;
      coin_collected = true;
      drop_coin();
    }
    cout<<"current score: "<<current_score<<"\n";
  }
  //diamond_hit detection
  if((posx-2.5)<=diamond_posx && (posx+2.5)>=diamond_posx && (posy-2.5)<=diamond_posy && (posy+2.5)>=diamond_posy )
  {
    if(diamond_collected==false)
    {
      current_score +=5;
      diamond_collected = true;
      drop_diamond();
      cout<<"current score: "<<current_score<<"\n";
    }
  }

  if((posx-2.5)<=heart_posx && (posx+2.5)>=heart_posx && (posy-2.5)<=heart_posy && (posy+2.5)>=heart_posy )
  {
    if(heart_collected==false)
    {
      
      heart_collected = true;
      if (current_lives==3)
      {
        current_score+=2;
        cout<<"current score: "<<current_score<<"\n";
      }
      else
      {
        current_lives+=1;
        cout<<"current lives: "<<current_lives<<"\n";
      }
      
      drop_heart();
      
    }
  }


  if(diamond_posy<=-120)
  {
    drop_diamond();
  }

  if(coin_posy<=-120)
  {
    current_lives -=1;
    drop_coin();
  }
  if(heart_posy<=-120)
  {
    drop_heart();
  }
  
  coin_posy-=0.5;
  diamond_posy -=0.5;
  heart_posy -= 0.5;

  wheelAngle-=2.0;
  sunAngle+=2.0;
  if(wheelAngle<=-360.0)
  {
    wheelAngle = 0;
    sunAngle=0;
  }
  
  bladeAngle += 0.5;
  if(bladeAngle >=360)
  {
    bladeAngle=0;
  }


  mountain1_posx -=0.25;
  mountain2_posx -=0.25;

  if(mountain1_posx<=-150)
  {
    mountain1_posx =150;
  }

  if(mountain2_posx<=-150)
  {
    mountain2_posx = 150;
  }
  
  cloud1_posx-=1.0;
  cloud2_posx-=1.0;
  cloud3_posx-=1.0;

  if(cloud1_posx<=-120)
  {
    cloud1_posx=120;
  }

  if(cloud2_posx<=-120)
  {
    cloud2_posx=120;
  }

  if(cloud3_posx<=-120)
  {
    cloud3_posx=120;
  }
  
  house1_posx -= 0.25;
  if(house1_posx<=-107)
  {
    house1_posx=193;
  }
  house2_posx -= 0.25;
  if(house2_posx<=-110)
  {
    house2_posx = 190;
  }
  

  hill_posx -=0.25;
  
  if(hill_posx<=-130)
  {
    hill_posx = 170;
  }

  tree1_posx -= 0.25;
  if(tree1_posx<=-120)
  {
    tree1_posx = 180;
  }
  tree2_posx -= 0.25;
   
  if(tree2_posx<= -140)
  {
    tree2_posx = 160;
  }

  tree3_posx -=0.25;
  if(tree3_posx<=-110)
  {
    tree3_posx = 200;
  }

  windmill1_posx -=0.25;
  if(windmill1_posx<=-110)
  {
    windmill1_posx = 190;
  }
  windmill2_posx -=0.25;
  if(windmill2_posx<=-123)
  {
    windmill2_posx = 190;
  }

  if(current_lives==0)
  {
    game_over();
  }
  
}

void game_over()
{
  if(max_score<current_score)
  {
    max_score =current_score;  
  }
  cout<<"Max score: " <<max_score<<"\n";
  cout<<"Your score: " <<current_score<<"\n";
  max_score = current_score;
  current_score=0;
  paused =true;
  while(paused)
  {
    char choice;
    cout<<"restart?Press y"<<"\n";
    cin>>choice;
    if(choice=='y')
    {
      paused = false ;
    }
  }
  want_to_restart = false;
  restart();
}

void restart()
{
posx =0 , posy=-58.0;
coin_posx =10, coin_posy =50;
diamond_posx=0, diamond_posy=300;
heart_posx =0, heart_posy =500;


falling=false;
current_lives = 3;


mountain1_posx = -100;
mountain2_posx = 27;
house1_posx = 70;
house2_posx  = - 30;
hill_posx = -40;
tree1_posx = -40;
tree2_posx = 20;
tree3_posx = 110;

//Cloud position
cloud1_posx = 0;
cloud2_posx = -60;
cloud3_posx = 60;

//windmill position
windmill1_posx = -50;
windmill2_posx = 140;

//Angulos
sunAngle=0;
wheelAngle=0;
bladeAngle=0;

}

void drop_coin()
{
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> distrib(0, 100);
  coin_posx = distrib(rd);
  coin_posy = 90;
  coin_collected = false;
}


void drop_diamond()
{
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> distrib(0, 100);
  diamond_posx = distrib(rd);
  diamond_posy = 90;
  diamond_collected = false;
}

void drop_heart()
{
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> distrib(0, 100);
  heart_posx = distrib(rd);
  heart_posy = 90;
  heart_collected = false;
}


void keyboardControls(unsigned char key,GLint x, GLint y)
{
    switch(key)
    {
        case 'a':
        {
          run_left = true;
          break;
        }
        case 'd':
        {
          run_right = true;
          break;
        }
        case 'w' :
        {
          jump = true;
          break;
        }
    }
}


void triangle()
{
  glBegin(GL_TRIANGLES);
    glVertex3f(-1,0,0);
    glVertex3f(0,1,0);
    glVertex3f(1,0,0);
  glEnd();
}

void rectangularTriangle()
{
  glBegin(GL_TRIANGLES);
    glVertex3f(0,0,0);
    glVertex3f(0,1,0);
    glVertex3f(1,0,0);
  glEnd();
}

void square()
{
  glBegin(GL_QUADS);
    glVertex3f(-1.0,-1.0,0);
    glVertex3f(-1.0,1.0,0);
    glVertex3f(1.0,1.0,0);
    glVertex3f(1.0,-1.0,0);
  glEnd();
}

void circle()
{
	int i=0;
	glBegin(GL_LINE_LOOP);
	  for(i =0;i<=100;i++)
    {
	    glVertex3f( cos((2*PI/100)* i) ,sin((2*PI/100)*i),0);
    }
	glEnd();
}

void ground()
{
  glBegin(GL_QUADS);
    glColor3f(0.039, 0.388, 0.008);
    glVertex3f(-100,-100,0);
    glVertex3f(-100,-60,0);
    glVertex3f(100,-60,0);
    glVertex3f(100,-100,0);
  glEnd();
}

void filledCircle()
{
    int i=0;
	glBegin(GL_POLYGON);
	  for(i =0;i<=36;i++)
    {
	    glVertex3f( cos((2*PI/36)* i) ,sin((2*PI/36)*i),0);
    }
	glEnd();
}

void houseGroundLevel()
{
    //main frame
    glPushMatrix();
      glColor3f(0.286, 0.722, 1);
      glScalef(6,5,1);
      square();
    glPopMatrix();

    //windows on the left
    glPushMatrix();
      glColor3f(0.322, 0.043, 0.043);
      glTranslatef(-4.0,1,0);
      glScalef(1.2,1.2,1.0);
      square();
    glPopMatrix();

    //windows 2
    glPushMatrix();
      glColor3f(0.322, 0.043, 0.043);
      glTranslatef(-1.0,1.0,0);
       glScalef(1.2,1.2,1.0);
      square();
    glPopMatrix();

    //windows 3
    glPushMatrix();
      glColor3f(0.322, 0.043, 0.043);
      glTranslatef(4.0,1,0);
      glScalef(1.2,1.2,1.0);
      square();
    glPopMatrix();

    //door
    glPushMatrix();
      glColor3f(0.612, 0.557, 0.557);
      glTranslatef(1.6,-1.5,0);
      glScalef(1,3.5,1);
      square();
    glPopMatrix();

}



void houseRoof()
{
    glPushMatrix();
      glColor3f(0.878, 0.059, 0.059);
      glTranslatef(0,5,0);
      glScalef(7,2,1);
      square();
    glPopMatrix();

    glPushMatrix();
      glColor3f(0.878, 0.059, 0.059);
      glTranslatef(-7.0,6.7,0);
      glScalef(14.5,3,1);
      rectangularTriangle();
    glPopMatrix();
}

void garage()
{
    //base
    glPushMatrix();
      glColor3f(0.631, 0.655, 0.871);
      glScalef(1.5,2.5,1);
      square();
    glPopMatrix();

    //garage door
    glPushMatrix();
      glTranslatef(0,-1.0,0);
      glColor3f(0.235, 0.263, 0.569);
      glScalef(1,1.5,1);

      square();
    glPopMatrix();

    //floorRoof
    glPushMatrix();
      glColor3f(0.235, 0.263, 0.569);
      glTranslatef(0,1.8,0);
      glScalef(1.8,0.6,1);
      square();
    glPopMatrix();

    glPushMatrix();
      glColor3f(0.235, 0.263, 0.569);
      glTranslatef(1.8,2.4,0);
      glRotatef(180,0,1,0);
      glScalef(3.6,1,1);
      rectangularTriangle();
    glPopMatrix();
}

void blade()
{

  glPushMatrix();
    glTranslatef(1,0,0);

    glPushMatrix();
      glTranslatef(0,0,0);
      glRotatef(-90,0,0,1);
      glScalef(1,5,1);
      triangle();
    glPopMatrix();


    glPushMatrix();
     glTranslatef(0,0,0);
     glRotatef(90,0,0,1);
     triangle();
    glPopMatrix();

  glPopMatrix();

}

void windmill()
{
  glPushMatrix();
    glColor3f(0.592,0.612,0.631);
    glScalef(1,20,1);
    square();
  glPopMatrix();

  glPushMatrix();
    glColor3f(0.749,0.22,0.22);
    glTranslatef(0,20,0);
    glRotatef(bladeAngle+90,0,0,1);
    glScalef(5,2,1);
    blade();
  glPopMatrix();

  glPushMatrix();
    glColor3f(0.749,0.22,0.22);
    glTranslatef(0,20,0);
    glRotatef(bladeAngle+210,0,0,1);
    glScalef(5,2,1);
    blade();
  glPopMatrix();

  glPushMatrix();
    glColor3f(0.749,0.22,0.22);
    glTranslatef(0,20,0);
    glRotatef(bladeAngle+(-30),0,0,1);
    glScalef(5,2,1);
    blade();
  glPopMatrix();
}



void car()
{
  glPushMatrix();
    glColor3f(0.192, 0.333, 0.89);
    glTranslatef(0,1,0);
    glScalef(2,2,1);
    square();
  glPopMatrix();

  glPushMatrix();
    glTranslatef(-1.5,-0.5,0);
    glRotatef(wheelAngle,0,0,1);
    wheel();
  glPopMatrix();

  glPushMatrix();
    glTranslatef(1.5,-0.5,0);
    glRotatef(wheelAngle,0,0,1);
    wheel();
  glPopMatrix();

}


void wheel()
{
    glPushMatrix();
      glColor3f(0.741,0.741,0.741);
      filledCircle();
    glPopMatrix();

    glPushMatrix();
      glColor3f(0,0,0);
      circle();
    glPopMatrix();

    glPushMatrix();
      glScalef(0.1,0.1,1);
      glColor3f(0,0,0);
      filledCircle();
    glPopMatrix();

    glPushMatrix();
      GLint i;
      for(i=0;i<=12;i++)
        {

            glColor3f(0,0,0);
            glBegin(GL_LINES);
              glVertex3f(0,0,0);
              glVertex3f(cos((2*PI/12)* i) ,sin((2*PI/12)*i),0);
            glEnd();
        }
    glPopMatrix();

}

void house()
{
  glPushMatrix();
    houseGroundLevel();
  glPopMatrix();
  glPushMatrix();
    houseRoof();
  glPopMatrix();
  
  glPushMatrix();
    glTranslatef(-9.0,-1.5,0);
    glScalef(2.0,1.5,1);
    garage();
  glPopMatrix();
}


void tree(FOLLTYPE leaf)
{

    glPushMatrix();
      glColor3f(0.478, 0.22, 0.212);
      glScalef(1,6,1);
      square();
    glPopMatrix();   

    if(leaf==TRIANGULAR)
    {
      glPushMatrix();
        glColor3f(0, 1, 0.012);
        glTranslatef(0,1,1);
        glScalef(3,8,1);
        triangle();
      glPopMatrix();
    }
    else if(leaf==ROUND)
    {
      glPushMatrix();
        glScalef(3,4,1);
        glPushMatrix();
          glColor3f(0, 1, 0.012);
          filledCircle();
        glPopMatrix();

        glPushMatrix();
          glColor3f(0, 1, 0.012);
          glTranslatef(0,1,0);
          filledCircle();
        glPopMatrix();
      glPopMatrix();
    }
    else
    {
      glPushMatrix();
        glTranslatef(0,3,0);
        glScalef(2.5,2.5,1); 
        glPushMatrix();
          glColor3f(0, 1, 0.012);
          glTranslatef(0,0.5,0);
          filledCircle();
        glPopMatrix();

        glPushMatrix();
          glColor3f(0, 1, 0.012);
          glTranslatef(0.5,0,0);
          filledCircle();
        glPopMatrix();

        glPushMatrix();
          glColor3f(0, 1, 0.012);
          glTranslatef(-0.5,0,0);
          filledCircle();
        glPopMatrix();
      glPopMatrix();
    }
}

void cloud()
{
  glPushMatrix();
    glColor3f(0.89, 0.89, 0.89);
    glTranslatef(-0.5,0,0);
    filledCircle();
  glPopMatrix();

  glPushMatrix();
    glColor3f(0.89, 0.89, 0.89);
    glTranslatef(0.5,0,0);
    filledCircle();
  glPopMatrix();

  glPushMatrix();
    glColor3f(0.89, 0.89, 0.89);
    glTranslatef(0,-0.5,0);
    filledCircle();
  glPopMatrix();

  glPushMatrix();
    glColor3f(0.89, 0.89, 0.89);
    glTranslatef(0,0.5,0);
    filledCircle();
  glPopMatrix();
}


void sun()
{
  int i;
  glPushMatrix();
    glColor3f(0.961,0.533,0);
    glBegin(GL_LINES);
      for(i=0;i<=12;i++)
      {
          glVertex3f(0,0,0);
          glVertex3f(1.5*cos((2*PI/12)* i), 1.5*sin((2*PI/12)*i),0);
      }
    glEnd();

    glPushMatrix();
      glColor3f(1,1,0);
      filledCircle();
    glPopMatrix();

    glPushMatrix();
      glColor3f(0.961,0.533,0);
      circle();
    glPopMatrix();

  glPopMatrix();
}


void mountain()
{
  glPushMatrix();
    glColor3f(0.42, 0.42, 0.42);
    triangle();
  glPopMatrix();

  glPushMatrix();
    glTranslatef(0, (5.8 *sqrt(3.0))/12.0 ,0);
    mountainSnow();
  glPopMatrix();
}

void mountainSnow()
{
  glPushMatrix();
    glColor3f(1,1,1);
    glScalef(1.0/6.0, 1.0/6.0, 1);
    triangle();
  glPopMatrix();

  glPushMatrix();
    glColor3f(1,1,1);
    glTranslatef(1.0/12.0,0,0);
    glRotatef(180,0,0,1);
    glScalef(1.0/12.0, 1.0/12.0, 1);
    triangle();
  glPopMatrix();
  
  glPushMatrix();
    glColor3f(1,1,1);
    glTranslatef(-(1.0/12.0),0,0);
    glRotatef(180,0,0,1);
    glScalef(1.0/12.0, 1.0/12.0, 1);
    triangle();
  glPopMatrix();

}

void coin()
{
  glPushMatrix();
    glColor3f(1, 0.749, 0);
    filledCircle();
  glPopMatrix();
}

void diamond()
{
  
  glPushMatrix();
    glRotatef(180,0,0,1);
    glPushMatrix();
      glColor3f(0.812, 1, 0.996);
      glScalef(1.0/6.0, 1.0/6.0, 1);
      triangle();
    glPopMatrix();

    glPushMatrix();
      glColor3f(0.812, 1, 0.996);
      glTranslatef(1.0/12.0,0,0);
      glRotatef(180,0,0,1);
      glScalef(1.0/12.0, 1.0/12.0, 1);
      triangle();
    glPopMatrix();

    glPushMatrix();
      glColor3f(0.812, 1, 0.996);
      glTranslatef(0,-1.0/12.0,0);
      
      glScalef(1.0/12.0, 1.0/12.0, 1);
      triangle();
    glPopMatrix();
    
    glPushMatrix();
      glColor3f(0.812, 1, 0.996);
      glTranslatef(-(1.0/12.0),0,0);
      glRotatef(180,0,0,1);
      glScalef(1.0/12.0, 1.0/12.0, 1);
      triangle();
    glPopMatrix();
  glPopMatrix();
}

void heart()
{
  glPushMatrix();
    
    glRotatef(180,0,0,1);
    
    glPushMatrix();
      glColor3f(1,0,0);
      glScalef(1.0/6.0, 1.0/6.0, 1);
      triangle();
    glPopMatrix();

    glPushMatrix();
      glColor3f(1,0,0);
      glTranslatef(1.0/12.0,0,0);
      glRotatef(180,0,0,1);
      glScalef(1.0/12.0, 1.0/12.0, 1);
      triangle();
    glPopMatrix();
  
    glPushMatrix();
      glColor3f(1,0,0);
      glTranslatef(-(1.0/12.0),0,0);
      glRotatef(180,0,0,1);
      glScalef(1.0/12.0, 1.0/12.0, 1);
      triangle();
    glPopMatrix();
    
  glPopMatrix();
}

void hill()
{
  glPushMatrix();
    glColor3f(0.039, 0.388, 0.008);
    filledCircle();
  glPopMatrix();
}

void animation(GLint v)
{
  frameNumber++;

  glutTimerFunc(20,animation,0);

  glutPostRedisplay();

}


int main(int argc, char** argv)
{
     glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_DOUBLE);
    glutInitWindowSize (960,720);
    glutInitWindowPosition (200, 200);

    glutCreateWindow("jogo");
    init();

    glutDisplayFunc(display);

    glutTimerFunc(20,animation,0);

    glutKeyboardFunc(keyboardControls);

    glutMainLoop();

    return 0;
}
