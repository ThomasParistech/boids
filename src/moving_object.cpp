/*********************************************************************************************************************
 * File : moving_object.cpp                                                                                          *
 *                                                                                                                   *
 * 2020 Thomas Rouch                                                                                                 *
 *********************************************************************************************************************/

#include "moving_object.h"

float MovingObject::neighborhood_max_dist_ = 10;

float MovingObject::separation_min_dist_ = 1;

float MovingObject::separation_factor_ = 0.1;
float MovingObject::cohesion_factor_ = 0.05;
float MovingObject::alignment_factor_ = 0.04;
float MovingObject::target_attraction_factor_ = 0.1;

float MovingObject::randomness_ = 0;

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
