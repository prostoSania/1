#include <iostream>
#include <stdexcept>
#include <string>
#include <cmath>

class Shape {
protected:
    virtual void validate() const = 0;

public:
    virtual ~Shape() = default;

    virtual std::string getDescription() const = 0;
};

class Circle : public Shape {
private:
    double radius;

    void validate() const override {
        if (radius <= 0) {
            throw std::invalid_argument("Radius must be positive");
        }
        if (std::isnan(radius)) {
            throw std::invalid_argument("Radius cannot be NaN");
        }
    }

public:
    Circle(double r) : radius(r) {
        validate();
    }

    std::string getDescription() const override {
        validate();
        return "Circle with radius " + std::to_string(radius);
    }
};

class Square : public Shape {
private:
    double side;

    void validate() const override {
        if (side <= 0) {
            throw std::invalid_argument("Side length must be positive");
        }
        if (std::isnan(side)) {
            throw std::invalid_argument("Side length cannot be NaN");
        }
    }

public:
    Square(double s) : side(s) {
        validate();
    }

    std::string getDescription() const override {
        validate();
        return "Square with side length " + std::to_string(side);
    }
};

class Triangle : public Shape {
private:
    double side1, side2, side3;

    bool isValidTriangle() const {
        return (side1 + side2 > side3) &&
            (side1 + side3 > side2) &&
            (side2 + side3 > side1);
    }

    void validate() const override {
        if (side1 <= 0 || side2 <= 0 || side3 <= 0) {
            throw std::invalid_argument("All sides must be positive");
        }
        if (std::isnan(side1) || std::isnan(side2) || std::isnan(side3)) {
            throw std::invalid_argument("Sides cannot be NaN");
        }
        if (!isValidTriangle()) {
            throw std::invalid_argument("Invalid triangle sides");
        }
    }

public:
    Triangle(double s1, double s2, double s3)
        : side1(s1), side2(s2), side3(s3) {
        validate();
    }

    std::string getDescription() const override {
        validate();
        return "Triangle with sides " + std::to_string(side1) + ", " +
            std::to_string(side2) + ", " + std::to_string(side3);
    }
};

void printDescription(const Shape& shape) {
    try {
        std::cout << shape.getDescription() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

int main() {
    try {
        Circle circle(5.0);
        Square square(4.0);
        Triangle triangle(3.0, 4.0, 5.0);

        printDescription(circle);
        printDescription(square);
        printDescription(triangle);

    }
    catch (const std::exception& e) {
        std::cerr << "Initialization error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}