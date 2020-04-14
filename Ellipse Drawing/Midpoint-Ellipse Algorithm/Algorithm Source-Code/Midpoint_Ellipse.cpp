#include <stdio.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <GL/glut.h>
using namespace std;


using namespace std;

int pntX1, pntY1, pntX2, pntY2;

int roundoff(double d)
{
  return floor(d + 0.5);
}

void plot(int x, int y)
{
	glBegin(GL_POINTS);
	glVertex2i(x + pntX2, y + pntY2);
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


void midpoint_ellipse(int r_maj, int r_min, int x_cen, int y_cen) 
{ 
    float dx, dy, d1, d2, x, y; 
    x = 0; 
    y = r_min; 
  
    d1 = (r_min * r_min) - (r_maj * r_maj * r_min) +  
                     (0.25 * r_maj * r_maj); 
    dx = 2 * r_min * r_min * x; 
    dy = 2 * r_maj * r_maj * y; 
  
    while (dx < dy)  
    { 
  
        plot(x, y);
        plot(-x, y);
        plot(x, -y);
        plot(-x, -y);
  
        if (d1 < 0) 
        { 
            x++; 
            dx = dx + (2 * r_min * r_min); 
            d1 = d1 + dx + (r_min * r_min); 
        } 
        else 
        { 
            x++; 
            y--; 
            dx = dx + (2 * r_min * r_min); 
            dy = dy - (2 * r_maj * r_maj); 
            d1 = d1 + dx - dy + (r_min * r_min); 
        } 
    } 
  
    d2 = ((r_min * r_min) * ((x + 0.5) * (x + 0.5))) +  
         ((r_maj * r_maj) * ((y - 1) * (y - 1))) - 
          (r_maj * r_maj * r_min * r_min); 
  
    while (y >= 0) 
    { 

    	plot(x, y);
    	plot(-x, y);
    	plot(x, -y);
    	plot(-x, -y);
    
        if (d2 > 0)  
        { 
            y--; 
            dy = dy - (2 * r_maj * r_maj); 
            d2 = d2 + (r_maj * r_maj) - dy; 
        } 
        else 
        { 
            y--; 
            x++; 
            dx = dx + (2 * r_min * r_min); 
            dy = dy - (2 * r_maj * r_maj); 
            d2 = d2 + dx - dy + (r_maj * r_maj); 
        } 
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
	midpoint_ellipse(pntX1, pntY1, pntX2, pntY2);
	//drawLine();
	glFlush ();
}

int main(int argc, char** argv)
{

	cout << "Enter the radius of the major and minor axes: ";
	cin >> pntX1 >> pntY1;
	cout << "\nEnter the centre of the ellipse: "; 
	cin >> pntX2 >> pntY2;

	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize (640, 480);
	glutInitWindowPosition (100, 150);
	glutCreateWindow ("Midpoint Ellipse Drawing Alogrithm");
	glutDisplayFunc(myDisplay);
	myInit ();
	glutMainLoop();

}
