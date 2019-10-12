// standard
#include <assert.h>
#include <math.h>

// glut
#include <GLUT/glut.h>

int main(int argc, char **argv) {
    
    // init and create window for application
    glutInit(&argc, argv);
    glutInitWindowPosition(500, 200);
    glutInitWindowSize(500, 500);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("Andy's first time using OpenGL");
    
    return 0;
    
}
