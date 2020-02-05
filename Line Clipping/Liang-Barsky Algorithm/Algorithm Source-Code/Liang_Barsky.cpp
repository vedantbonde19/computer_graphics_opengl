#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <cstring>
#include <vector>
#include <GL/glut.h>

using namespace std;

void plot(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

GLint roundoff(GLfloat a) {
    return (GLint) (a + 0.5f);
}


void lineBres(int xBeg, int yBeg, int xEnd, int yEnd)
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


   class wcPt2D 
   {
      public:
      GLfloat x, y;

      GLfloat getx() const {
         return x;
      }

      GLfloat gety() const {
         return y;
      }
   };

inline GLint roundoff1(const GLfloat a) 
{ 
    return GLint (a + 0.5); 
}

GLint clipTest (GLfloat p, GLfloat q, GLfloat * u1, GLfloat * u2)
{
  GLfloat r;
  GLint returnValue = true;

  if (p < 0.0) {
    r = q / p;
    if (r > *u2)
      returnValue = false;
    else
      if (r > *u1)
        *u1 = r;
  }
  else
    if (p > 0.0) {
      r = q / p;
      if (r < *u1)
        returnValue = false;
      else if (r < *u2)
        *u2 = r;
    }
    else
      /*  Thus p = 0 and line is parallel to clipping boundary.  */
      if (q < 0.0)
        /*  Line is outside clipping boundary.  */
        returnValue = false;

  return (returnValue);
}

void lineClipLiangBarsk (wcPt2D winMin, wcPt2D winMax, wcPt2D p1, wcPt2D p2)
{
  GLfloat u1 = 0.0, u2 = 1.0, dx = p2.getx ( ) - p1.getx ( ), dy;

  if (clipTest(-dx, p1.getx() - winMin.getx(), &u1, &u2))
    if (clipTest (dx, winMax.getx() - p1.getx(), &u1, &u2)) {
      dy = p2.gety() - p1.gety();
      if (clipTest(-dy, p1.gety() - winMin.gety(), &u1, &u2))
        if (clipTest(dy, winMax.gety() - p1.gety(), &u1, &u2)) {
          if (u2 < 1.0) {
            p2.x = (p1.getx() + u2 * dx);
            p2.y = (p1.gety() + u2 * dy);
          }
          if (u1 > 0.0) {
            p1.x = (p1.getx() + u1 * dx);
            p1.y = (p1.gety() + u1 * dy);
          }

        glColor3f(1, 0, 0);
        // glLineWidth(2);
        glBegin(GL_LINES);
        glVertex2i(roundoff1(p1.getx()), roundoff1(p1.gety()));
        glVertex2i(roundoff1(p2.getx()), roundoff1(p2.gety()));
        glEnd();
        glFlush();

          lineBres(roundoff1(p1.getx()), roundoff1 (p1.gety()), 
                       roundoff1(p2.getx( )), roundoff1 (p2.gety()));
        }
    }
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

void draw_window(wcPt2D init_win, wcPt2D fin_win) {

    glColor3f(0, 0, 0);
    glBegin(GL_LINE_LOOP);
    glVertex2i(roundoff(init_win.x), roundoff(init_win.y));
    glVertex2i(roundoff(init_win.x), roundoff(fin_win.y));
    glVertex2i(roundoff(fin_win.x), roundoff(fin_win.y));
    glVertex2i(roundoff(fin_win.x), roundoff(init_win.y));
    glEnd();
    glFlush();
}

void draw_line(wcPt2D Pnt1, wcPt2D Pnt2) {

    glColor3f(0, 0, 1);
    glBegin(GL_LINE_LOOP);
    glVertex2i(roundoff(Pnt1.x), roundoff(Pnt1.y));
    glVertex2i(roundoff(Pnt2.x), roundoff(Pnt2.y));

    glEnd();
    glFlush();
} 

void init_clip() {
    glClear(GL_COLOR_BUFFER_BIT);
    wcPt2D Win1, Win2, Pnt1, Pnt2;
    Win1.x = 150;
    Win1.y = 100;
    Win2.x = 350;
    Win2.y = 300;

    Pnt1.x = 60;
    Pnt1.y = 60;
    Pnt2.x = 400;
    Pnt2.y = 30;
    //Pnt init_win = {60, 60};
    //Pnt fin_win = {470, 290};
    draw_window(Win1, Win2);
    //Pnt p1 = {50, 50};
    //Pnt p2 = {490, 30};
    glColor3f(0, 0, 1);

    glBegin(GL_LINES);glFlush();

    glVertex2i(roundoff1(Pnt1.x), roundoff1(Pnt1.y));
    glVertex2i(roundoff1(Pnt2.x), roundoff1(Pnt2.y));

    glEnd();
    glFlush();

    draw_line(Pnt1, Pnt2);

    lineClipLiangBarsk(Win1, Win2, Pnt1, Pnt2);
}

int main(int argc, char **argv) {

    initialize(argc, argv);

    /*  int Win1X, Win1Y, Win2X, Win2Y;
    int Pnt1X, Pnt1Y, Pnt2X, Pnt2Y;

    cout << "Enter the coordinates of the bottom-left point of the Window: ";
    cin >> Win1X >> Win1Y;
    cout << "\nEnter the coordinates of the top-right point of the Window: ";
    cin >> Win2X >> Win2Y;

    cout << "\nEnter the coordinates of initial point of the Line: ";
    cin >> Pnt1X >> Pnt1Y;
    cout << "\nEnter the coordinates of the final point of the Line: ";
    cin >> Pnt2X >> Pnt2Y;

    initWin.x = Win1X;
    initWin.y = Win1Y;
    finWin.x = Win2X;
    finWin.y = Win2Y;

    initLine.x = Pnt1X;
    initLine.y = Pnt1Y;
    finLine.x = Pnt2X;
    finLine.y = Pnt2Y;  */

    glutDisplayFunc(init_clip);
    close_graph();

    return 0;
}
