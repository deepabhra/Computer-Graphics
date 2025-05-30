/************************************
Name: Abhradeep Guin
Program: Write a program in C to implement two-dimensional scaling with respect to a pivot point. Output depends upon user’s choice. [Use OpenGL Library]
Program No. 07
Date: 19/05/2025
************************************/

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

char title[] = "2D Scaling";
int winWidth = 1000;
int winHeight = 1000;
int range_x1 = -10;
int range_x2 = 10;
int range_y1 = -10;
int range_y2 = 10;

GLfloat scale_factor = 0;

float pivotX = 0.0;
float pivotY = 0.0;

GLfloat vertices[][2] = {
    {0.0, 0.0},
    {1.0, 0.0},
    {1.0, 1.0},
    {0.0, 1.0}};

void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, winWidth, 0, winHeight);
}

void drawAxes(void)
{
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(range_x1, 0.0);
    glVertex2f(range_x2, 0.0);
    glVertex2f(0.0, range_y1);
    glVertex2f(0.0, range_y2);
    glEnd();

    int num_ticks_x = (int)(range_x2 - range_x1);
    GLfloat tick_size_x = 0.1;
    GLfloat tick_spacing_x = (range_x2 - range_x1) / num_ticks_x;
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    for (register int i = 0; i <= num_ticks_x; i++)
    {
        glVertex2f(range_x1 + i * tick_spacing_x, -tick_size_x);
        glVertex2f(range_x1 + i * tick_spacing_x, tick_size_x);
    }
    glEnd();

    int num_ticks_y = (int)(range_y2 - range_y1);
    GLfloat tick_size_y = 0.1;
    GLfloat tick_spacing_y = (range_y2 - range_y1) / num_ticks_y;
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    for (register int i = 0; i <= num_ticks_y; i++)
    {
        glVertex2f(-tick_size_y, range_y1 + i * tick_spacing_y);
        glVertex2f(tick_size_y, range_y1 + i * tick_spacing_y);
    }
    glEnd();
}

void scale(float pivotX, float pivotY, GLfloat scale_factor, float scaled_vertices[][2])
{
    for (int i = 0; i < 4; i++)
    {
        scaled_vertices[i][0] = vertices[i][0] - pivotX;
        scaled_vertices[i][1] = vertices[i][1] - pivotY;
    }

    for (int i = 0; i < 4; i++)
    {
        scaled_vertices[i][0] *= scale_factor;
        scaled_vertices[i][1] *= scale_factor;
    }

    for (int i = 0; i < 4; i++)
    {
        scaled_vertices[i][0] += pivotX;
        scaled_vertices[i][1] += pivotY;
    }
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawAxes();

    float scaled_vertices[4][2];

    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 4; i++)
    {
        glVertex2fv(vertices[i]);
    }
    glEnd();
    glPopMatrix();

    scale(pivotX, pivotY, scale_factor, scaled_vertices);
    glPushMatrix();
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 4; i++)
    {
        glVertex2fv(scaled_vertices[i]);
    }
    glEnd();
    glPopMatrix();

    glFlush();
}

void reshape(int width, int height)
{
    float aspect_ratio = (range_x2 - range_x1) / (range_y2 - range_y1);

    float cx = (range_x1 + range_x2) / 2.0;
    float cy = (range_y1 + range_y2) / 2.0;

    int size = width < height ? width : height;
    int x = (width - size) / 2;
    int y = (height - size) / 2;
    glViewport(x, y, size, size);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (aspect_ratio > 1)
    {
        float left = (range_x1 - cx) * aspect_ratio;
        float right = (range_x2 - cx) * aspect_ratio;
        glOrtho(left, right, range_y1 - cy, range_y2 - cy, -1.0, 1.0);
    }
    else
    {
        float bottom = (range_y1 - cy) / aspect_ratio;
        float top = (range_y2 - cy) / aspect_ratio;
        glOrtho(range_x1 - cx, range_x2 - cx, bottom, top, -1.0, 1.0);
    }
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
    printf("Enter the pivot point for x and y: ");
    scanf("%f %f", &pivotX, &pivotY);
    printf("Enter the degree of scaling: ");
    scanf("%f", &scale_factor);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(winWidth, winHeight);
    glutCreateWindow(title);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
