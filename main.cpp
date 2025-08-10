#include <thread>
#include <chrono>
#include <vector>
#include <iostream>
#include "Shapes/primitives.h"
#include "Shapes/types.h"
#include "Shapes/cube.h"


struct Vec2 {
    double x, y;
};

Vec2 projectPerspective(const Point& p, double focalLength) {
    return { focalLength * (p.x / p.z), focalLength * (p.y / p.z) };
}

int main()
{
	DirectionVector dir = DirectionVector(0,1,0);
    Cube cub(Point(2,0,4), dir, 2);
    double focalLength = 0.5;

    const int width = 100;
    const int height = 40;
    
    while(true) {
        std::vector<Point> points;
        
        
        std::vector<std::string> screen(height, std::string(width, ' '));
        cub.render(points);
        for (const auto& p : points) {
            if (p.z <= -20) continue;
            Vec2 proj = projectPerspective(p, focalLength);

            int col = static_cast<int>((proj.x + 1) * 0.5 * (width - 1));
            int row = static_cast<int>((-proj.y + 1) * 0.5 * (height - 1));

            if (row >= 0 && row < height && col >= 0 && col < width) {
                screen[row][col] = '*';
            }
        }
        
        for (const auto& line : screen) {
            std::cout << line << "\n";
        }
        std::cout.flush();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        std::cout << "\033[2J\033[H";
        std::cout.flush();
        cub.rotate_around_up(0.0001);
    }

    return 0;
}