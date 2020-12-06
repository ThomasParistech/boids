/*********************************************************************************************************************
 * File : obstacle.h                                                                                                 *
 *                                                                                                                   *
 * 2020 Thomas Rouch                                                                                                 *
 *********************************************************************************************************************/

#ifndef Obstacle_H
#define Obstacle_H

#include <functional>

#include "moving_object.h"

class Obstacle : public MovingObject
{
public:
    Obstacle(const Vec3f &position, float radius);

    virtual ~Obstacle() = default;

    Vec3f get_exerced_proximity_force(const MovingObject &object) const override;

    void update(float t) override;

    void draw() const override;

    static float obstacle_factor_;

private:
    float radius_;

    float rad_max_;
};

#endif // Obstacle_H
