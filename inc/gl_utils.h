/*********************************************************************************************************************
 * File : gl_utils.h                                                                                                 *
 *                                                                                                                   *
 * 2020 Thomas Rouch                                                                                                 *
 *********************************************************************************************************************/

#ifndef GL_UTILS_H
#define GL_UTILS_H

#include <Eigen/Dense>
using Vec3f = Eigen::Vector3f;

namespace GlUtils
{
    /// @brief Aligns the X-axis with @p orientation
    /// @param orientation Desired target for the X-axis
    void align_view(const Vec3f &orientation);

    /// @brief Draws a cube centered around (0,0,0)
    /// @param scale Length of half of a square's side
    /// @param color Color of each face
    void draw_cube(float scale, const Vec3f &color = Vec3f(1, 1, 1));

    /// @brief Draws a box centered around (0,0,0)
    /// @param scale Length of half of a box's side along X, Y and Z axes
    /// @param color Color of each face
    void draw_box(const Vec3f &scale, const Vec3f &color = Vec3f(1, 1, 1));

    /// @brief Draws a plane normal to the X-axis and centered around (0,0,0)
    /// @param width Half of the plane's length along Y
    /// @param height Half of the plane's length along Z
    /// @param color Color of the plane
    void draw_yz_plane(float width, float height, const Vec3f &color = Vec3f(1, 1, 1));

    /// @brief Draws a pyramid oriented toward the X-axis, the base of which is centered around (0,0,0)
    /// @param scale XYZ scales
    /// @param color Color of the plane
    void draw_pyramid(const Vec3f &scale, const Vec3f &color = Vec3f(1, 1, 1));

} // namespace GlUtils

#endif // GL_UTILS_H
