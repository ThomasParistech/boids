/*********************************************************************************************************************
 * File : moving_object.cpp                                                                                          *
 *                                                                                                                   *
 * 2020 Thomas Rouch                                                                                                 *
 *********************************************************************************************************************/

#include <GL/glut.h>

#include "boid.h"
#include "gl_utils.h"
#include <iostream>

Boid::Boid(const Vec3f &position, const Vec3f &speed) : MovingObject(position, speed)
{
    boid_type_ = 1;

    last_t_ = 0;

    n_neighbors_ = 0;
    avg_position_ = Vec3f(0, 0, 0);
    avg_speed_ = Vec3f(0, 0, 0);
    proximity_force_ = Vec3f(0, 0, 0);

    float r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    float g = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    float b = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);

    color_ = Vec3f(r, g, b);
}

void Boid::add_neighbor(const MovingObject &object)
{
    if (boid_type_ == object.get_type()) // different for each child class
    {
        // Vision angle
        const Vec3f diff = object.get_position() - position_;
        if (diff.dot(speed_) >= min_cos_angle_ * speed_.norm() * diff.norm())
        {
            n_neighbors_++;

            // Cohesion
            avg_position_ += object.get_position();

            // Alignment
            avg_speed_ += object.get_speed();
        }
    }

    // Separation + Target attraction
    proximity_force_ += object.get_exerced_proximity_force(*this);
}

Vec3f Boid::get_exerced_proximity_force(const MovingObject &object) const
{
    if (object.get_id() == id_) // Can't repel itself
        return Vec3f(0, 0, 0);

    // Separation
    const Vec3f diff = object.get_position() - position_;
    const auto dist = std::max(separation_min_dist_, diff.norm()); // In case close to zero
    return separation_factor_ * diff / (dist * dist);
}

void Boid::update(float t)
{
    Vec3f speed_incr(0, 0, 0);
    // Update speed
    if (n_neighbors_ != 0)
    {
        const Vec3f cohesion_force = avg_position_ / n_neighbors_ - position_;
        const Vec3f alignment_force = avg_speed_ / n_neighbors_ - speed_;

        speed_incr += cohesion_factor_ * cohesion_force;
        speed_incr += alignment_factor_ * alignment_force;
    }

    const float dv_x = -0.5 + static_cast<float>(std::rand()) / RAND_MAX;
    const float dv_y = -0.5 + static_cast<float>(std::rand()) / RAND_MAX;
    const float dv_z = -0.5 + static_cast<float>(std::rand()) / RAND_MAX;

    const Vec3f random_force = randomness_ * Vec3f(dv_x, dv_y, dv_z);
    speed_incr += random_force;

    speed_incr += proximity_force_;

    // Clamp speed if needed
    speed_ += speed_incr;
    if (speed_.norm() > max_speed_)
        speed_ = max_speed_ * speed_.normalized();

    // Update position
    const float dt = (t - last_t_);
    last_t_ = t;
    position_ += speed_ * dt;

    // Update color: Red if a lot of proximity forces
    const double cos_angle_x = 0.5 * (1 + speed_.dot(Vec3f::UnitX()) / speed_.norm());
    const double cos_angle_y = 0.5 * (1 + speed_.dot(Vec3f::UnitY()) / speed_.norm());
    const double cos_angle_z = 0.5 * (1 + speed_.dot(Vec3f::UnitZ()) / speed_.norm());
    color_ = Vec3f(cos_angle_x, cos_angle_y, cos_angle_z);

    // Clear
    n_neighbors_ = 0;
    avg_position_ = Vec3f(0, 0, 0);
    avg_speed_ = Vec3f(0, 0, 0);
    proximity_force_ = Vec3f(0, 0, 0);
}

void Boid::draw() const
{
    glPushMatrix();

    glTranslatef(position_[0], position_[1], position_[2]);
    GlUtils::align_view(speed_);
    GlUtils::draw_box(Vec3f(0.6, 0.1, 0.1), color_);

    glTranslatef(-0.6, 0, 0);
    GlUtils::draw_yz_plane(0.3, 0.3, Vec3f(0.0, 0.0, 1.0));

    glTranslatef(1.2, 0, 0);
    GlUtils::draw_pyramid(Vec3f(0.4, 0.1, 0.1), Vec3f(1.0, 1.0, 0.0));
    //GlUtils::draw_pyramid(size_ * Vec3f(1.0, 0.1, 0.1), Vec3f(0.2, 0.3, 0.8));
    glPopMatrix();
}