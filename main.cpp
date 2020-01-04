#include <stdio.h>
#include <math.h>
#include <windows.h>

#include <GL/glut.h>

#include "RGBpixmap.cpp"


#define PI 3.1415926535897932384626433832795
#define MaximumTheta 1.0
#define MinimumTheta 0.0009
#define MaximumRadious 10.5
#define MinimumRadious .9


//DATATYPE DECLERATION
GLfloat IncrementTheta = 0.05;
GLint WindowSizX=640,WindowSizY=480;
GLfloat EyePosition_X=0.0,EyePosition_Y=2,EyePosition_Z= 8.0;
GLfloat Radious=3.3,ProRadious=3.0,InitialTheta1=0.716,InitialTheta2=0.403;
GLfloat Center_X=0.0,Center_Y=0.0,Center_Z=-1.0;
GLfloat Up_X=0.0,Up_Y=1.0,Up_Z=0.0;
enum { ClockWise,AntiClockWise };
enum {Theta1,Theta2};
float Near=.05, Far=10.0,fova = 20.0;
GLint direction = AntiClockWise;
GLint PressMovenent=Theta1;

RGBpixmap pix[6];

//FUNCTION DECLEARATION
void CalculationX_Y_Z();
void CalculationTH1();
void CalculationTH2();
void Movenent();



void tableLeg(double thick, double len)

{

	glPushMatrix();

    glTranslated(0, len/2, 0);
    glScaled(thick, len, thick);
	glutSolidCube(1.0);
	glPopMatrix();
}

void jackPart()
{
	glPushMatrix();
	glScaled(0.2, 0.2, 1.0);
	glutSolidSphere(1, 15, 15);
	glPopMatrix();
    glPushMatrix();
	glTranslated(0, 0, 1.2);
	glutSolidSphere(0.2, 15, 15);
	glTranslated(0, 0, -2.4);
	glutSolidSphere(0.2, 15, 15);
	glPopMatrix();
}

void jack()
{

	glPushMatrix();
	//jackPart();
	glRotated(45, 0, 1, 0);
	jackPart();
	glRotated(90, 1, 0, 0);
	jackPart();
	glRotated(90, 0, 1, 0);
	jackPart();

	glPopMatrix();
}

void table(double topWidth, double topThick, double legThick, double legLen)
{

	glPushMatrix();
	glTranslated(0, legLen, 0);
	glScaled(topWidth, topThick, topWidth);
	glutSolidCube(1.0);
	glPopMatrix();

	double dist = 0.95 * topWidth/2.0 - legThick/2.0;
	glPushMatrix();
	glTranslated(dist, 0, dist);
	tableLeg(legThick, legLen);
	glTranslated(0, 0, -2*dist);
	tableLeg(legThick, legLen);
	glTranslated(-2*dist, 0, 2*dist);
	tableLeg(legThick, legLen);
	glTranslated(0, 0, -2*dist);
	tableLeg(legThick, legLen);
	glPopMatrix();
}



void displaySolid(void)
{

	GLfloat mat_ambient[] = {0.7f, 0.7f, 0.7f, 1.0f};
	GLfloat mat_defused[] = {0.6f, 0.6f, 0.6f, 1.0f};
	GLfloat mat_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat mat_shininess[] = {50.0f};

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_defused);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	//GLfloat lightIntensity[] = {0.7f, 0.7f, 0.7f, 1.0f};
//	GLfloat lightPosition[] = {2.0f, 6.0f, 3.0f, 0.0f};


//	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);




	glViewport(0, 0, WindowSizX,WindowSizY );


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	float aspectR = ((float)WindowSizX / 2) / WindowSizY;


	gluPerspective(fova,aspectR, Near, Far);

	glMatrixMode(GL_MODELVIEW);/////
	glLoadIdentity();//////
    //gluLookAt(EyePosition_X,EyePosition_Y,EyePosition_Z,Center_X,Center_Y,Center_Z,Up_X,Up_Y,Up_Z);
	//start drawing
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
        glViewport(0, 0, WindowSizX / 2, WindowSizY);
        gluLookAt(EyePosition_X,EyePosition_Y,EyePosition_Z,Center_X,Center_Y,Center_Z,Up_X,Up_Y,Up_Z);
        glBindTexture(GL_TEXTURE_2D, 4);
        glEnable(GL_TEXTURE_2D);
        glutSolidCube(1.5);

        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
        glViewport(WindowSizX / 2, 0, WindowSizX / 2, WindowSizY);
        gluLookAt(EyePosition_X,EyePosition_Y,EyePosition_Z,Center_X,Center_Y,Center_Z,Up_X,Up_Y,Up_Z);
        glBindTexture(GL_TEXTURE_2D, 5);
        glEnable(GL_TEXTURE_2D);
        glutSolidCube(1.5);
        glDisable(GL_TEXTURE_2D);
glPopMatrix();


	glFlush();

	glutSwapBuffers();
}



void RepeatDisplay()
{
	glutPostRedisplay();
}


void Movenent()
{

	CalculationX_Y_Z();

	if(PressMovenent == Theta1)
		CalculationTH1();
	else
		CalculationTH2();

}


void CalculationX_Y_Z()
{

		ProRadious = Radious * cos(InitialTheta2);
		EyePosition_Y = Radious * sin(InitialTheta2);

		EyePosition_X = ProRadious * cos(InitialTheta1);
		EyePosition_Z = ProRadious * sin(InitialTheta1);


		printf("EyePosition_X: %f\n",EyePosition_X);
		printf("EyePosition_Y: %f\n",EyePosition_Y);
		printf("EyePosition_Z: %f\n\n",EyePosition_Z);
}



void CalculationTH1()
{


	if (InitialTheta1 > PI*2)
		InitialTheta1 = 0.0;
	if(direction == AntiClockWise)
	{
	   InitialTheta1 += IncrementTheta;
        printf("InitialTheta1: %f\n",InitialTheta1);
	}
	else
	   InitialTheta1 -= IncrementTheta;
       printf("InitialTheta1: %f\n",InitialTheta1);
}



void CalculationTH2(){


	if (InitialTheta2 > PI*2)
		InitialTheta2 = 0.0;

	if(direction == AntiClockWise)
	{
		InitialTheta2 += IncrementTheta;
        printf("InitialTheta2: %f\n",InitialTheta2);
	}

	else
		InitialTheta2 -= IncrementTheta;
       printf("InitialTheta2: %f\n",InitialTheta2);

}



void CalculationRadious(unsigned int key)
{

	if(key == '-')
	{
	if(Radious > MaximumRadious)
		Radious = MaximumRadious;
	else
		Radious += 0.2;
		printf("Radious: %f\n",Radious);
	}
	else if(key == '+')
	{
	if(Radious <= MinimumRadious)
		Radious = MinimumRadious;
	else
		Radious -= 0.2;
		printf("Radious: %f\n",Radious);
	}

	CalculationX_Y_Z();
}


void KeybordFunction( unsigned char key, int x, int y )
{

    if(key=='-')
        CalculationRadious(key);

	else if(key=='+')
        CalculationRadious(key);

	else if(key == '4')
	{
		direction = ClockWise;
		PressMovenent = Theta1;
		Movenent();
	}

	else if(key == '6')
	{

		direction = AntiClockWise;
		PressMovenent = Theta1;
		Movenent();
	}
	else if(key == '8')
	{

		direction = ClockWise;
		PressMovenent = Theta2;
		Movenent();
	}
	else if(key == '2')
	{

		direction = AntiClockWise;
		PressMovenent = Theta2;
		Movenent();
	}

}



void Init()
{


    pix[0].makeCheckImage();
	pix[0].setTexture(1,1);

	pix[1].readBMPFile("H:\\Lectures\\4-2\\Lab\\CSE 4208\\L4\\Lab 4 graphics Class work\\lab4 texturing\\spre.bmp");
	pix[1].setTexture(2,1);

	pix[2].readBMPFile("H:\\Lectures\\4-2\\Lab\\CSE 4208\\L4\\Lab 4 graphics Class work\\lab4 texturing\\cone.bmp");
	pix[2].setTexture(3,1);

	pix[3].readBMPFile("H:\\Lectures\\4-2\\Lab\\CSE 4208\\L4\\Lab 4 graphics Class work\\lab4 texturing\\mosque.bmp");
	pix[3].setTexture(4,2);

    pix[4].readBMPFile("H:\\Lectures\\4-2\\Lab\\CSE 4208\\L3\\wall.bmp");
	pix[4].setTexture(5,1);


}


int main(int argc, char **argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(200, 200);
	glutInitWindowSize(WindowSizX, WindowSizY);
	glutCreateWindow("Texturing");
	glutKeyboardFunc(KeybordFunction);
	glutIdleFunc(RepeatDisplay);
	glutDisplayFunc(displaySolid);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	Init();
	//glClearColor(0.2f, 0.3f, 0.3f, 0.0f);
	glutMainLoop();

	return 0;
}
