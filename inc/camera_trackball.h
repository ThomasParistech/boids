/*********************************************************************************************************************
 * File : camera_trackball.h                                                                                         *
 *                                                                                                                   *
 * 2020 Thomas Rouch                                                                                                 *
 *********************************************************************************************************************/

#ifndef CAMERA_TRACKBALL_H
#define CAMERA_TRACKBALL_H

#include <Eigen/Dense>

using Vec3f = Eigen::Vector3f;

/// @brief Implements a 3D trackball around the Z axis
class CameraTrackball
{
public:
    /// @brief Constructor
    CameraTrackball();

    /// @brief Init the camera to look at @p center at a distance @p r0
    void init(const Vec3f &center, float r0);

    /// @brief
    void lookAt();

    /// @brief Rotate the camera around the center
    void rotate(float right_input, float up_input);

    /// @brief Translate the camera in the tangent directions
    void pan(float right_input, float up_input, float front_input);

    /// @brief Zoom towards the camera center
    void zoom(int zoom_input);

    static const float DEFAULT_EULER_YAW;
    static const float DEFAULT_EULER_PITCH;

private:
    Vec3f eye_;
    Vec3f center_;

    Vec3f front_;
    Vec3f left_;
    Vec3f up_;

    float r_;
    float yaw_;
    float pitch_;
};

#endif // CAMERA_TRACKBALL_H
