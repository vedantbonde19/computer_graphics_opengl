#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <cstring>
#include <vector>
#include <GL/glut.h>

using namespace std;

typedef struct {
    GLfloat x, y;
} Pnt;

GLint roundoff(GLfloat a) {
    return (GLint) (a + 0.5f);
}

const GLint BIT_LEFT = 0x01;
const GLint BIT_RIGHT = 0x02;
const GLint BIT_BOTTOM = 0x04;
const GLint BIT_TOP = 0x08;

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

void swap_points(Pnt *p1, Pnt *p2) {
    Pnt t = *p1;
    *p1 = *p2;
    *p2 = t;
}

void swap_codes(GLint *x, GLint *y) {
    GLint t = *x;
    *x = *y;
    *y = t;
}

GLint inside(GLint code) {
    return !code;
}

GLint accept(GLint code1, GLint code2) {
    return !(code1 | code2);
}

GLint reject(GLint code1, GLint code2) {
    return code1 & code2;
}

GLint divide(Pnt p1, Pnt init_win, Pnt fin_win) {
    GLint code = 0x00;

    if (p1.x < init_win.x) code |= BIT_LEFT;
    if (p1.x > fin_win.x) code |= BIT_RIGHT;
    if (p1.y < init_win.y) code |= BIT_BOTTOM;
    if (p1.y > fin_win.y) code |= BIT_TOP;
    return code;
}


void line_clip(Pnt p1, Pnt p2, Pnt init_win, Pnt fin_win) {
    GLint code1, code2;
    GLint done = 0, plot_line = 0;
    GLfloat m = 0;
    if (p1.x != p2.x) {
        m = (p2.y - p1.y) / (p2.x - p1.x);
    }
    while (!done) {
        code1 = divide(p1, init_win, fin_win);
        code2 = divide(p2, init_win, fin_win);
        if (accept(code1, code2)) {
            done = 1;
            plot_line = 1;
        } else if (reject(code1, code2)) {
            done = 1;
        } else {
            if (inside(code1)) {
                swap_points(&p1, &p2);
                swap_codes(&code1, &code2);
            }


            if (code1 & BIT_LEFT) {
                p1.y += (init_win.x - p1.x) * m;
                p1.x = init_win.x;
            } else if (code1 & BIT_RIGHT) {
                p1.y += (fin_win.x - p1.x) * m;
                p1.x = fin_win.x;
            } else if (code1 & BIT_BOTTOM) {
                if (p1.x != p2.x)
                    p1.x += (init_win.y - p1.y) / m;
                p1.y = init_win.y;
            } else if (code1 & BIT_TOP) {
                if (p1.x != p2.x)
                    p1.x += (fin_win.y - p1.y) / m;
                p1.y = fin_win.y;
            }
        }
    }

    if (plot_line) {
        glColor3f(1, 0, 0);
        glLineWidth(2);
        glBegin(GL_LINES);
        glVertex2i(roundoff(p1.x), roundoff(p1.y));
        glVertex2i(roundoff(p2.x), roundoff(p2.y));
        glEnd();
        glFlush();
    }
}

void draw_window(Pnt init_win, Pnt fin_win) {

    glColor3f(0, 0, 0);
    glBegin(GL_LINE_LOOP);
    glVertex2i(roundoff(init_win.x), roundoff(init_win.y));
    glVertex2i(roundoff(init_win.x), roundoff(fin_win.y));
    glVertex2i(roundoff(fin_win.x), roundoff(fin_win.y));
    glVertex2i(roundoff(fin_win.x), roundoff(init_win.y));
    glEnd();
    glFlush();
}

void draw_line(Pnt Pnt1, Pnt Pnt2) {

    glColor3f(0, 0, 1);
    glBegin(GL_LINE_LOOP);
    glVertex2i(roundoff(Pnt1.x), roundoff(Pnt1.y));
    glVertex2i(roundoff(Pnt2.x), roundoff(Pnt2.y));

    glEnd();
    glFlush();
} 


Pnt initWin, finWin, initLine, finLine;

void init_clip() {
    glClear(GL_COLOR_BUFFER_BIT);

    //Pnt init_win = {60, 60};
    //Pnt fin_win = {470, 290};
    draw_window(initWin, finWin);
    //Pnt p1 = {50, 50};
    //Pnt p2 = {490, 310};
    glColor3f(0, 0, 1);

    draw_line(initLine, finLine);

    glBegin(GL_LINES);
    glVertex2i(roundoff(initLine.x), roundoff(initLine.y));
    glVertex2i(roundoff(finLine.x), roundoff(finLine.y));
    glEnd();
    line_clip(initLine, finLine, initWin, finWin);
}

int main(int argc, char **argv) {

    initialize(argc, argv);

    int Win1X, Win1Y, Win2X, Win2Y;
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
    finLine.y = Pnt2Y;

    glutDisplayFunc(init_clip);
    close_graph();

    return 0;
}