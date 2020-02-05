#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <cstring>
#include <vector>
#include <GL/glut.h>

using namespace std;

#define round(a) (int(a+0.5))
float max(float a,float b)
{
return ((a>b) ? a : b);
}
float min(float a,float b)
{
return ((a>b) ? b : a);
}

void initialize(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutCreateWindow(argv[0]);
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glPointSize(1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 640, 0, 480);
}

void close_graph() {
    glutMainLoop();
}


float x,y,xmin,xmax,ymin,ymax,xi,xf,yi,yf,t,t1,t2=1;

void cyrus_beck(float xi, float yi, float xf, float yf){
	t=(xmin-xi)/(xf-xi);
	if(xf>xi)
		t1=max(t1,t);
	else
	t2=min(t2,t);
	t=(ymax-yi)/(yf-yi);
	if(yi>yf)
	t1=max(t1,t);
	else
	t2=min(t2,t);
	t=(xmax-xi)/(xf-xi);
	if(xi>xf)
	t1=max(t1,t);
	else
	t2=min(t2,t);
	t=(ymin-yi)/(yf-yi);
	if(yf>yi)
	t1=max(t1,t);
	else
	t2=min(t2,t);
	if(t1<t2)
	{
	x=xf;
	y=yf;
	xf=xi+t2*(xf-xi);
	yf=yi+t2*(yf-yi);
	xi+=t1*(x-xi);
	yi+=t1*(y-yi);

	glColor3f(1, 0, 0);
        glLineWidth(2);
        glBegin(GL_LINES);
        glVertex2i(round(xi), round(yi));
        glVertex2i(round(xf), round(yf));
        glEnd();
        glFlush();

}
}

int roundoff(GLfloat a) {
    return (GLint) (a + 0.5f);
}


void draw_window(float xmin, float ymin, float xmax, float ymax) {

    glColor3f(0, 0, 0);
    glBegin(GL_LINE_LOOP);
    glVertex2i(roundoff(xmin), roundoff(ymin));
    glVertex2i(roundoff(xmin), roundoff(ymax));
    glVertex2i(roundoff(xmax), roundoff(ymax));
    glVertex2i(roundoff(xmax), roundoff(ymin));
    glEnd();
    glFlush();
}

void draw_line(float xi, float yi, float xf, float yf) {

    glColor3f(0, 0, 1);
    glBegin(GL_LINE_LOOP);
    glVertex2i(roundoff(xi), roundoff(yi));
    glVertex2i(roundoff(xf), roundoff(yf));

    glEnd();
    glFlush();
} 


void init_clip() {
    glClear(GL_COLOR_BUFFER_BIT);

    //Pnt init_win = {60, 60};
    //Pnt fin_win = {470, 290};
    draw_window(xmin, ymin, xmax, ymax);
    //Pnt p1 = {50, 50};
    //Pnt p2 = {490, 310};
    glColor3f(0, 0, 1);

    draw_line(xi, yi, xf, yf);

    glBegin(GL_LINES);
    glVertex2i(roundoff(xi), roundoff(yi));
    glVertex2i(roundoff(xf), roundoff(yf));
    glEnd();
    cyrus_beck(xi, yi, xf, yf);


}

int main(int argc, char **argv) {

    initialize(argc, argv);

	cout<<"Enter the initial coordinates of rectangular clip window: ";

	cin>>xmin>>ymin;

	cout<<"\nEnter the final coordinates of rectangular clip window: ";

	cin>>xmax>>ymax;

	cout<<"\nEnter the initial coordinates of line to be clipped: ";
	cin>>xi>>yi;

	cout<<"\nEnter the final coordinates of line to be clipped: ";
	cin>>xf>>yf;

    glutDisplayFunc(init_clip);
    close_graph();

    return 0;
}