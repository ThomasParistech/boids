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
    inline int get_type() const { return boid_type_; }

    void add_neighbor(const Boid &boid);

    Vec3f get_exerced_proximity_force(const Boid &boid);

    void update(float t);

    void draw() const;

    static float neighborhood_max_dist_;
    static float separation_min_dist_;
    static float separation_factor_;
    static float cohesion_factor_;
    static float alignment_factor_;
    static float target_attraction_factor_;
    static float randomness_;

    static bool are_neighbors(const Boid &left, const Boid &right);

private:
    static int next_id_;

    int id_;
    int boid_type_;

    float last_t_;

    int n_neighbors_;
    Vec3f avg_position_;    // Cohesion
    Vec3f avg_speed_;       // Alignment
    Vec3f proximity_force_; // Separation + Target attraction

    Vec3f position_;
    Vec3f speed_;
    float size_;
};

#endif // BOID_H
