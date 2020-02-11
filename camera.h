#pragma once

#include "ray.h"

Vec3 random_in_unit_sphere() {
    Vec3 p;
    do {
        p = 2.0*Vec3(drand48(),drand48(),drand48()) - Vec3(1,1,1);
    } while (p.sqr_length() >= 1.0);
    return p;
}

class Camera {
    public:
        Camera() {
            lower_left_corner = Vec3(-2.0, -1.0, -1.0);
            horizontal = Vec3(4.0, 0.0, 0.0);
            vertical = Vec3(0.0, 2.0, 0.0);
            origin = Vec3(0.0, 0.0, 0.0);
        }
        Ray get_ray(float u, float v) {
            return Ray(origin, lower_left_corner + u*horizontal + v*vertical - origin);
        }

        Vec3 origin;
        Vec3 lower_left_corner;
        Vec3 horizontal;
        Vec3 vertical;
};