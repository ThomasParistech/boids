/*********************************************************************************************************************
 * File : boid.h                                                                                                     *
 *                                                                                                                   *
 * 2020 Thomas Rouch                                                                                                 *
 *********************************************************************************************************************/

#ifndef BOID_H
#define BOID_H

#include "moving_object.h"

class Boid : public MovingObject
{
public:
    Boid(const Vec3f &position, const Vec3f &speed = Vec3f(0, 0, 0));
    virtual ~Boid() = default;

    void add_neighbor(const Boid &boid);

    Vec3f get_exerced_proximity_force(const MovingObject &object) override;

    void update(float t) override;

    void draw() const override;

private:
    float last_t_;

    int n_neighbors_;
    Vec3f avg_position_;    // Cohesion
    Vec3f avg_speed_;       // Alignment
    Vec3f proximity_force_; // Separation + Target attraction
};

#endif // BOID_H
