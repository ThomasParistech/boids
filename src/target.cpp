/*********************************************************************************************************************
 * File : target.cpp                                                                                                 *
 *                                                                                                                   *
 * 2020 Thomas Rouch                                                                                                 *
 *********************************************************************************************************************/

#include <GL/glut.h>

#include "target.h"
#include "gl_utils.h"

float Target::target_attraction_factor_ = 0.02f;
float Target::target_speed_alignment_factor_ = 0.03f;

Target::Target(const Vec3f &position, UpdateSpeedFunc update_speed_func) : MovingObject(position)
{
    boid_type_ = 2; // TARGET

    update_speed_func_ = update_speed_func;
    last_t_ = 0;
    update(0);
}
#include <iostream>
Vec3f Target::get_exerced_proximity_force(const MovingObject &object) const
{
    if (object.get_id() == id_) // Can't repel itself
        return Vec3f(0, 0, 0);

    return target_attraction_factor_ * (position_ - object.get_position()) +
           target_speed_alignment_factor_ * (speed_ - object.get_speed()); // Attract
}

void Target::update(float t)
{
    update_speed_func_(t, speed_);
    const float dt = (t - last_t_);
    last_t_ = t;
    position_ += speed_ * dt;
}

void Target::draw() const
{
    glPushMatrix();
    glTranslatef(position_[0], position_[1], position_[2]);
    glColor3f(1, 0, 0);
    glutSolidSphere(1, 10, 10);
    glPopMatrix();
}