#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

// default
struct global
{
    int width;
    int height;
    char title[50];
    struct
    {
        int x1;
        int x2;
        int y1;
        int y2;
    } bound;
};

struct global g = {
    .width = 1000,
    .height = 1000,
    .title = "2D Scaling",
    .bound = {
        .x1 = -10,
        .x2 = 10,
        .y1 = -10,
        .y2 = 10
    }
};

// Define the shape vertices
GLfloat vertices[][2] = {
    {1.0, 1.0},
    {2.0, 1.0},
    {2.0, 2.0},
    {1.0, 2.0}
};

// Define the scaling factor
GLfloat scale_factor = 2;

// Define the translation factors to show the image properly along x-axis
GLfloat tx = 1;
GLfloat ty = -1;

void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0); // Set background color to white
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(g.bound.x1, g.bound.x2, g.bound.y1, g.bound.y2); // Set the window coordinates
    glViewport(0, 0, g.width, g.height);                        // Set the viewport to match the window size
}

void reshape(int width, int height)
{
    // Update the global width and height variables
    g.width = width;
    g.height = height;

    // Calculate the aspect ratio of the shape
    float aspect_ratio = (g.bound.x2 - g.bound.x1) / (g.bound.y2 - g.bound.y1);

    // Compute the center of the bounding box
    float cx = (g.bound.x1 + g.bound.x2) / 2.0;
    float cy = (g.bound.y1 + g.bound.y2) / 2.0;

    // Set the viewport to fill the largest square that fits within the window
    int size = width < height ? width : height;
    int x = (width - size) / 2;
    int y = (height - size) / 2;
    glViewport(x, y, size, size);

    // Set the orthographic projection matrix to maintain the aspect ratio of the shape
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (aspect_ratio > 1)
    {
        float left = (g.bound.x1 - cx) * aspect_ratio;
        float right = (g.bound.x2 - cx) * aspect_ratio;
        glOrtho(left, right, g.bound.y1 - cy, g.bound.y2 - cy, -1.0, 1.0);
    }
    else
    {
        float bottom = (g.bound.y1 - cy) / aspect_ratio;
        float top = (g.bound.y2 - cy) / aspect_ratio;
        glOrtho(g.bound.x1 - cx, g.bound.x2 - cx, bottom, top, -1.0, 1.0);
    }

    // Switch back to the modelview matrix
    glMatrixMode(GL_MODELVIEW);
}

void axis(void)
{
    // Draw the x and y axes
    glColor3f(0.0, 0.0, 0.0); // Set color to black
    glBegin(GL_LINES);
    glVertex2f(g.bound.x1, 0.0); // Draw the x-axis
    glVertex2f(g.bound.x2, 0.0);
    glVertex2f(0.0, g.bound.y1); // Draw the y-axis
    glVertex2f(0.0, g.bound.y2);
    glEnd();

    // Draw the x-axis tick marks
    int num_ticks_x = (int)(g.bound.x2 - g.bound.x1);
    GLfloat tick_size_x = 0.1;
    GLfloat tick_spacing_x = (g.bound.x2 - g.bound.x1) / num_ticks_x;
    glColor3f(0.0, 0.0, 0.0); // Set color to black
    glBegin(GL_LINES);
    for (register int i = 0; i <= num_ticks_x; i++)
    {
        glVertex2f(g.bound.x1 + i * tick_spacing_x, -tick_size_x);
        glVertex2f(g.bound.x1 + i * tick_spacing_x, tick_size_x);
    }
    glEnd();

    // Draw the y-axis tick marks
    int num_ticks_y = (int)(g.bound.y2 - g.bound.y1);
    GLfloat tick_size_y = 0.1;
    GLfloat tick_spacing_y = (g.bound.y2 - g.bound.y1) / num_ticks_y;
    glColor3f(0.0, 0.0, 0.0); // Set color to black
    glBegin(GL_LINES);
    for (register int i = 0; i <= num_ticks_y; i++)
    {
        glVertex2f(-tick_size_y, g.bound.y1 + i * tick_spacing_y);
        glVertex2f(tick_size_y, g.bound.y1 + i * tick_spacing_y);
    }
    glEnd();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT); // Clear the window

    // Draw the first shape (original)
    glColor3f(1.0, 0.0, 0.0); // Set color to red
    glBegin(GL_POLYGON);
    for (register int i = 0; i < 4; i++)
    {
        glVertex2fv(vertices[i]);
    }
    glEnd();

    // Draw the second shape (scaled)
    glPushMatrix();                            // Save the current matrix
    glScalef(scale_factor, scale_factor, 2.0); // Scale the shape
    glTranslatef(tx, ty, 0.0);                 // Translate the shape
    glColor3f(0.0, 1.0, 0.0);                  // Set color to green

    glBegin(GL_POLYGON);
    for (register int i = 0; i < 4; i++)
    {
        glVertex2fv(vertices[i]);
    }
    glEnd();

    glPopMatrix(); // Restore the previous matrix
    axis();        // Draw the x and y axes
    glFlush();     // Render the scene
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(g.width, g.height);
    glutInitWindowPosition(0, 0);
    glutCreateWindow(g.title);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
