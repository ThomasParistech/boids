/*********************************************************************************************************************
 * File : main.cpp                                                                                                   *
 *                                                                                                                   *
 * 2020 Thomas Rouch                                                                                                 *
 *********************************************************************************************************************/

#include <vector>
#include <GL/glut.h>
#include "camera_trackball.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glut.h"
#include "imgui/imgui_impl_opengl2.h"

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
    camera.init({0.0f, 0.0f, 0.0f}, 30.0f);

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

    ImGui_ImplOpenGL2_NewFrame();
    ImGui_ImplGLUT_NewFrame();

    ImGui::Begin("Test");
    ImGui::SliderFloat("Separation", &MovingObject::separation_factor_, 0.0f, 0.1f);
    ImGui::SliderFloat("Cohesion", &MovingObject::cohesion_factor_, 0.0f, 0.1f);
    ImGui::SliderFloat("Alignment", &MovingObject::alignment_factor_, 0.0f, 0.1f);
    ImGui::SliderFloat("Target attraction", &MovingObject::target_attraction_factor_, 0.0f, 0.1f);
    ImGui::SliderFloat("Randomness", &MovingObject::randomness_, 0.0f, 0.1f);

    ImGui::End();

    //Camera setup
    camera.lookAt();

    for (const auto &boid : boids_)
        boid.draw();

    ImGui::Render();
    ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

    glutSwapBuffers();
}

void reshape(int w, int h)
{
    ImGui_ImplGLUT_ReshapeFunc(w, h);

    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(FOVY, (GLfloat)w / (GLfloat)h, NEARCLIP, FARCLIP);
}

void processKeys(unsigned char key, int x, int y)
{
    ImGui_ImplGLUT_KeyboardFunc(key, x, y);
}

void systemEvolution()
{
    for (auto &boid_1 : boids_)
        for (auto &boid_2 : boids_)
            if (boid_1.get_id() != boid_2.get_id())
                boid_1.add_neighbor(boid_2);

    const float t = (float)glutGet(GLUT_ELAPSED_TIME) * 0.001;
    for (auto &boid : boids_)
        boid.update(t);
}

void mouseButton(int button, int state, int x, int y)
{
    ImGui_ImplGLUT_MouseFunc(button, state, x, y);
    if (ImGui::GetIO().WantCaptureMouse)
        return;

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
    ImGui_ImplGLUT_MotionFunc(x, y);
    if (ImGui::GetIO().WantCaptureMouse)
        return;

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
    // Init GLUT and create window
    glutInit(&argc, argv);
    glutInitWindowSize(window_w, window_h);
    glutInitWindowPosition(WINDOW_X, WINDOW_Y);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glViewport(0, 0, window_w, window_h);
    glutCreateWindow("Test window");

    init();

    // Register callbacks
    glutDisplayFunc(display);
    glutIdleFunc(systemEvolution);
    glutTimerFunc(1000 / FPS, timer, 0);

    // Setup Dear ImGui context
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGLUT_Init();
    ImGui_ImplGLUT_InstallFuncs();
    ImGui_ImplOpenGL2_Init();

    // Replace some handlers after ImGui_ImplGLUT_InstallFuncs() sets its own
    // our impls will call the Imgui impls internally
    glutPassiveMotionFunc(mousePassiveMotion);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouseButton);
    glutKeyboardFunc(processKeys);
    glutMotionFunc(mouseMotion);

    glutMainLoop();

    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplGLUT_Shutdown();
    ImGui::DestroyContext();
    return 0;
}
