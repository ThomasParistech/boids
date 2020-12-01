/*********************************************************************************************************************
 * File : moving_object.cpp                                                                                          *
 *                                                                                                                   *
 * 2020 Thomas Rouch                                                                                                 *
 *********************************************************************************************************************/

#include "moving_object.h"

float MovingObject::neighborhood_max_dist_ = 10;

float MovingObject::separation_min_dist_ = 1;

float MovingObject::separation_factor_ = 0.02;
float MovingObject::cohesion_factor_ = 0.07;
float MovingObject::alignment_factor_ = 0.005;

float MovingObject::randomness_ = 0;
float MovingObject::max_speed_ = 10.f;

float MovingObject::min_cos_angle_ = -0.5f;

int MovingObject::next_id_ = 0;

bool MovingObject::are_neighbors(const MovingObject &left, const MovingObject &right)
{
    return (left.get_position() - right.get_position()).norm() < neighborhood_max_dist_;
}

MovingObject::MovingObject(const Vec3f &position, const Vec3f &speed) : id_(next_id_++),
                                                                        position_(position),
                                                                        speed_(speed),
                                                                        boid_type_(-1)
{
}
