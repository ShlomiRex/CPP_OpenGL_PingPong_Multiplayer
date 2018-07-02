#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h> // OpenGL Graphics Utility Library
#include <iostream>
#include "SimpleDraw.h"
using namespace std;
// These variables set the dimensions of the rectanglar region we wish to view.
const double Xmin = 0.0, Xmax = 3.0;
const double Ymin = 0.0, Ymax = 3.0;

double xDelta = 0;

void myKeyboardFunc(unsigned char key, int x, int y)
{
    glutPostRedisplay();
    switch (key)
    {
    case 'A':
    case 'a':
        xDelta -= 0.1;
        glutPostRedisplay();
        break;

    case 27: // "27" is the Escape key
        exit(1);
    }
}

/*
 * drawScene() handles the animation and the redrawing of the
 *		graphics window contents.
 */
void drawScene(void)
{
    // Clear the rendering window
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBegin(GL_TRIANGLES);
        glColor3f(1.0, 0.0, 0.0);
        glVertex3f(0.3 + xDelta, 1.0, 0.5);
        glVertex3f(2.7 + xDelta, 0.85, 0.0);
        glVertex3f(2.7 + xDelta, 1.15, 0.0);
    glEnd();
    // Flush the pipeline.  (Not usually necessary.)
    glFlush();
    glutSwapBuffers();
}

// Called when the window is resized
//		w, h - width and height of the window in pixels.
void resizeWindow(int w, int h)
{
    double scale, center;
    double windowXmin, windowXmax, windowYmin, windowYmax;

    // Define the portion of the window used for OpenGL rendering.
    glViewport(0, 0, w, h); // View port uses whole window

    // Set up the projection view matrix: orthographic projection
    // Determine the min and max values for x and y that should appear in the window.
    // The complication is that the aspect ratio of the window may not match the
    //		aspect ratio of the scene we want to view.
    w = (w == 0) ? 1 : w;
    h = (h == 0) ? 1 : h;
    if ((Xmax - Xmin) / w < (Ymax - Ymin) / h)
    {
        scale = ((Ymax - Ymin) / h) / ((Xmax - Xmin) / w);
        center = (Xmax + Xmin) / 2;
        windowXmin = center - (center - Xmin) * scale;
        windowXmax = center + (Xmax - center) * scale;
        windowYmin = Ymin;
        windowYmax = Ymax;
    }
    else
    {
        scale = ((Xmax - Xmin) / w) / ((Ymax - Ymin) / h);
        center = (Ymax + Ymin) / 2;
        windowYmin = center - (center - Ymin) * scale;
        windowYmax = center + (Ymax - center) * scale;
        windowXmin = Xmin;
        windowXmax = Xmax;
    }

    // Now that we know the max & min values for x & y that should be visible in the window,
    //		we set up the orthographic projection.
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(windowXmin, windowXmax, windowYmin, windowYmax, -1, 1);
}



/*
	glPointSize(8);
	glLineWidth(5);
    glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);	// Make round points, not square points
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);		// Antialias the lines
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
*/

int main(int argc, char **argv)
{
    glutInit(&argc, argv);

    // The image is not animated so single buffering is OK.
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    // Window position (from top corner), and size (width and hieght)
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Pong by shlomi.");

    glEnable(GL_DEPTH_TEST);
    glLineWidth(5);
    glPointSize(5);

    // Set up callback functions for key presses
    glutKeyboardFunc(myKeyboardFunc); // Handles "normal" ascii symbols
    // glutSpecialFunc( mySpecialKeyFunc );		// Handles "special" keyboard keys

    // Set up the callback function for resizing windows
    glutReshapeFunc(resizeWindow);

    // Call this for background processing
    // glutIdleFunc( myIdleFunction );

    // call this whenever window needs redrawing
    glutDisplayFunc(drawScene);

    fprintf(stdout, "Press space bar to toggle images; escape button to quit.\n");

    // Start the main loop.  glutMainLoop never returns.
    glutMainLoop();

    return (0); // This line is never reached.
}