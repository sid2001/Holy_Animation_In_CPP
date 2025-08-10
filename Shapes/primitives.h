#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include <iostream>
#include <cmath>
#include <cassert>

struct PointObject {
    virtual void translate_to(struct Point&) = 0;
    virtual void translate_by(struct Point&) = 0;
    virtual ~PointObject() = default;
};

template<typename T>
struct Tuple3 {
    double x, y, z;
    
    Tuple3(double x = 0, double y = 0, double z = 0): x(x), y(y), z(z) {}

    T operator+(const T& t) const {
        return T(x + t.x, y + t.y, z + t.z);
    }

    T operator/(const double a) const {
        return T(x / a, y / a, z / a);
    }

    T& operator=(const T& t) {
        x = t.x; y = t.y; z = t.z;
        return *this;
    }

    T operator*(double a) {
        return T(x * a, y * a, z * a);
    }

    T operator-() {
        return T(-x, -y, -z);
    }
    
    bool operator==(T& t) {
        return (x == t.x && y == t.y && z == t.z);
    }
};

struct Vector : Tuple3<Vector> {
    using Tuple3::Tuple3;
    Vector(const Tuple3<Vector>& t);
    void normalize();
    void normalize_or_zero();
    double magnitude_squared() const;
    double magnitude() const;
    double dot(Vector& a);
    Vector cross(Vector& a);
    bool parallel_to(Vector& a);
    static Vector rotate_around_axis(const Vector& vec, double angle_rad, const Vector& axis);
};

struct DirectionVector : Vector {
    DirectionVector();
    DirectionVector(Vector& a);
    DirectionVector(double x, double y, double z);
    DirectionVector operator*(double a);
    DirectionVector operator+(const DirectionVector& t) const;
    static DirectionVector X();
    static DirectionVector Y();
    static DirectionVector Z();
    DirectionVector cross(DirectionVector& a);
    DirectionVector rotate_around_axis(double angle_rad, Vector axis);
};

typedef DirectionVector Dir;

struct Point : PointObject, Tuple3<Point> {
    using Tuple3::Tuple3;
    Point(const Tuple3<Point>& t);
    Point(const DirectionVector& t);
    void translate_to(Point& p) override;
    void translate_by(Point& p) override;
    static Point point_at_distance(Point& start, DirectionVector direction, double distance);
};

#endif // PRIMITIVES_H