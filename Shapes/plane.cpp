#include "plane.h"
#include <vector>
using namespace std;

Plane::Plane(double l, double b, Point center, Dir right, Dir up) : length(l), breadth(b), center(center), right(right), up(up) {}

void Plane::render(vector<Point>& points) {
    Point right = Point(this->right.x, this->right.y, this->right.z);
    Point up = Point(this->up.x, this->up.y, this->up.z);
    for(int i = 0; i <= length; i++) {
        double t = (double)i / length - 0.5;
        for(int j = 0; j <= breadth; j++) {
			if(j == 0 || j == breadth || i == 0 || i == length){
				double s = (double)j / breadth - 0.5;
				Point p = center + right * (t* length) + up * (s * breadth);
				points.push_back(p);
			}
        }
    }
}