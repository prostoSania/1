#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <vector>
#include <stdexcept>
#include <cmath>


struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
};


class Shape {
public:
    virtual ~Shape() = default;

    virtual std::vector<Point> getVertices() const = 0;

    virtual void validate() const = 0;

    virtual void printInfo() const = 0;
};


class Triangle : public Shape {
private:
    Point p1, p2, p3;


    bool isDegenerate() const {

        return std::abs((p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x)) < 1e-9;
    }

public:
    Triangle(const Point& p1, const Point& p2, const Point& p3)
        : p1(p1), p2(p2), p3(p3) {
        validate();
    }

    void validate() const override {
        if (isDegenerate()) {
            throw std::invalid_argument("Triangle is degenerate (points are colinear)");
        }
    }

    std::vector<Point> getVertices() const override {
        return { p1, p2, p3 };
    }

    void printInfo() const override {
        std::cout << "Triangle with vertices:\n";
        std::cout << "  (" << p1.x << ", " << p1.y << ")\n";
        std::cout << "  (" << p2.x << ", " << p2.y << ")\n";
        std::cout << "  (" << p3.x << ", " << p3.y << ")\n";
    }
};


class Square : public Shape {
private:
    Point center;
    double side;
    double rotation; 

public:
    Square(const Point& center, double side, double rotation = 0)
        : center(center), side(side), rotation(rotation) {
        validate();
    }

    void validate() const override {
        if (side <= 0) {
            throw std::invalid_argument("Square side must be positive");
        }
    }

    std::vector<Point> getVertices() const override {
        std::vector<Point> vertices;
        double half = side / 2.0;


        std::vector<Point> baseVertices = {
            {center.x - half, center.y - half},
            {center.x + half, center.y - half},
            {center.x + half, center.y + half},
            {center.x - half, center.y + half}
        };


        for (const auto& p : baseVertices) {
            double dx = p.x - center.x;
            double dy = p.y - center.y;


            double rotatedX = center.x + dx * cos(rotation) - dy * sin(rotation);
            double rotatedY = center.y + dx * sin(rotation) + dy * cos(rotation);

            vertices.emplace_back(rotatedX, rotatedY);
        }

        return vertices;
    }

    void printInfo() const override {
        std::cout << "Square with center at (" << center.x << ", " << center.y
            << "), side = " << side
            << ", rotation = " << rotation * 180.0 / M_PI << " degrees\n";
    }
};

class Pentagon : public Shape {
private:
    Point center;
    double radius;

public:
    Pentagon(const Point& center, double radius)
        : center(center), radius(radius) {
        validate();
    }

    void validate() const override {
        if (radius <= 0) {
            throw std::invalid_argument("Pentagon radius must be positive");
        }
    }

    std::vector<Point> getVertices() const override {
        std::vector<Point> vertices;

        for (int i = 0; i < 5; ++i) {
            double angle = 2.0 * M_PI * i / 5.0;
            double x = center.x + radius * cos(angle);
            double y = center.y + radius * sin(angle);
            vertices.emplace_back(x, y);
        }

        return vertices;
    }

    void printInfo() const override {
        std::cout << "Regular pentagon with center at (" << center.x << ", " << center.y
            << "), circumradius = " << radius << "\n";
    }
};

int main() {
    try {

        Triangle triangle({ 0, 0 }, { 1, 0 }, { 0.5, sqrt(3) / 2 });
        Square square({ 0, 0 }, 2.0, M_PI / 4); 
        Pentagon pentagon({ 0, 0 }, 1.0);

        triangle.printInfo();
        square.printInfo();
        pentagon.printInfo();

        auto printVertices = [](const Shape& shape) {
            std::cout << "Vertices:\n";
            for (const auto& p : shape.getVertices()) {
                std::cout << "  (" << p.x << ", " << p.y << ")\n";
            }
            };

        std::cout << "\nTriangle vertices:\n";
        printVertices(triangle);

        std::cout << "\nSquare vertices:\n";
        printVertices(square);

        std::cout << "\nPentagon vertices:\n";
        printVertices(pentagon);



    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}