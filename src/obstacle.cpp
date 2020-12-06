/*********************************************************************************************************************
 * File : obstacle.cpp                                                                                               *
 *                                                                                                                   *
 * 2020 Thomas Rouch                                                                                                 *
 *********************************************************************************************************************/

#include <GL/glut.h>
#include <iostream>
#include "obstacle.h"
#include "gl_utils.h"

float Obstacle::obstacle_factor_ = 100.f;

Obstacle::Obstacle(const Vec3f &position, float radius) : MovingObject(position)
{
    boid_type_ = 3; // Obstacle

    radius_ = radius;

    rad_max_ = 1.2 * radius_;
}

Vec3f Obstacle::get_exerced_proximity_force(const MovingObject &object) const
{
    if (object.get_id() == id_) // Can't repel itself
        return Vec3f(0, 0, 0);

    // Repel
    Vec3f diff = object.get_position() - position_;
    float dist = diff.norm();
    if (dist > rad_max_)
        return Vec3f(0, 0, 0);

    return obstacle_factor_ * diff.normalized() * (1.0 / dist - 1.0 / rad_max_);
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