/*********************************************************************************************************************
 * File : obstacle.cpp                                                                                               *
 *                                                                                                                   *
 * 2020 Thomas Rouch                                                                                                 *
 *********************************************************************************************************************/

#include <GL/glut.h>
#include <iostream>
#include "obstacle.h"
#include "gl_utils.h"

float Obstacle::obstacle_factor_ = 10.f;

Obstacle::Obstacle(const Vec3f &position, int radius) : MovingObject(position)
{
    boid_type_ = 3; // Obstacle

    radius_ = radius;
}

Vec3f Obstacle::get_exerced_proximity_force(const MovingObject &object) const
{
    if (object.get_id() == id_) // Can't repel itself
        return Vec3f(0, 0, 0);

    // Repel
    Vec3f diff = object.get_position() - position_;
    const float dist = diff.norm();
    return obstacle_factor_ * diff.normalized() / (dist * dist);
}

void Obstacle::update(float t)
{
}

void Obstacle::draw() const
{
    glPushMatrix();
    glTranslatef(position_[0], position_[1], position_[2]);
    glColor3f(0.2, 0.3, 0.8);
    glutSolidSphere(radius_, 20, 20);
    glPopMatrix();
}