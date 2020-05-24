#include<iostream>
#include<math.h>
#include<GL/glut.h>

using namespace std;

double roundoff(double d)
{
    return floor(d + 0.5);
}

typedef float dim4 [4][4];

dim4 mat;

static GLfloat input[8][3]=
{
    {40,40,-50},{90,40,-50},{90,90,-50},{40,90,-50},
    {30,30,0},{80,30,0},{80,80,0},{30,80,0}

};

float trans[8][3];
float tx,ty,tz;
float sx,sy,sz;
float angle;

int sel,choiceRot;

void IdMat(dim4 m)
{
for(int i=0;i<4;i++)
    for(int j=0;j<4;j++)
        m[i][j]=(i==j);
}

void translate(float tx,float ty,float tz)
{

for(int i=0;i<8;i++)
{
trans[i][0]=input[i][0]+tx;
trans[i][1]=input[i][1]+ty;
trans[i][2]=input[i][2]+tz;
}
}
void scale(float sx, float sy, float sz)
{
    mat[0][0]=sx;
    mat[1][1]=sy;
    mat[2][2]=sz;
}
void RotateX(float angle) //Parallel to x
{

     angle = angle*3.142/180;
     mat[1][1] = cos(angle);
     mat[1][2] = -sin(angle);
     mat[2][1] = sin(angle);
     mat[2][2] = cos(angle);

}
void RotateY(float angle) //parallel to y
{

     angle = angle*3.14/180;
     mat[0][0] = cos(angle);
     mat[0][2] = -sin(angle);
     mat[2][0] = sin(angle);
     mat[2][2] = cos(angle);

}
void RotateZ(float angle) //parallel to z
{

     angle = angle*3.14/180;
     mat[0][0] = cos(angle);
     mat[0][1] = sin(angle);
     mat[1][0] = -sin(angle);
     mat[1][1] = cos(angle);

}

void MatMult()
{
for(int i=0;i<8;i++)
 {
    for(int j=0;j<3;j++)
    {
        trans[i][j]=0;
        for(int k=0;k<3;k++)
        {
            trans[i][j]=trans[i][j]+input[i][k]*mat[k][j];
        }
    }
}

}


void Axes(void)
{
 glColor3f (0.0, 0.0, 0.0);               
 glBegin(GL_LINES);                       
 glVertex2i(-1000 ,0);
 glVertex2i( 1000 ,0);
 glEnd();
 glBegin(GL_LINES);
 glVertex2i(0 ,-1000);
 glVertex2i(0 , 1000);
 glEnd();
} 
void draw(float a[8][3])
{

    glBegin(GL_QUADS);

    glColor3f(0.0,0.1,1.0);
    glVertex3fv(a[4]);
    glVertex3fv(a[5]);
    glVertex3fv(a[6]);
    glVertex3fv(a[7]);

    glColor3f(0.7,0.4,0.5); 
    glVertex3fv(a[0]);
    glVertex3fv(a[1]);
    glVertex3fv(a[2]);
    glVertex3fv(a[3]);

    glColor3f(0.8,0.2,0.4);  
    glVertex3fv(a[0]);
    glVertex3fv(a[1]);
    glVertex3fv(a[5]);
    glVertex3fv(a[4]);

    glColor3f(0.3,0.6,0.7); 
    glVertex3fv(a[0]);
    glVertex3fv(a[4]);
    glVertex3fv(a[7]);
    glVertex3fv(a[3]);

    glColor3f(0.2,0.8,0.2);  
    glVertex3fv(a[1]);
    glVertex3fv(a[2]);
    glVertex3fv(a[6]);
    glVertex3fv(a[5]);

    glColor3f(1,0.1,0.1); 
    glVertex3fv(a[2]);
    glVertex3fv(a[3]);
    glVertex3fv(a[7]);
    glVertex3fv(a[6]);

    glEnd();
}

void init()
{
    glClearColor(1.0,1.0,1.0,1.0); 
    glOrtho(-454.0,454.0,-250.0,250.0,-250.0,250.0);
    glEnable(GL_DEPTH_TEST);
}

void display()
{
glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
Axes();
glColor3f(1.0,0.0,0.0);
draw(input);
IdMat(mat);
switch(sel)
{
case 1:
    translate(tx,ty,tz);
    break;
 case 2:
    scale(sx,sy,sz);
MatMult();
    break;
 case 3:
    switch (choiceRot) {
    case 1:
        RotateX(angle);
        break;
    case 2: RotateY(angle);
        break;
    case 3:
        RotateZ(angle);
        break;
    default:
        break;
    }
MatMult();
    break;
}

draw(trans);
glFlush();

}

int main(int argc, char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(1362,750);
    glutInitWindowPosition(0,0);
    glutCreateWindow("VARIOUS 3D TRANSFORMATIONS");
    init();
    cout<<"Enter your sel number:\n1.Translation\n2.Scaling\n3.Rotation\n=>";
    cin>>sel;
    switch (sel) {
    case 1:
        cout<<"\nEnter the translation factors Tx,Ty &Tz: \n";
        cin>>tx>>ty>>tz;
        break;
    case 2:
        cout<<"\nEnter the scaling factors Sx,Sy & Sz: \n";
        cin>>sx>>sy>>sz;
        break;
    case 3:
        cout<<"Enter your sel for rotating the figure about one of the following axis:\n1.parallel to X-axis."
             <<"(y& z)\n2.parallel to Y-axis.(x& z)\n3.parallel to Z-axis."
              <<"(x& y)\n =>";
        cin>>choiceRot;
        switch (choiceRot) {
        case 1:
            cout<<"\nEnter the angle of Rotation: ";
            cin>>angle;
            break;
        case 2:
            cout<<"\nEnter the angle of Rotation: ";
            cin>>angle;
            break;
        case 3:
            cout<<"\nEnter the angle of Rotation: ";
            cin>>angle;
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }

    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
