#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <cmath>

class Shape {
public:
    virtual ~Shape() = default;

    virtual double getArea() const = 0;

    virtual void validate() const = 0;

    virtual std::string getType() const = 0;
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

    double getArea() const override {
        validate();
        return M_PI * radius * radius;
    }

    std::string getType() const override {
        return "Circle";
    }
};

class Rectangle : public Shape {
private:
    double width;
    double height;

    void validate() const override {
        if (width <= 0 || height <= 0) {
            throw std::invalid_argument("Width and height must be positive");
        }
        if (std::isnan(width) || std::isnan(height)) {
            throw std::invalid_argument("Dimensions cannot be NaN");
        }
    }

public:
    Rectangle(double w, double h) : width(w), height(h) {
        validate();
    }

    double getArea() const override {
        validate();
        return width * height;
    }

    std::string getType() const override {
        return "Rectangle";
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

    double getArea() const override {
        validate();
        double s = (side1 + side2 + side3) / 2;
        return sqrt(s * (s - side1) * (s - side2) * (s - side3));
    }

    std::string getType() const override {
        return "Triangle";
    }
};

void printArea(const Shape& shape) {
    try {
        std::cout << shape.getType() << " area: " << shape.getArea() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error calculating area: " << e.what() << std::endl;
    }
}

int main() {
    try {
        Circle circle(5.0);
        Rectangle rectangle(4.0, 6.0);
        Triangle triangle(3.0, 4.0, 5.0);

        printArea(circle);
        printArea(rectangle);
        printArea(triangle);



    }
    catch (const std::exception& e) {
        std::cerr << "Initialization error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}