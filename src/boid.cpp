/*********************************************************************************************************************
 * File : boid.cpp                                                                                                   *
 *                                                                                                                   *
 * 2020 Thomas Rouch                                                                                                 *
 *********************************************************************************************************************/

#include <GL/glut.h>

#include "boid.h"


Boid::Boid(const Vec3f &position, const Vec3f &speed) : id_(next_id_++),
                                                        position_(position),
                                                        speed_(speed)
{
}

void Boid::update(float dt)
{
    // Update position
    position_ += speed_ * dt;
}

void drawCube()
{
    glColor3f(1, 1, 1);
    glLineWidth(2.0);
    glBegin(GL_QUAD_STRIP);
    glColor3f(1, 1, 1);
    glNormal3f(0, 0, 1);
    glVertex3f(-1, -1, 1);
    glVertex3f(1, -1, 1);
    glVertex3f(-1, 1, 1);
    glVertex3f(1, 1, 1);
    glNormal3f(0, 1, 0);
    glVertex3f(-1, 1, -1);
    glVertex3f(1, 1, -1);
    glNormal3f(0, 0, -1);
    glVertex3f(-1, -1, -1);
    glVertex3f(1, -1, -1);
    glNormal3f(0, -1, 0);
    glVertex3f(-1, -1, 1);
    glVertex3f(1, -1, 1);
    glEnd();

    glBegin(GL_QUADS);
    glNormal3f(1, 0, 0);
    glVertex3f(1, 1, 1);
    glVertex3f(1, -1, 1);
    glVertex3f(1, -1, -1);
    glVertex3f(1, 1, -1);
    glEnd();
    glBegin(GL_QUADS);
    glNormal3f(-1, 0, 0);
    glVertex3f(-1, 1, 1);
    glVertex3f(-1, -1, 1);
    glVertex3f(-1, -1, -1);
    glVertex3f(-1, 1, -1);
    glEnd();
}

void Boid::draw() const
{
    std::cout << "Draw " << std::endl
              << "Position: " << position_.transpose() << std::endl
              << "Speed   : " << speed_.transpose() << std::endl;
    glPushMatrix();
    glTranslatef(position_[0], position_[1], position_[2]);
    drawCube();
    glPopMatrix();
}