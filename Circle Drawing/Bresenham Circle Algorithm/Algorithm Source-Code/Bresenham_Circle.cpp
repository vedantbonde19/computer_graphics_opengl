#include <iostream>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

using namespace std;

int pntX1, pntY1, pntX2, pntY2, r;

int roundoff(double d)
{
  return floor(d + 0.5);
}

void plot(int x, int y)
{
	glBegin(GL_POINTS);
	glVertex2i(x + pntX1, y + pntY1);
	glEnd();
}


void myInit (void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor3f (1.0, 1.0, 1.0);
	glPointSize(4.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}

void Bres_Circle (int xBeg, int yBeg, int r)
{
	int xp = 0;
	int yp = r;
	int dec_par = 3 - 2*r;
	plot(xp, yp);

	while(yp > xp){
		if(dec_par < 0){
			xp = xp + 1;
			dec_par = dec_par + 4*(xp) + 6;
		}
		else{
			yp = yp - 1;
			xp = xp + 1;
			dec_par = dec_par + 4*(xp - yp) + 10;
		}


		plot(xp, yp);
		plot(xp, -yp);
		plot(-xp, yp);
		plot(-xp, -yp);
		plot(yp, xp);
		plot(yp, -xp);
		plot(-yp, xp);
		plot(-yp, -xp);
		
	}

}

void drawLine()
{
	glBegin(GL_LINES);
	glVertex2i(pntX1, pntY1+30);
	glVertex2i(pntX2, pntY2+30);
	glEnd();
}

void myDisplay(void)
{
	glClear (GL_COLOR_BUFFER_BIT);
	glColor3f (1.0, 1.0, 1.0);
	glPointSize(1.0);
	Bres_Circle(pntX1, pntY1, r);
	//drawLine();
	glFlush ();
}

int main(int argc, char** argv)
{

	cout << "Enter the coordinates of the center: ";

	cin >> pntX1;
	cin >> pntY1;
	cout << "\nEnter radius : "; 
	cin >> r;

	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize (640, 480);
	glutInitWindowPosition (100, 150);
	glutCreateWindow ("Bresenham-Circle Drawing Alogrithm");
	glutDisplayFunc(myDisplay);
	myInit ();
	glutMainLoop();

}
