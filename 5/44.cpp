#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <cmath>


class Shape {
public:
    virtual ~Shape() = default;


    virtual void scale(double factor) = 0;


    virtual double area() const = 0;


    virtual void printInfo() const = 0;

protected:

    void checkScaleFactor(double factor) const {
        if (factor <= 0) {
            throw std::invalid_argument("Scale factor must be positive");
        }
    }
};

class Circle : public Shape {
private:
    double radius;

public:
    Circle(double r) : radius(r) {
        if (radius <= 0) {
            throw std::invalid_argument("Radius must be positive");
        }
    }

    void scale(double factor) override {
        checkScaleFactor(factor);
        radius *= factor;
    }

    double area() const override {
        return M_PI * radius * radius;
    }

    void printInfo() const override {
        std::cout << "Circle: radius = " << radius
            << ", area = " << area() << std::endl;
    }

    double getRadius() const { return radius; }
};


class Square : public Shape {
private:
    double side;

public:
    Square(double s) : side(s) {
        if (side <= 0) {
            throw std::invalid_argument("Side length must be positive");
        }
    }

    void scale(double factor) override {
        checkScaleFactor(factor);
        side *= factor;
    }

    double area() const override {
        return side * side;
    }

    void printInfo() const override {
        std::cout << "Square: side = " << side
            << ", area = " << area() << std::endl;
    }

    double getSide() const { return side; }
};


class Polygon : public Shape {
private:
    int sides;
    double sideLength;

public:
    Polygon(int n, double length) : sides(n), sideLength(length) {
        if (sides < 3) {
            throw std::invalid_argument("Polygon must have at least 3 sides");
        }
        if (sideLength <= 0) {
            throw std::invalid_argument("Side length must be positive");
        }
    }

    void scale(double factor) override {
        checkScaleFactor(factor);
        sideLength *= factor;
    }

    double area() const override {
        return (sides * sideLength * sideLength) /
            (4 * tan(M_PI / sides));
    }

    void printInfo() const override {
        std::cout << "Regular Polygon: sides = " << sides
            << ", side length = " << sideLength
            << ", area = " << area() << std::endl;
    }

    int getSides() const { return sides; }
    double getSideLength() const { return sideLength; }
};

int main() {
    try {

        Circle circle(5.0);
        Square square(4.0);
        Polygon pentagon(5, 3.0);


        circle.printInfo();
        square.printInfo();
        pentagon.printInfo();


        circle.scale(2.0);
        square.scale(1.5);
        pentagon.scale(0.5);

        std::cout << "\nAfter scaling:\n";
        circle.printInfo();
        square.printInfo();
        pentagon.printInfo();

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}