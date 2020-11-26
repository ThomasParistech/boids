/*********************************************************************************************************************
 * File : camera_trackball.cpp                                                                                       *
 *                                                                                                                   *
 * 2020 Thomas Rouch                                                                                                 *
 *********************************************************************************************************************/

#include "camera_trackball.h"

#include <GL/glut.h>
#include <Eigen/Dense>

const float CameraTrackball::DEFAULT_EULER_YAW = 1.0f;
const float CameraTrackball::DEFAULT_EULER_PITCH = 0.6f;

CameraTrackball::CameraTrackball()
    : eye_{0.0f, 0.0f, 0.0f},
      center_{0.0f, 0.0f, 0.0f},
      front_{0.0f, 0.0f, 1.0f},
      left_{0.0f, 0.0f, 1.0f},
      up_{0.0f, 0.0f, 1.0f},
      r_{1.0f},
      yaw_{3.14f},
      pitch_{1.0f}
{
}

void CameraTrackball::init(const Vec3f &center, float r0)
{
    center_ = center;
    r_ = r0;
    yaw_ = DEFAULT_EULER_YAW;
    pitch_ = DEFAULT_EULER_PITCH;
}

void CameraTrackball::lookAt()
{
    front_ = (-(cos(pitch_) * cos(yaw_) * Vec3f::UnitX() +
                cos(pitch_) * sin(yaw_) * Vec3f::UnitY() +
                sin(pitch_) * Vec3f::UnitZ()))
                 .normalized();

    left_ = (Vec3f::UnitZ().cross(front_)).normalized();
    up_ = (front_.cross(left_)).normalized();

    eye_ = center_ - r_ * front_;

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eye_[0], eye_[1], eye_[2],
              center_[0], center_[1], center_[2],
              0.0, 0.0, 1.0);
}

void CameraTrackball::rotate(float right_input, float up_input)
{
    static const float HALFPI_F = static_cast<float>(0.5 * M_PI);

    yaw_ += HALFPI_F * right_input;
    pitch_ += HALFPI_F * up_input;

    // Clamp pitch to ]-pi/2, pi/2[
    static const float PITCH_MIN = -HALFPI_F + 0.001f;
    static const float PITCH_MAX = HALFPI_F - 0.001f;
    pitch_ = std::min(std::max(pitch_, PITCH_MIN), PITCH_MAX);
}

void CameraTrackball::pan(float right_input, float up_input, float front_input)
{
    center_ +=
        -right_input * r_ * left_ +
        up_input * r_ * up_ +
        front_input * r_ * front_;
}

void CameraTrackball::zoom(int zoom_input)
{
    r_ *= std::pow(1.1f, zoom_input);
}
