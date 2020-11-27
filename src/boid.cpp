/*********************************************************************************************************************
 * File : boid.cpp                                                                                                   *
 *                                                                                                                   *
 * 2020 Thomas Rouch                                                                                                 *
 *********************************************************************************************************************/

#include <GL/glut.h>

#include "boid.h"
#include "gl_utils.h"

float Boid::neighborhood_max_dist_ = 10;

float Boid::separation_min_dist_ = 1;

float Boid::separation_factor_ = 0.1;
float Boid::cohesion_factor_ = 0.05;
float Boid::alignment_factor_ = 0.04;

float Boid::randomness_ = 0;

int Boid::next_id_ = 0;

bool Boid::are_neighbors(const Boid &left, const Boid &right)
{
    return (left.get_position() - right.get_position()).norm() < neighborhood_max_dist_;
}

Boid::Boid(const Vec3f &position, const Vec3f &speed) : id_(next_id_++),
                                                        position_(position),
                                                        speed_(speed),
                                                        n_neighbors_(0),
                                                        avg_position_{0, 0, 0},
                                                        avg_speed_{0, 0, 0},
                                                        separation_force_{0, 0, 0},
                                                        size_(1.0)
{
}

void Boid::add_neighbor(const Boid &boid)
{
    n_neighbors_++;

    // Cohesion
    avg_position_ += boid.get_position();

    // Alignment
    avg_speed_ += boid.get_speed();

    // Separation
    if (boid.get_id() != id_) // Can't repel itself
    {
        const Vec3f diff = position_ - boid.get_position();
        const auto dist = std::max(separation_min_dist_, diff.norm()); // In case close to zero
        separation_force_ += diff / (dist * dist);
    }
}

#include <iostream>
void Boid::update(float dt)
{
    // Update speed
    if (n_neighbors_ != 0)
    {
        const Vec3f cohesion_force = 1.0 / n_neighbors_ * avg_position_ - position_;
        const Vec3f alignment_force = 1.0 / n_neighbors_ * avg_speed_ - speed_;

        const float dv_x = -0.5 + static_cast<float>(std::rand()) / RAND_MAX;
        const float dv_y = -0.5 + static_cast<float>(std::rand()) / RAND_MAX;
        const float dv_z = -0.5 + static_cast<float>(std::rand()) / RAND_MAX;

        const Vec3f random_force = randomness_ * Vec3f(dv_x, dv_y, dv_z);

        speed_ += separation_factor_ * separation_force_;
        speed_ += cohesion_factor_ * cohesion_force;
        speed_ += alignment_factor_ * alignment_force;
        speed_ += random_force;
    }

    // Update position
    position_ += speed_ * dt;

    // Clear
    n_neighbors_ = 0;
    avg_position_ = Vec3f(0, 0, 0);
    avg_speed_ = Vec3f(0, 0, 0);
    separation_force_ = Vec3f(0, 0, 0);
}


void Boid::draw() const
{
    std::cout << "Draw " << std::endl
              << "Position: " << position_.transpose() << std::endl
              << "Speed   : " << speed_.transpose() << std::endl;
    glPushMatrix();

    glTranslatef(position_[0], position_[1], position_[2]);
    GlUtils::align_view(speed_);
    // GlUtils::draw_box(Vec3f(0.6, 0.3, 0.3));

    // glTranslatef(-0.6, 0, 0);
    // GlUtils::draw_yz_plane(0.4, 0.4, Vec3f(0.0, 0.0, 1.0));

    // glTranslatef(1.2, 0, 0);
    // GlUtils::draw_pyramid(Vec3f(0.1, 0.1, 0.1), Vec3f(1.0, 1.0, 0.0));
    GlUtils::draw_pyramid(size_ * Vec3f(1.0, 0.1, 0.1), Vec3f(0.2, 0.3, 0.8));
    glPopMatrix();
}