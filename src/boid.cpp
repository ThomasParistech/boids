/*********************************************************************************************************************
 * File : moving_object.cpp                                                                                          *
 *                                                                                                                   *
 * 2020 Thomas Rouch                                                                                                 *
 *********************************************************************************************************************/

#include <GL/glut.h>

#include "boid.h"
#include "gl_utils.h"

Boid::Boid(const Vec3f &position, const Vec3f &speed) : MovingObject(position, speed)
{
    boid_type_ = 1;

    last_t_ = 0;

    n_neighbors_ = 0;
    avg_position_ = Vec3f(0, 0, 0);
    avg_speed_ = Vec3f(0, 0, 0);
    proximity_force_ = Vec3f(0, 0, 0);
}

void Boid::add_neighbor(const Boid &boid)
{
    if (boid_type_ == boid.get_type()) // different for each child class
    {
        n_neighbors_++;

        // Cohesion
        avg_position_ += boid.get_position();

        // Alignment
        avg_speed_ += boid.get_speed();
    }

    // Separation + Target attraction
    proximity_force_ += get_exerced_proximity_force(boid);
}

Vec3f Boid::get_exerced_proximity_force(const MovingObject &object)
{
    if (object.get_id() == id_) // Can't repel itself
        return Vec3f(0, 0, 0);

    // Separation
    const Vec3f diff = position_ - object.get_position();
    const auto dist = std::max(separation_min_dist_, diff.norm()); // In case close to zero
    return separation_factor_ * diff / (dist * dist);
}

void Boid::update(float t)
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

        speed_ += proximity_force_;
        speed_ += cohesion_factor_ * cohesion_force;
        speed_ += alignment_factor_ * alignment_force;
        speed_ += random_force;
    }

    // Update position
    const float dt = (t - last_t_);
    last_t_ = t;
    position_ += speed_ * dt;

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
    GlUtils::draw_box(Vec3f(0.6, 0.3, 0.3));

    glTranslatef(-0.6, 0, 0);
    GlUtils::draw_yz_plane(0.4, 0.4, Vec3f(0.0, 0.0, 1.0));

    glTranslatef(1.2, 0, 0);
    GlUtils::draw_pyramid(Vec3f(0.1, 0.1, 0.1), Vec3f(1.0, 1.0, 0.0));
    //GlUtils::draw_pyramid(size_ * Vec3f(1.0, 0.1, 0.1), Vec3f(0.2, 0.3, 0.8));
    glPopMatrix();
}