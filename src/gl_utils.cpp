/*********************************************************************************************************************
 * File : gl_utils.cpp                                                                                               *
 *                                                                                                                   *
 * 2020 Thomas Rouch                                                                                                 *
 *********************************************************************************************************************/

#include <GL/glut.h>

#include "gl_utils.h"

namespace GlUtils
{
    void align_view(const Vec3f &orientation)
    {
        // Normal of the plane containing both the X-Axis and the boid speed
        const Vec3f axeRot = Vec3f::UnitX().cross(orientation);

        // |x^u| = |u|*|sin(Theta)|
        //  x.u  = |u|*cos(Theta)
        const float angle = 180 / 3.14 * std::atan2(axeRot.norm(), orientation.dot(Vec3f::UnitX()));
        glRotatef(angle, axeRot[0], axeRot[1], axeRot[2]);
    }

    void draw_cube(float scale, const Vec3f &color)
    {
        draw_box({scale, scale, scale}, color);
    }

    void draw_box(const Vec3f &scale, const Vec3f &color)
    {
        glColor3f(color[0], color[1], color[2]);
        glLineWidth(2.0);

        glBegin(GL_QUAD_STRIP);
        glNormal3f(0, 0, 1); // Face Z
        glVertex3f(-scale[0], -scale[1], scale[2]);
        glVertex3f(scale[0], -scale[1], scale[2]);
        glVertex3f(-scale[0], scale[1], scale[2]);
        glVertex3f(scale[0], scale[1], scale[2]);

        glNormal3f(0, 1, 0); // Face Y
        glVertex3f(-scale[0], scale[1], -scale[2]);
        glVertex3f(scale[0], scale[1], -scale[2]);

        glNormal3f(0, 0, -1); // Face -Z
        glVertex3f(-scale[0], -scale[1], -scale[2]);
        glVertex3f(scale[0], -scale[1], -scale[2]);

        glNormal3f(0, -1, 0); // Face -Y
        glVertex3f(-scale[0], -scale[1], scale[2]);
        glVertex3f(scale[0], -scale[1], scale[2]);
        glEnd();

        glBegin(GL_QUADS);
        glNormal3f(1, 0, 0); // Face X
        glVertex3f(scale[0], scale[1], scale[2]);
        glVertex3f(scale[0], -scale[1], scale[2]);
        glVertex3f(scale[0], -scale[1], -scale[2]);
        glVertex3f(scale[0], scale[1], -scale[2]);
        glEnd();

        glBegin(GL_QUADS);
        glNormal3f(-1, 0, 0); // Face -X
        glVertex3f(-scale[0], scale[1], scale[2]);
        glVertex3f(-scale[0], -scale[1], scale[2]);
        glVertex3f(-scale[0], -scale[1], -scale[2]);
        glVertex3f(-scale[0], scale[1], -scale[2]);
        glEnd();
    }

    void draw_yz_plane(float width, float height, const Vec3f &color)
    {
        glColor3f(color[0], color[1], color[2]);
        glBegin(GL_QUADS);
        glNormal3f(1, 0, 0);
        glVertex3f(0, -width, -height);
        glVertex3f(0, -width, height);
        glVertex3f(0, width, height);
        glVertex3f(0, width, -height);
        glEnd();
    }

    void draw_pyramid(const Vec3f &scale, const Vec3f &color)
    {
        glColor3f(color[0], color[1], color[2]);

        glBegin(GL_TRIANGLE_FAN);
        glVertex3f(scale[0], 0, 0); // Central Vertex

        glNormal3f(1, 1, 1);
        glVertex3f(0, 0, scale[2]);
        glVertex3f(0, scale[1], 0);

        glNormal3f(1, 1, -1);
        glVertex3f(0, 0, -scale[2]);

        glNormal3f(1, -1, -1);
        glVertex3f(0, -scale[1], 0);

        glNormal3f(1, -1, 1);
        glVertex3f(0, 0, scale[2]);
        glEnd();
    }

} // namespace GlUtils
