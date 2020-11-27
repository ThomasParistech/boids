/*********************************************************************************************************************
 * File : main.cpp                                                                                                   *
 *                                                                                                                   *
 * 2020 Thomas Rouch                                                                                                 *
 *********************************************************************************************************************/

#include <vector>
#include <GL/glut.h>
#include "camera_trackball.h"

#include "boid.h"
const float FOVY = 60.0f;
const float NEARCLIP = 0.1f;
const float FARCLIP = 100.0f;
const int FPS = 30;
const int WINDOW_X = 700;
const int WINDOW_Y = 100;

// Inputs
int mouse_x = 0;
int mouse_y = 0;
int mouse_buttons[GLUT_NUM_MOUSE_BUTTONS];
int window_w = 800;
int window_h = 600;

// Camera
CameraTrackball camera;

// Time management
float t = 0;
float last_t = 0;
float dt = 0;


std::vector<Boid> boids_;

void init(void)
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);

    // Init inputs
    for (int i(0); i < GLUT_NUM_MOUSE_BUTTONS; ++i)
        mouse_buttons[i] = GLUT_UP;

    // Init camera
    camera.init({0.0f, 0.0f, 0.0f}, 10.0f);

    for (int j = 0; j < 30; j++)
    {
        int scale = 10;
        float x = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
        float y = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
        float z = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);

        float u = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
        float v = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
        float w = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
        boids_.emplace_back(scale * Vec3f(x, y, z), Vec3f(u, v, w));
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Camera setup
    camera.lookAt();

    for (const auto &boid : boids_)
        boid.draw();

    glutSwapBuffers();
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(FOVY, (GLfloat)w / (GLfloat)h, NEARCLIP, FARCLIP);
}

void processKeys(unsigned char key, int x, int y)
{
}

void systemEvolution()
{
    last_t = t;
    t = (float)glutGet(GLUT_ELAPSED_TIME);
    dt = (t - last_t) * 0.001;

    for (auto &boid_1 : boids_)
        for (auto &boid_2 : boids_)
            if (boid_1.get_id() != boid_2.get_id())
                boid_1.add_neighbor(boid_2);

    for (auto &boid : boids_)
        boid.update(dt);
}

void mouseButton(int button, int state, int x, int y)
{
    mouse_buttons[button] = state;

    // Update camera
    camera.zoom(mouse_buttons[3] - mouse_buttons[4]);
}

void mousePassiveMotion(int x, int y)
{
    mouse_x = x;
    mouse_y = y;
}

void mouseMotion(int x, int y)
{
    int mouse_dx = mouse_x - x;
    int mouse_dy = mouse_y - y;
    float dxn = static_cast<float>(mouse_dx) / static_cast<float>(window_w);
    float dyn = -static_cast<float>(mouse_dy) / static_cast<float>(window_h);
    mouse_x = x;
    mouse_y = y;

    // Update camera
    if (mouse_buttons[GLUT_LEFT_BUTTON] == GLUT_DOWN)
        camera.rotate(dxn, dyn);
    if (mouse_buttons[GLUT_RIGHT_BUTTON] == GLUT_DOWN)
        camera.pan(dxn, dyn, 0.0f);
}

void timer(int v)
{
    glutPostRedisplay();
    glutTimerFunc(1000 / FPS, timer, 0);
}

// Main function: GLUT runs as a console application
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(window_w, window_h);
    glutInitWindowPosition(WINDOW_X, WINDOW_Y);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glViewport(0, 0, window_w, window_h);
    glutCreateWindow("Test window");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouseButton);
    glutPassiveMotionFunc(mousePassiveMotion);
    glutKeyboardFunc(processKeys);
    glutMotionFunc(mouseMotion);

    glutIdleFunc(systemEvolution);
    glutTimerFunc(1000 / FPS, timer, 0);

    glutMainLoop();

    return 0;
}
