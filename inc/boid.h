/*********************************************************************************************************************
 * File : boid.h                                                                                                     *
 *                                                                                                                   *
 * 2020 Thomas Rouch                                                                                                 *
 *********************************************************************************************************************/

#ifndef BOID_H
#define BOID_H

#include <Eigen/Dense>

using Vec3f = Eigen::Vector3f;

class Boid
{
public:
    Boid(const Vec3f &position, const Vec3f &speed = Vec3f(0, 0, 0));

    inline const Vec3f &get_position() const { return position_; }
    inline const Vec3f &get_speed() const { return speed_; }
    inline int get_id() const { return id_; }
    void update(float dt);

    void draw() const;
private:
    static int next_id_;

    int id_;

    Vec3f position_;
    Vec3f speed_;
};

#endif // BOID_H