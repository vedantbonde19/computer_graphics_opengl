#include <stdio.h>
#include <math.h>
#include <iostream>
#include <GL/glut.h>
using namespace std;

int pntX1, pntY1, pntX2, pntY2;

int roundoff(double d)
{
  return floor(d + 0.5);
}

void plot(int x, int y)
{
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}


void myInit (void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	//glColor3f(0.0f, 0.0f, 0.0f);
	glColor3f (1.0, 1.0, 1.0);
	glPointSize(4.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}

void Bres_Line (int xBeg, int yBeg, int xEnd, int yEnd)
{
	int dx = fabs (xEnd - xBeg), dy = fabs(yEnd - yBeg);
	int p = 2 * dy - dx;
	int twoDy = 2 * dy, twoDyMinusDx = 2 * (dy - dx);
	int x, y;
	if (xBeg > xEnd) {
		x = xEnd;
		y = yEnd;
		xEnd = xBeg;
	}
	else {
		x = xBeg;
		y = yBeg;
	}
	plot(x, y);
	while (x < xEnd) {
		x++;
		if (p < 0)
		p += twoDy;
		else {
		y++;
		p += twoDyMinusDx;
		}
		plot(x, y);
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
	//glColor3f (0.0, 0.0, 0.0);
	glColor3f (1.0, 1.0, 1.0);
	glPointSize(1.0);
	//ddaAlgo();
	Bres_Line (pntX1,pntY1,pntX2,pntY2);
	//drawLine();
	glFlush ();
}

int main(int argc, char** argv)
{

	cout << "Enter the Initial Point: "; cin >> pntX1; cin >> pntY1;
	cout << "\nEnter the Final Point: "; cin >> pntX2; cin >> pntY2;

	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize (640, 480);
	glutInitWindowPosition (100, 150);
	glutCreateWindow ("Bresenham Line Drawing Alogrithm");
	glutDisplayFunc(myDisplay);
	myInit ();
	glutMainLoop();

}
