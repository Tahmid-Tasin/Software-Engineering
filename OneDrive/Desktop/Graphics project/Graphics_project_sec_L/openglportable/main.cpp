#include<windows.h>
#include<GL/glut.h>
#include<stdlib.h>
#include<math.h>
double  r=.2,s=.3;
int i;
float  tx=10,bx=10;
float wheelAngle = 0.0f;   // nagordola rotation



void init()
{
    glClearColor(1.0f,1.0f,1.0f,1.0f);
    glOrtho(-210,210,-220,310,-210,310);

}
//-----------------------sky------------------------------------------------------------------

//-----------------------cloud-----------------------------------------------------------------
void cloud(double x, double y)
{


    glBegin(GL_TRIANGLE_FAN);
        for(i=0;i<360;i++)
        {
            x=x+cos((i*3.14)/180)*r;
            y=y+sin((i*3.14)/180)*r;

            glVertex2d(x,y);

        }


    glEnd();



}
void sun(double x, double y)
{


    glBegin(GL_TRIANGLE_FAN);
        for(i=0;i<360;i++)
        {
            x=x+cos((i*3.14)/180)*s;
            y=y+sin((i*3.14)/180)*s;

            glVertex2d(x,y);

        }


    glEnd();



}
// ------------------------------------Fence-------------------------------------------------
void fence(int x)
{
    glBegin(GL_POLYGON);
        glColor3ub(184,134,11);

        glVertex2i(190-x,130);
        glVertex2i(190-x,70);
        glVertex2i(187-x,70);
        glVertex2i(187-x,130);
        glVertex2i(190-x,130);



    glEnd();

}

// ------------------ Nagordola ------------------
void ferrisWheel(float cx, float cy)
{
    glPushMatrix();

    // Wheel stand
    glColor3ub(160,160,160);
    glBegin(GL_POLYGON);
        glVertex2f(cx-6, cy-5);
        glVertex2f(cx+6, cy-5);
        glVertex2f(cx+30, cy-90);
        glVertex2f(cx+20, cy-90);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(cx-6, cy-5);
        glVertex2f(cx+6, cy-5);
        glVertex2f(cx-20, cy-90);
        glVertex2f(cx-30, cy-90);
    glEnd();

    // Move to wheel center
    glTranslatef(cx, cy, 0);

    glScalef(1.3f, 1.3f, 1.0f);   // increase wheel size


    // Clockwise rotation
    glRotatef(-wheelAngle, 0, 0, 1);

    // Outer rim (light blue)
    glColor3ub(173,216,230);
    glBegin(GL_LINE_LOOP);
    for(int i=0;i<360;i++)
        glVertex2f(cos(i*3.14/180)*45, sin(i*3.14/180)*45);
    glEnd();

    // Inner red ring
    glColor3ub(220,20,60);
    glBegin(GL_LINE_LOOP);
    for(int i=0;i<360;i++)
        glVertex2f(cos(i*3.14/180)*30, sin(i*3.14/180)*30);
    glEnd();

    // Center hub
    glColor3ub(255,215,0);
    glBegin(GL_POLYGON);
    for(int i=0;i<360;i++)
        glVertex2f(cos(i*3.14/180)*8, sin(i*3.14/180)*8);
    glEnd();

    // Spokes (blue)
    glColor3ub(30,144,255);
    for(int i=0;i<360;i+=45)
    {
        glBegin(GL_LINES);
            glVertex2f(0,0);
            glVertex2f(cos(i*3.14/180)*45, sin(i*3.14/180)*45);
        glEnd();
    }

    // Cabins (fixed orientation)
int colors[8][3] = {
    {255,99,71}, {255,182,193}, {72,209,204}, {255,215,0},
    {255,99,71}, {255,182,193}, {72,209,204}, {255,215,0}
};

int idx = 0;
for(int i=0;i<360;i+=45)
{
    glPushMatrix();

    // Move to cabin position
    float angle = i * 3.14 / 180;
    float x = cos(angle) * 45;
    float y = sin(angle) * 45;

    glTranslatef(x, y, 0);

    // Counter-rotate cabin to keep upright
    glRotatef(wheelAngle, 0, 0, 1);

    // Cabin body
    glColor3ub(colors[idx][0], colors[idx][1], colors[idx][2]);
    glBegin(GL_POLYGON);
        glVertex2f(-7, 0);
        glVertex2f( 7, 0);
        glVertex2f( 5,-10);
        glVertex2f(-5,-10);
    glEnd();

    // Cabin roof
    glColor3ub(220,20,60);
    glBegin(GL_TRIANGLES);
        glVertex2f(-7, 0);
        glVertex2f( 7, 0);
        glVertex2f( 0, 8);
    glEnd();

    glPopMatrix();
    idx++;
}



    glPopMatrix();
}






void display()
{

    glClear(GL_COLOR_BUFFER_BIT);
//-----------------------sky------------------------------------------------------------------
    glColor3ub(135,206,250);//light blue
        glRecti(-200,300,200,100);
//-----------------------------------field------------------------------
    glBegin(GL_POLYGON);
        glColor3ub(0,100,0);//green

        glVertex2i(-200,100);
        glVertex2i(-100,160);
        glVertex2i(0,100);
        glVertex2i(50,70);
        glVertex2i(100,180);
        glVertex2i(200,100);
        glColor3ub(255,215,0);//gold
        glVertex2i(200,-200);

        glVertex2i(-200,-200);
        glColor3ub(255,215,0);//gold
        glVertex2i(-200,100);

    glEnd();

//-------------------SUN-------------------------
    glColor3ub(255,215,0);
    sun(90,250);
// ------------------------------------fence--------------------------
    int x=0;
    for(int i=0;i<39;i++)
    {
        fence(x);
        x+=10;
    }

    glColor3ub(184,134,11);
    glRecti(-200,120,200,115);
    glRecti(-200,100,200,95);
    glRecti(-200,85,200,80);


//-------------------------------------TREE------------------------
    glColor3ub(139,69,19);//
    glRecti(-20,200,-13,140);
    glColor3ub(0,100,0);
    sun(-30,190);
    sun(0,190);
    sun(-10,210);
    sun(-30,175);
    sun(-0,170);
    glBegin(GL_POLYGON); // Main Tree // first part
        glColor3ub(139,69,19);//
        glVertex2i(-170,160);
        glVertex2i(-168,120);
        glColor3ub(139,69,19);//
        glVertex2i(-178,40);
        glVertex2i(-145,40);
        glColor3ub(139,69,19);//
        glVertex2i(-153,120);
        glVertex2i(-150,160);
        glVertex2i(-170,160);
    glEnd();
    glBegin(GL_POLYGON);  // Main Tree // second part
        glColor3ub(139,69,19);//
        glVertex2i(-153,100);
        glVertex2i(-100,200);
        glVertex2i(-95,200);
        glVertex2i(-153,80);
        glVertex2i(-153,100);
    glEnd();
    glBegin(GL_POLYGON);  // Main Tree // third part
        glColor3ub(139,69,19);//
        glVertex2i(-170,160);
        glVertex2i(-185,210);
        glVertex2i(-190,210);
        glVertex2i(-168,90);
        glVertex2i(-170,160);

    glEnd();
    glBegin(GL_POLYGON);  // Main Tree // fourth part
        glColor3ub(139,69,19);//
        glVertex2i(-160,160);
        glVertex2i(-150,210);
        glVertex2i(-140,210);
        glVertex2i(-150,160);
        glVertex2i(-160,160);


    glEnd();
    glColor3ub(0,128,0);//leaf
        sun(-95,200);
        sun(-80,180);
        sun(-110,180);
        sun(-120,200);

        sun(-150,200);
        sun(-130,180);
        sun(-125,220);
        sun(-140,230);

        sun(-190,210);
        sun(-180,200);
        sun(-175,225);
        sun(-195,190);



// --------------------------------------- HOUSE one----------------------------
glPushMatrix();
glTranslatef(-40, 0, 0);
    glBegin(GL_POLYGON);  // first Part
        glColor3ub(128,0,0);//gray
        glVertex2i(-58,115);
        glVertex2i(-75,145);
        glVertex2i(-115,150);//point
        glVertex2i(-90,100);
        glVertex2i(-62,100);
        glVertex2i(-58,115);

    glEnd();
    glBegin(GL_POLYGON);  // second Part
        glColor3ub(120,0,0);//maroon
        glVertex2i(-115,150);
        glVertex2i(-130,100);
        glVertex2i(-120,100);//point
        glVertex2i(-108,137);//point
        glVertex2i(-115,150);
    glEnd();
    glBegin(GL_POLYGON);  // third Part
        glColor3ub(46,139,87);//
        glVertex2i(-108,137);
        glVertex2i(-120,100);
        glVertex2i(-120,45);
        glVertex2i(-90,40);//point
        glVertex2i(-90,100);
        glVertex2i(-108,137);
    glEnd();


    glBegin(GL_POLYGON);  // fourth Part
        glColor3ub(143,188,143);//
        glVertex2i(-90,40);
        glVertex2i(-60,45);
        glVertex2i(-60,100);
        glVertex2i(-90,100);

    glEnd();
    glColor3ub(120,0,0);//maroon // Door One
        glRecti(-75,80,-65,40);
    glColor3ub(120,0,0);//maroon // Door One
        glRecti(-110,90,-100,70);
    glBegin(GL_POLYGON);  // third Part (lower part 1)
        glColor3ub(0,0,0);//
        glVertex2i(-90,40);
        glVertex2i(-123,45);
        glVertex2i(-123,35);
        glVertex2i(-90,30);
        glVertex2i(-90,40);

    glEnd();
    glBegin(GL_POLYGON);  // third Part (lower part 2)
        glColor3ub(0,0,0);//
        glVertex2i(-90,40);
        glVertex2i(-55,45);
        glVertex2i(-55,35);
        glVertex2i(-90,30);
        glVertex2i(-90,40);


    glEnd();

glPopMatrix();


//-------------------------------------------  HOUSE  two  -------------------------------------------------
glPushMatrix();
glTranslatef(-60, 0, 0);
    glBegin(GL_POLYGON);  // First part

        glColor3ub(25,25,112);//midnight blue
        glVertex2i(-50,140);
        glVertex2i(0,149);
        glVertex2i(-12,88);
        glVertex2i(-65,89);
        glVertex2i(-50,140);
    glEnd();





    glBegin(GL_POLYGON);  // Second Part
    glColor3ub(70,130,180);//midnight blue
        glVertex2i(-60,90);
        glVertex2i(-60,30);
        glVertex2i(-10,25);
        glVertex2i(-10,95);
    glEnd();


//---------------------------------------Door------------------------------------------
    glColor3ub(25,25,112);//midnight blue
    glRecti(-45,70,-30,27);

//--------------------------------------------------------------------------
    glBegin(GL_POLYGON);   // Third part
    glColor3ub(95,158,160);//midnight blue
        glVertex2i(-10,25);
        glVertex2i(18,35);
        glVertex2i(18,100);
        glVertex2i(0,148);
        glVertex2i(-10,100);
        glVertex2i(-10,25);

    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(25,25,112);//midnight blue
        glVertex2i(-1,150);
        glVertex2i(20,100);
        glVertex2i(17,90);
        glVertex2i(-4,140);
        glVertex2i(-1,150);

    glEnd();


    glBegin(GL_POLYGON);  // door
    glColor3ub(25,25,112);//midnight blue
        glVertex2i(0,70);
        glVertex2i(10,73);
        glVertex2i(10,32);
        glVertex2i(0,29);
        glVertex2i(0,70);


    glEnd();
    glBegin(GL_POLYGON);  // (lower part 1)
        glColor3ub(0,0,0);//
        glVertex2i(-10,25);
        glVertex2i(-10,15);
        glVertex2i(20,27);
        glVertex2i(20,37);
        glVertex2i(-10,25);


    glEnd();
    glBegin(GL_POLYGON);  // (lower part 2)
        glColor3ub(0,0,0);//
        glVertex2i(-10,25);
        glVertex2i(-62,30);
        glVertex2i(-62,20);
        glVertex2i(-10,15);
        glVertex2i(-10,25);




    glEnd();
glPopMatrix();

 // -------- Roof (cloth) --------
    glBegin(GL_POLYGON);
        glColor3ub(178,34,34); // dark red
        glVertex2i(-40,140);
        glVertex2i(40,140);
        glVertex2i(30,170);
        glVertex2i(-30,170);
    glEnd();

    // -------- Roof stripes --------
    glColor3ub(255,255,255);
    for(int i=-30;i<=30;i+=15)
        glRecti(i,140,i+7,170);

    // -------- Stall body --------
    glBegin(GL_POLYGON);
        glColor3ub(245,222,179); // wheat color
        glVertex2i(-35,140);
        glVertex2i(35,140);
        glVertex2i(30,80);
        glVertex2i(-30,80);
    glEnd();

    // -------- Counter --------
    glColor3ub(160,82,45); // wood
    glRecti(-35,90,35,80);

    // -------- Support poles --------
    glColor3ub(101,67,33);
    glRecti(-30,140,-25,60);
    glRecti(25,140,30,60);

    // -------- Items on stall (pots / fruits) --------
    glColor3ub(255,69,0);   // fruit
    glRecti(-20,100,-10,90);
    glRecti(-5,100,5,90);
    glRecti(10,100,20,90);

    glColor3ub(139,69,19);  // pot
    glRecti(-18,90,-12,80);
    glRecti(12,90,18,80);

    // ---------------- Ferris Wheel beside stall ----------------
    ferrisWheel(90, 115);




    wheelAngle += 0.03f;   // speed
if(wheelAngle > 360)
    wheelAngle = 0;


    glutPostRedisplay();

    glFlush();
}


int main(int argc,char *argv[])
{
    glutInit(&argc,argv);
    glutInitWindowSize(1920,1080);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutCreateWindow(" Village-Fair ");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
