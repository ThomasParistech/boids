/*********************************************************************************************************************
 * File : target.h                                                                                                   *
 *                                                                                                                   *
 * 2020 Thomas Rouch                                                                                                 *
 *********************************************************************************************************************/

#ifndef TARGET_H
#define TARGET_H

#include <functional>

#include "moving_object.h"

class Target : public MovingObject
{
public:
    using UpdateSpeedFunc = std::function<void(float, Vec3f &)>;

    Target(
        const Vec3f &position,
        UpdateSpeedFunc update_speed_func = [](float, Vec3f &) {});

    virtual ~Target() = default;

    Vec3f get_exerced_proximity_force(const MovingObject &object) const override;

    void update(float t) override;

    void draw() const override;

    static float target_attraction_factor_;
    static float target_speed_alignment_factor_;

private:
    float last_t_;
    UpdateSpeedFunc update_speed_func_;
};

#endif // TARGET_H
