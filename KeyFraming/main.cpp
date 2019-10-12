// standard
#include <assert.h>
#include <math.h>
#include <vector>
#include <iostream>
#include "interpolate.cpp"

// glut
#include <GLUT/glut.h>

using namespace std;
//================================
// global variables
//================================
// screen size
int g_screenWidth  = 0;
int g_screenHeight = 0;

std::vector<std::vector<float>> keyFrames;
std::vector<Event> events;
std::vector<float> current;
std::vector<float> quat;
GLfloat* rotationVector;
float dt = 1;
int counter = 0;
float PI = 3.14159;
bool quaternion = true;
bool curve = false;

//================================
// update
//================================
void update( void ) {
    // do something before rendering...
    current.clear();
    counter++;
    if (counter == events.size()) {
        counter = 0;
    }
}

//================================
// render
//================================
void render(void) {
    
    // clear buffer
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glClearDepth (1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // ensures that faces pointing away from camera are not rendered to front and defines shading model
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);

    // enable lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // light source attributes
    GLfloat LightSpecular[]    = {0.8f, 0.8f, 0.8f, 1.0f};
    GLfloat LightPosition[] = {5.0f, 5.0f, 5.0f, 1.0f};

    glLightfv(GL_LIGHT0, GL_SPECULAR, LightSpecular);
    glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);

    // surface material attributes
    GLfloat material_Ks[] = {0.33f, 0.33f, 0.52f, 1.0f};
    GLfloat material_Ke[] = {0.1f, 0.0f, 0.1f, 1.0f};
    GLfloat material_Se = 10;

    glMaterialfv(GL_FRONT, GL_SPECULAR, material_Ks);
    glMaterialfv(GL_FRONT, GL_EMISSION, material_Ke);
    glMaterialf (GL_FRONT, GL_SHININESS, material_Se);

    // modelview matrix
    current = events[counter].getFrame();
    
    // cout << rotationVector[0];
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(current[0], current[1], current[2]);
    // rotate by the specified amount around each axis (specified by vector)
    if (quaternion) {
        quat = events[counter].getQuaternion();
        glRotatef((quat[0]*180)/PI, quat[1], quat[2], quat[3]);
    }
    else {
        rotationVector = events[counter].getRotationVector();
        glMultMatrixf(rotationVector);
    }
    
    // render objects
    glutSolidTeapot(1.0);

    // disable lighting
    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHTING);

    // swap back and front buffers
    glutSwapBuffers();
}

//================================
// reshape: update viewport and projection matrix when the window is resized
//================================
void reshape(int w, int h) {
    // screen size
    g_screenWidth  = w;
    g_screenHeight = h;

    // viewport
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);

    // projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30, (GLfloat)w/(GLfloat)h, 1.0, 2000.0);
}


//================================
// timer: triggered every 16ms (about 60 frames per second)
//================================
void timer(int value) {
    update();
    // tells the program that it needs to call the render function again
    glutPostRedisplay();
    // reset timer
    // 16 ms per frame (about 60 frames per second)
    glutTimerFunc(16, timer, 0);
}

//================================
// input: gets the input from the user
//================================
static void input() {
    int numKeys = 0;
    int resp1 = 0;
    int resp2 = 0;
    bool curve;
    float x; float y; float z; float theta; float phi; float omega; float psi;
    
    // asks user to specify the number of key frames to generate
    while (numKeys < 4) {
        cout << "How many key frames (at least 4) do you want to specify: ";
        cin >> numKeys;
        if (numKeys > 4) {
            break;
        }
    }
    
    // gets whether the user would like to use catmull-rom or b-spline
    cout << "Would you like to use a catmull-rom curve (1 or 0): ";
    cin >> resp1;
    
    if (resp1 == 1) {
        curve = true;
    }
    else {
        curve = false;
    }
    
    // gets whether user will use quaternions or fixed angles
    cout << "Would you like to use quaternions (1 or 0): ";
    cin >> resp2;
    
    if (resp2 == 1) {
        quaternion = true;
    }
    else {
        quaternion = false;
    }
    
    std::vector<float> tmp_vector;
    // gets user input for each key frame
    for (int i = 0; i < numKeys; i++) {
        tmp_vector.clear();
        cout << "x" << i+1 << ": ";
        cin >> x;
        cout << "y: " << i+1 << ": ";
        cin >> y;
        cout << "z: " << i+1 << ": ";
        cin >> z;
        cout << "theta: " << i+1 << ": ";
        cin >> theta;
        cout << "phi: " << i+1 << ": ";
        cin >> phi;
        cout << "omega: " << i+1 << ": ";
        cin >> omega;
        tmp_vector.push_back(x);
        tmp_vector.push_back(y);
        tmp_vector.push_back(z);
        tmp_vector.push_back(theta);
        tmp_vector.push_back(phi);
        tmp_vector.push_back(omega);
        tmp_vector.push_back(psi);
        keyFrames.push_back(tmp_vector);
    }
    cout << "dt: ";
    cin >> dt;
}

//================================
// main
//================================
int main(int argc, char** argv) {
    
      input();
    
//     a default keyFrames matrix to recreate the animation in my .mp4
//    keyFrames = {
//        {1,1,-50,15,45,13},
//        {2,2,-13,90,12,13},
//        {0,1,-10,15,270,13},
//        {0,0,-100,15,100,360},
//        {-1,-1,-15,40,0,13},
//        {-1,0,-15,100,120,40},
//        {1,0,-15,15,350,13}
//    };
//
    // call to the interpolate class to interpolate the defined keyFrames
    Interpolate interpolate (keyFrames, curve, quaternion, dt);
    events = interpolate.getEvents();
    
    // create opengL window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(1000, 1000);
    glutCreateWindow(argv[0]);

    // set callback functions
    glutDisplayFunc(render);
    glutReshapeFunc(reshape);
    glutTimerFunc(16, timer, 0);

    // main loop
    glutMainLoop();

    return 0;
}
