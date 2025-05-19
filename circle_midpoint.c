/************************************
Name: Abhradeep Guin
Program: Write a program in C to draw a circle by using midpoint circle drawing algorithm. [Use OpenGL Library]
Program No. 03
Date: 18/05/2025
************************************/
#include <GL/freeglut.h>
#include <math.h>

#define WIN_WIDTH 800
#define WIN_HEIGHT 600
#define POINT_SIZE 10

#define ORTHO_LEFT -(int)(WIN_WIDTH / POINT_SIZE) / 2
#define ORTHO_RIGHT (int)(WIN_WIDTH / POINT_SIZE) / 2
#define ORTHO_BOTTOM -(int)(WIN_HEIGHT / POINT_SIZE) / 2
#define ORTHO_TOP (int)(WIN_HEIGHT / POINT_SIZE) / 2

void drawCircle(int xc, int yc, int r)
{
    int p = 1 - r;
    int x = 0;
    int y = r;

    while (x <= y)
    {
        glColor3f(0.416, 0.173, 0.439);
        glBegin(GL_POINTS);
        glVertex2i(xc + x, yc + y);
        glVertex2i(xc + x, yc - y);
        glVertex2i(xc - x, yc + y);
        glVertex2i(xc - x, yc - y);
        glVertex2i(xc + y, yc + x);
        glVertex2i(xc + y, yc - x);
        glVertex2i(xc - y, yc + x);
        glVertex2i(xc - y, yc - x);
        glEnd();

        x = x + 1;
        if (p < 0)
        {
            p = p + 2 * x + 1;
        }
        else
        {
            y = y - 1;
            p = p + 2 * x - 2 * y + 1;
        }
    }
}

void drawAxes()
{
    glColor3f(0.941, 0.541, 0.365);
    glBegin(GL_LINES);
    glVertex2f(ORTHO_LEFT, 0);
    glVertex2f(ORTHO_RIGHT, 0);
    glVertex2f(0, ORTHO_BOTTOM);
    glVertex2f(0, ORTHO_TOP);
    glEnd();
}

void displayFunc()
{
    glClearColor(0.976, 0.929, 0.412, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    drawAxes();
    drawCircle(2, 5, 6);
    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
    glutCreateWindow("MidPoint Circle");

    gluOrtho2D(ORTHO_LEFT, ORTHO_RIGHT, ORTHO_BOTTOM, ORTHO_TOP);
    glPointSize(POINT_SIZE);

    glutDisplayFunc(displayFunc);
    glutMainLoop();
}