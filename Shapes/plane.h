#ifndef PLANE_H
#define PLANE_H

#include "Shapes/primitives.h"
#include "Shapes/types.h"
#include <vector>

struct Plane {
    double length, breadth;
    Point center;
    Dir right, up;

    Plane(double l, double b, Point center, Dir right, Dir up);
    void render(std::vector<Point>& points);
};

#endif // PLANE_H 