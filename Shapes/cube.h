#ifndef CUBE_H
#define CUBE_H

#include "primitives.h"
#include "types.h"
#include <vector>

struct Cube {
    private:
    void set_normals();
    void render_faces(std::vector<Point>& points);

    public:
    Point center;
    double half_length, angular_position;
    Dir normal, out, right; //up

    Cube(Point center);
    Cube(Point center, double half_length);
    Cube(Point center, Dir normal, double half_length);

    void rotate_around_up(double angle_rad);
    void render(std::vector<Point>& points);
};

#endif // CUBE_H 