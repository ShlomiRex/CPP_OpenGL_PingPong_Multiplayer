#include <GL/gl.h>
#include <GL/glut.h>

#define ORTHO_SCALE 10.

GLfloat triangle_vertices[] = {
    -0.5, 0.0,
     0.5, 0.0,
     0.0, 1.0
};

struct {
    struct {
        struct {
            GLfloat x, y;
        } pos;
        GLfloat rot;
    } triangle;
} sceneinfo;


void display(void)
{
    GLuint win_width, win_height;
    GLfloat win_aspect;

    win_width  = glutGet(GLUT_WINDOW_WIDTH);
    win_height = glutGet(GLUT_WINDOW_HEIGHT);
    win_aspect = (float)win_width/(float)win_height;

    glViewport(0, 0, win_width, win_height);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-win_aspect * ORTHO_SCALE, 
             win_aspect * ORTHO_SCALE, 
        -ORTHO_SCALE, 
         ORTHO_SCALE,
         -1., 1.);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPushMatrix();

    glTranslatef(sceneinfo.triangle.pos.x, sceneinfo.triangle.pos.y, 0.);
    glRotatef(sceneinfo.triangle.rot, 0, 0, 1.);

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, triangle_vertices);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glPopMatrix();

    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
    switch(key) {
    case '+':
        sceneinfo.triangle.rot += 2.;
        break;
    case '-':
        sceneinfo.triangle.rot -= 2.;
        break;
    }
    glutPostRedisplay();
}

void special(int key, int x, int y)
{
    switch(key) {
    case GLUT_KEY_LEFT:
        sceneinfo.triangle.pos.x -= 0.2;
        break;
    case GLUT_KEY_RIGHT:
        sceneinfo.triangle.pos.x += 0.2;
        break;
    case GLUT_KEY_UP:
        sceneinfo.triangle.pos.y += 0.2;
        break;
    case GLUT_KEY_DOWN:
        sceneinfo.triangle.pos.y -= 0.2;
        break;
    }
    glutPostRedisplay();
}


int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

    glutCreateWindow("simple triangle test");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard); //Normal keyboard
    glutSpecialFunc(special); //Special keyboard characters (such as arrow keys)

    glutMainLoop();

    return 0;
}