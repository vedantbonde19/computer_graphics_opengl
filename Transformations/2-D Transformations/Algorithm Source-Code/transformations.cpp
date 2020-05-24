#include <stdio.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <GL/glut.h>

using namespace std;



double roundoff(double d)
{
	return floor(d + 0.5);
}

int X1, Y1, sel = 0, edges;
vector<int> pntX;
vector<int> pntY;
int tnsX, tnsY;
double scaleX, scaleY;
double ang, angRad;
char reflectionAxis, shearingAxis;
int shearingX, shearingY;

void plot(int x, int y)
{
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

void plotPoly()
{
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);
	for (int i = 0; i < edges; i++)
	{
		glVertex2i(pntX[i], pntY[i]);
	}
	glEnd();
}


void PolyTrans(int x, int y)
{
	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 1.0);
	for (int i = 0; i < edges; i++)
	{
		glVertex2i(pntX[i] + x, pntY[i] + y);
	}
	glEnd();
}

void PolyScale(double x, double y)
{
	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 1.0);
	for (int i = 0; i < edges; i++)
	{
		glVertex2i(roundoff(pntX[i] * x), roundoff(pntY[i] * y));
	}
	glEnd();
}

void PolyRot(double angRad)
{
	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 1.0);
	for (int i = 0; i < edges; i++)
	{
		glVertex2i(roundoff((pntX[i] * cos(angRad)) - (pntY[i] * sin(angRad))), roundoff((pntX[i] * sin(angRad)) + (pntY[i] * cos(angRad))));
	}
	glEnd();
}

void PolyRef(char reflectionAxis)
{
	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 1.0);

	if (reflectionAxis == 'x' || reflectionAxis == 'X')
	{
		for (int i = 0; i < edges; i++)
		{
			glVertex2i(roundoff(pntX[i]), roundoff(pntY[i] * -1));

		}
	}
	else if (reflectionAxis == 'y' || reflectionAxis == 'Y')
	{
		for (int i = 0; i < edges; i++)
		{
			glVertex2i(roundoff(pntX[i] * -1), roundoff(pntY[i]));
		}
	}
	glEnd();
}

void PolyShear()
{
	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 1.0);

	if (shearingAxis == 'y' || shearingAxis == 'Y')
	{
		glVertex2i(pntX[0], pntY[0]+ shearingX*pntY[0]);

		glVertex2i(pntX[1], pntY[1]+ shearingX*pntY[1]);
		glVertex2i(pntX[2], pntY[2]+ shearingX*pntY[2]);

		glVertex2i(pntX[3], pntY[3]+ shearingX*pntY[3]);
	}
	else if (shearingAxis == 'x' || shearingAxis == 'X')
	{
		glVertex2i(pntX[0], pntY[0]);
		glVertex2i(pntX[1], pntY[1]);
		
		glVertex2i(pntX[2], pntY[2] + shearingY);
		glVertex2i(pntX[3], pntY[3] + shearingY);
	}
	glEnd();
}

void myInit(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0f, 0.0f, 0.0f);
	glPointSize(4.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-640.0, 640.0, -480.0, 480.0);
}


void myDisplay(void)
{

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);
	glPointSize(1.0);
	for(int i=-640;i<=640;i++){
		plot(i,0);
		plot(0,i);
	}
	glPointSize(4.0);
	if (sel == 1)
	{
		plotPoly();
		PolyTrans(tnsX, tnsY);
	}
	else if (sel == 2)
	{
		plotPoly();
		PolyScale(scaleX, scaleY);
	}
	else if (sel == 3)
	{
		plotPoly();
		PolyRot(angRad);
	}
	else if (sel == 4)
	{
		plotPoly();
		PolyRef(reflectionAxis);
	}
	else if (sel == 5)
	{
		plotPoly();
		PolyShear();
	}

	glFlush();
}

int main(int argc, char** argv)
{
	cout << "Enter your selection:\n\n" << endl;

	cout << "1. Translation" << endl;
	cout << "2. Scaling" << endl;
	cout << "3. Rotation" << endl;
	cout << "4. Mirror Reflection" << endl;
	cout << "5. Shearing" << endl;
	cout << "6. Exit" << endl;

	cin >> sel;

	if (sel == 6) {
		return 0;
	}

	cout << "\n\nFor Convex Polygon:\n" << endl;

	cout << "Enter no of edges (IN CLOCKWISE/COUNTER-CLOCKWISE ORDER ONLY): "; cin >> edges;

	for (int i = 0; i < edges; i++)
	{
		cout << "Enter co-ordinates for vertex  " << i + 1 << " : "; cin >> X1 >> Y1;
		pntX.push_back(X1);
		pntY.push_back(Y1);
	}

	if (sel == 1)
	{
		cout << "Enter the translation factor for X and Y: "; cin >> tnsX >> tnsY;
	}
	else if (sel == 2)
	{
		cout << "Enter the scaling factor for X and Y: "; cin >> scaleX >> scaleY;
	}
	else if (sel == 3)
	{
		cout << "Enter the ang for rotation (in degrees): "; cin >> ang;
		angRad = ang * 3.1416 / 180;
	}
	else if (sel == 4)
	{
		cout << "Enter reflection axis ( x or y ): "; cin >> reflectionAxis;
	}
	else if (sel == 5)
	{
		cout << "Enter reflection axis ( x or y ): "; cin >> shearingAxis;
		if (shearingAxis == 'x' || shearingAxis == 'X')
		{
			cout << "Enter the shearing factor for X: "; cin >> shearingX;
		}
		else
		{
			cout << "Enter the shearing factor for Y: "; cin >> shearingX;
		}
	}
	//cout << "\n\nPoints:" << pntX[0] << ", " << pntY[0] << endl;
	//cout << angRad;


	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(100, 150);
	glutCreateWindow("Extended Basic Transformations");
	glutDisplayFunc(myDisplay);
	myInit();
	glutMainLoop();

}
