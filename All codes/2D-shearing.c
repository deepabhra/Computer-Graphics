#include <GL/glut.h>

// Define the vertices of a square
GLfloat vertices[] = {
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.5f, 0.5f, 0.0f,
    -0.5f, 0.5f, 0.0f};

// Define the indices of the square's edges
GLubyte indices[] = {
    0, 1,
    1, 2,
    2, 3,
    3, 0};

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the x and y axes
    glBegin(GL_LINES);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-1.5, 0.0, 0.0);
    glVertex3f(1.5, 0.0, 0.0);
    glVertex3f(0.0, -1.5, 0.0);
    glVertex3f(0.0, 1.5, 0.0);
    glEnd();


    // Draw the unsheared square
    glPushMatrix();
    glColor3f(0.0, 1.0, 1.0);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glDrawElements(GL_LINES, 8, GL_UNSIGNED_BYTE, indices);
    glDisableClientState(GL_VERTEX_ARRAY);
    glPopMatrix();

    // Shearing matrix along the y-axis
    GLfloat shearingMatrix[] = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.5f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f};
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glMultMatrixf(shearingMatrix);

    // Draw the sheared square
    glColor3f(1.0, 0.0, 0.0);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glDrawElements(GL_LINES, 8, GL_UNSIGNED_BYTE, indices);
    glDisableClientState(GL_VERTEX_ARRAY);

    glPopMatrix();

    glFlush();
}

void init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.5, 1.5, -1.5, 1.5, -1.5, 1.5);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Sheared square");
    glutDisplayFunc(display);
    init();
    glutMainLoop();
    return 0;
}
