/* This is a purely procedural version of 'points.hpp'.
I wrote this because I couldn't get 'points.hpp' to work
properly in C, even when it was named 'points.h'. */
#ifndef MATH_H
#define MATH_H
#include <math.h>
#endif

/* rotate an x-coordinate about an arbitrary point */
float rotate_point_x(float cx,
                     float cy,
                     float theta,
                     float px,
                     float py) {
    float s = sin(theta);
    float c = cos(theta);
    px -= cx;
    py -= cy;

    float rotated_x = px * c - py * s;
    px = rotated_x + cx;
    return px;
}

/* rotate a y-coordinate about an arbitrary point */
float rotate_point_y(float cx,
                     float cy,
                     float theta,
                     float px,
                     float py) {
    float s = sin(theta);
    float c = cos(theta);
    px -= cx;
    py -= cy;

    float rotated_y = px * s + py * c;
    py = rotated_y + cy;
    return py;
}
