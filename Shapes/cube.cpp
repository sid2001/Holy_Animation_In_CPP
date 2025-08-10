#include "cube.h"
#include "plane.h"
#include <cmath>
#include <vector>

using namespace std;

void Cube::set_normals() {
    DirectionVector u = DirectionVector::X();
    if(normal.parallel_to(u)) {
        u = DirectionVector::Y();
    }
    DirectionVector d1 = u.cross(normal);
    out = d1;
    right = normal.cross(d1);
}

void Cube::render_faces(vector<Point>& points) {
    vector<Plane> faces;
    faces.push_back(Plane(half_length * 2, half_length * 2, Point::point_at_distance(center, normal, half_length), right, out));
    faces.push_back(Plane(half_length * 2, half_length * 2, Point::point_at_distance(center, normal * -1.0, half_length), right, out));
    faces.push_back(Plane(half_length * 2, half_length * 2, Point::point_at_distance(center, out, half_length), right, normal));
    faces.push_back(Plane(half_length * 2, half_length * 2, Point::point_at_distance(center, out * -1.0, half_length), right, normal));
    faces.push_back(Plane(half_length * 2, half_length * 2, Point::point_at_distance(center, right, half_length), out, normal));
    faces.push_back(Plane(half_length * 2, half_length * 2, Point::point_at_distance(center, right * -1.0, half_length), out, normal));

    for(Plane p : faces) {
        p.render(points);
    }
}

Cube::Cube(Point center) : center(center), normal(DirectionVector()), half_length(0), angular_position(0) {
    set_normals();
}

Cube::Cube(Point center, double half_length) : center(center), half_length(half_length), angular_position(0) {
    set_normals();
}

Cube::Cube(Point center, Dir normal, double half_length) : center(center), normal(normal), half_length(half_length), angular_position(0) {
    set_normals();
}

void Cube::rotate_around_up(double angle_rad) {
    double cosA = std::cos(angle_rad);
    double sinA = std::sin(angle_rad);

    Vector out = Vector(this->out.x, this->out.y, this->out.z);
    Vector right = Vector(this->right.x, this->right.y, this->right.z);
    Vector normal = Vector(this->normal.x, this->normal.y, this->normal.z);

    out = out * cosA + normal.cross(out) * sinA + normal * (normal.dot(out) * (1.0 - cosA));
    right = right * cosA + normal.cross(right) * sinA + normal * (normal.dot(right) * (1.0 - cosA));

    this->out = DirectionVector(out);
    this->right = DirectionVector(right);
}

void Cube::render(vector<Point>& points) {
    render_faces(points);
}
