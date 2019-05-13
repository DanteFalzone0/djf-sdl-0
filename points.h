#ifndef MATH_H
#define MATH_H
#include <math.h>
#endif

typedef struct Point {
    float x;
    float y;
} Point;

Point rotate_point(float cx, float cy, float theta, Point p) {
/* credit to Cameron for this bit
https://stackoverflow.com/a/2259502
*/
    float s = sin(theta);
    float c = cos(theta);
    p.x -= cx;
    p.y -= cy;

    float rotated_x = p.x * c - p.y * s;
    float rotated_y = p.x * s + p.y * c;
    p.x = rotated_x + cx;
    p.y = rotated_y + cy;
    return p;
}
