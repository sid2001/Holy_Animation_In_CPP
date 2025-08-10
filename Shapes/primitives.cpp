#include <iostream>
#include <cmath>
#include <cassert>
#include "primitives.h"

// Vector implementations
Vector::Vector(const Tuple3<Vector>& t) : Tuple3(t) {}

void Vector::normalize() {
    double mag = this->magnitude();
    if(mag == 0) {
      std::cerr<<"Can't normalize because mag is zero"<<"\n";
      assert(mag != 0);
    }
    *this = (Vector)(*this / mag);
}

void Vector::normalize_or_zero() {
  double mag = this->magnitude();
    if(mag == 0) {
      this->x = 0;
      this->y = 0;
      this->z = 0;
      return;
    }
    *this = (Vector)(*this / mag);
}

double Vector::magnitude_squared() const {
    return x * x + y * y + z * z;
}

double Vector::magnitude() const {
    return std::sqrt(magnitude_squared());
}

double Vector::dot(Vector& a) {
    return x * a.x + y  * a.y + z * a.z;
}

Vector Vector::cross(Vector& a) {
    return Vector(y * a.z - z * a.y, z * a.x - x * a.z, x * a.y - y * a.x);
}

bool Vector::parallel_to(Vector& a) {
    return this->cross(a).magnitude_squared() == 0;
}

Vector Vector::rotate_around_axis(const Vector& vec, double angle_rad, const Vector& axis) {
    double len = axis.magnitude();
    double ux = axis.x / len;
    double uy = axis.y / len;
    double uz = axis.z / len;

    double cos_theta = std::cos(angle_rad);
    double sin_theta = std::sin(angle_rad);

    return {
        (cos_theta + ux*ux*(1 - cos_theta)) * vec.x +
        (ux*uy*(1 - cos_theta) - uz*sin_theta) * vec.y +
        (ux*uz*(1 - cos_theta) + uy*sin_theta) * vec.z,

        (uy*ux*(1 - cos_theta) + uz*sin_theta) * vec.x +
        (cos_theta + uy*uy*(1 - cos_theta)) * vec.y +
        (uy*uz*(1 - cos_theta) - ux*sin_theta) * vec.z,

        (uz*ux*(1 - cos_theta) - uy*sin_theta) * vec.x +
        (uz*uy*(1 - cos_theta) + ux*sin_theta) * vec.y +
        (cos_theta + uz*uz*(1 - cos_theta)) * vec.z
    };
}

// DirectionVector implementations
DirectionVector::DirectionVector() : Vector(0,1,0) {}

DirectionVector::DirectionVector(Vector& a) : Vector(a) {}

DirectionVector::DirectionVector(double x, double y, double z) : Vector(x,y,z) {
    if(std::fabs(this->magnitude_squared() - 1.0) > 1e-6) {
        std::cerr <<"Vector is not normalized,\nNormalizing vector...resultant may or may not be normalized.\n";
        this->normalize();
    }
}

DirectionVector DirectionVector::operator*(double a) {
    return DirectionVector(x * a, y * a, z * a);
}

DirectionVector DirectionVector::operator+(const DirectionVector& t) const {
    return DirectionVector(t.x + x, t.y + y, t.z + z);
}

DirectionVector DirectionVector::X() {
    return DirectionVector(1,0,0);
}

DirectionVector DirectionVector::Y() {
    return DirectionVector(0,1,0);
}

DirectionVector DirectionVector::Z() {
    return DirectionVector(0,0,1);
}

DirectionVector DirectionVector::cross(DirectionVector& a) {
    Vector* t1 = this;
    Vector* t2 = &a;
    Vector res = t1->cross(*t2);
    return DirectionVector(res.x, res.y, res.z);
}

DirectionVector DirectionVector::rotate_around_axis(double angle_rad, Vector axis) {
    Vector rotated_vector = Vector::rotate_around_axis(*this, angle_rad, axis);
    rotated_vector.normalize();
    return DirectionVector(rotated_vector.x, rotated_vector.y, rotated_vector.z);
}

// Point implementations
Point::Point(const Tuple3<Point>& t) : Tuple3(t) {}

Point::Point(const DirectionVector& t) : Tuple3(t.x,t.y,t.z) {}

void Point::translate_to(Point& p) {
    *this = p;
}

void Point::translate_by(Point& p) {
    *this = (Point)(*this + p);
}

Point Point::point_at_distance(Point& start, DirectionVector direction, double distance) {
    return Point(start + (Point)direction * distance);
}