#include "main.h"

using namespace std;
static thread client_network_thread_sendto;
static thread client_network_thread_recvfrom;

static player me;
static player opponent;
static moving_circle<int> ball;
static bool running = true;

void keyboardHandler(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'W':
        case 'w':
            me.body.updatePos(me.body.location.getX(), me.body.location.getY() + DeltaY);
            break;

        case 'S':
        case 's':
            me.body.updatePos(me.body.location.getX(), me.body.location.getY() - DeltaY);
            break;

        case 27: // "27" is the Escape key
            exit(1);
    }
}

//drawScene() handles the animation and the redrawing of the graphics window contents.
void drawScene(void)
{
    // Clear the rendering window
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(255,255,255);

    //Draw me
    glRecti(
        me.body.location.getX(), 
        me.body.location.getY(), 
        me.body.location.getX()+me.body.getWidth(),
        me.body.location.getY()+me.body.getHeight());
    //Draw my name?
    //TODO: Add text library

    //Draw opponent
    glRecti(
        opponent.body.location.getX(),
        opponent.body.location.getY(),
        opponent.body.location.getX()+opponent.body.getWidth(),
        opponent.body.location.getY()+opponent.body.getHeight());

    // Flush the pipeline.  (Not usually necessary.)
    glFlush();
    glutSwapBuffers();

    glutPostRedisplay(); //Re render, idle rendering...
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
    ////////////////////////////// User Input and Networking //////////////////////////////

    cout << "Do you want to join(j) or create(c) a game?" << endl;
    char choice = getchar();
    if(choice != 'c' && choice != 'j') {
        cerr << "You'r choice is incorrect." << endl;
        exit(1);
    }
    string server_ip;
    string tmp;
    cout << "Please enter ip (enter 'd' for default server ip): " << endl;
    cin >> tmp;

    if(tmp == "d")
        server_ip = SERVER_DEFAULT_IP;
    else
        server_ip = tmp;
    if(choice == 'j') {
        cout << "Joining a game..." << endl;
        start_client(server_ip, &me, &opponent);
        
        client_network_thread_sendto = thread(sendto_network_loop, &running, &me);
        client_network_thread_recvfrom = thread(recvfrom_network_loop, &running, &opponent);
    } else {
        cout << "Creating a game..." << endl;
        server_start(&server_ip);
        goto finish;
    }

    cout << "Starting game :D enjoy" << endl;

    ////////////////////////////// Rendering //////////////////////////////

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
    glutKeyboardFunc(keyboardHandler); // Handles "normal" ascii symbols
    // glutSpecialFunc( mySpecialKeyFunc );		// Handles "special" keyboard keys

    // Set up the callback function for resizing windows
    glutReshapeFunc(resizeWindow);

    // Call this for background processing
    // glutIdleFunc( myIdleFunction );

    // call this whenever window needs redrawing
    glutDisplayFunc(drawScene);

    // Start the main loop.  glutMainLoop never returns.
    glutMainLoop();

finish:
    return (0); // This line is never reached by client, but by server yes.
}
