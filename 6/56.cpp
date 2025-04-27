#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <cmath>

class Shape {
public:
    virtual ~Shape() = default;

    virtual double getPerimeter() const = 0;

    virtual void validate() const = 0;

 
    virtual void printInfo() const = 0;
};


class Circle : public Shape {
private:
    double radius;

public:
    Circle(double r) : radius(r) {
        validate();
    }

    void validate() const override {
        if (radius <= 0) {
            throw std::invalid_argument("Radius must be positive");
        }
        if (std::isnan(radius)) {
            throw std::invalid_argument("Radius cannot be NaN");
        }
    }

    double getPerimeter() const override {
        return 2 * M_PI * radius; 
    }

    void printInfo() const override {
        std::cout << "Circle: radius = " << radius
            << ", perimeter = " << getPerimeter() << std::endl;
    }
};


class Rectangle : public Shape {
private:
    double width, height;

public:
    Rectangle(double w, double h) : width(w), height(h) {
        validate();
    }

    void validate() const override {
        if (width <= 0 || height <= 0) {
            throw std::invalid_argument("Width and height must be positive");
        }
        if (std::isnan(width) || std::isnan(height)) {
            throw std::invalid_argument("Dimensions cannot be NaN");
        }
    }

    double getPerimeter() const override {
        return 2 * (width + height); 
    }

    void printInfo() const override {
        std::cout << "Rectangle: width = " << width
            << ", height = " << height
            << ", perimeter = " << getPerimeter() << std::endl;
    }
};


class Triangle : public Shape {
private:
    double side1, side2, side3;


    bool satisfiesTriangleInequality() const {
        return (side1 + side2 > side3) &&
            (side1 + side3 > side2) &&
            (side2 + side3 > side1);
    }

public:
    Triangle(double s1, double s2, double s3)
        : side1(s1), side2(s2), side3(s3) {
        validate();
    }

    void validate() const override {
        if (side1 <= 0 || side2 <= 0 || side3 <= 0) {
            throw std::invalid_argument("All sides must be positive");
        }
        if (std::isnan(side1) || std::isnan(side2) || std::isnan(side3)) {
            throw std::invalid_argument("Sides cannot be NaN");
        }
        if (!satisfiesTriangleInequality()) {
            throw std::invalid_argument("Triangle inequality violated");
        }
    }

    double getPerimeter() const override {
        return side1 + side2 + side3; 
    }

    void printInfo() const override {
        std::cout << "Triangle: sides = " << side1 << ", " << side2 << ", " << side3
            << ", perimeter = " << getPerimeter() << std::endl;
    }
};

void demonstrateShape(const Shape& shape) {
    try {
        shape.printInfo();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

int main() {
    try {

        Circle circle(5.0);
        Rectangle rectangle(4.0, 6.0);
        Triangle triangle(3.0, 4.0, 5.0);


        demonstrateShape(circle);
        demonstrateShape(rectangle);
        demonstrateShape(triangle);



    }
    catch (const std::exception& e) {
        std::cerr << "Initialization error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}