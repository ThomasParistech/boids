/*********************************************************************************************************************
 * File : boid.cpp                                                                                                   *
 *                                                                                                                   *
 * 2020 Thomas Rouch                                                                                                 *
 *********************************************************************************************************************/

#include <GL/glut.h>

#include "boid.h"
#include "gl_utils.h"


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


void Boid::draw() const
{
    std::cout << "Draw " << std::endl
              << "Position: " << position_.transpose() << std::endl
              << "Speed   : " << speed_.transpose() << std::endl;
    glPushMatrix();

    glTranslatef(position_[0], position_[1], position_[2]);
    GlUtils::align_view(speed_);
    GlUtils::draw_box(Vec3f(0.6, 0.3, 0.3));

    glTranslatef(-0.6, 0, 0);
    GlUtils::draw_yz_plane(0.4, 0.4, Vec3f(0.0, 0.0, 1.0));

    glTranslatef(1.2, 0, 0);
    GlUtils::draw_pyramid(Vec3f(0.1, 0.1, 0.1), Vec3f(1.0, 1.0, 0.0));
    glPopMatrix();
}