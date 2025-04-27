
#include <iostream>
#include <stdexcept>
#include <cmath>

const double PI = 3.14159265358979323846;


class Shape {
public:
    virtual ~Shape() = default;


    virtual void rotate(double angleDegrees) {
        if (std::isnan(angleDegrees)) {
            throw std::invalid_argument("Rotation angle cannot be NaN");
        }
        if (std::isinf(angleDegrees)) {
            throw std::invalid_argument("Rotation angle cannot be infinite");
        }
    }


    virtual void printInfo() const = 0;
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


    void rotate(double angleDegrees) override {
        Shape::rotate(angleDegrees); // Проверка угла
        std::cout << "Circle rotated by " << angleDegrees
            << " degrees (no visible change)" << std::endl;
    }

    void printInfo() const override {
        std::cout << "Circle with radius " << radius << std::endl;
    }
};


class Square : public Shape {
private:
    double side;
    double rotationAngle = 0.0; 

public:
    Square(double s) : side(s) {
        if (side <= 0) {
            throw std::invalid_argument("Side length must be positive");
        }
    }

    void rotate(double angleDegrees) override {
        Shape::rotate(angleDegrees); 

        rotationAngle += angleDegrees;
        rotationAngle = fmod(rotationAngle, 360.0);

        std::cout << "Square rotated to " << rotationAngle
            << " degrees" << std::endl;
    }

    void printInfo() const override {
        std::cout << "Square with side " << side
            << ", current rotation: " << rotationAngle
            << " degrees" << std::endl;
    }
};


class Triangle : public Shape {
private:
    double side;
    double rotationAngle = 0.0; 

public:
    Triangle(double s) : side(s) {
        if (side <= 0) {
            throw std::invalid_argument("Side length must be positive");
        }
    }

    void rotate(double angleDegrees) override {
        Shape::rotate(angleDegrees); 

        if (fmod(angleDegrees, 120.0) != 0) {
            throw std::runtime_error("Triangle can only be rotated by multiples of 120 degrees");
        }

        rotationAngle += angleDegrees;
        rotationAngle = fmod(rotationAngle, 360.0);

        std::cout << "Triangle rotated to " << rotationAngle
            << " degrees" << std::endl;
    }

    void printInfo() const override {
        std::cout << "Equilateral triangle with side " << side
            << ", current rotation: " << rotationAngle
            << " degrees" << std::endl;
    }
};

int main() {
    try {

        Circle circle(5.0);
        Square square(4.0);
        Triangle triangle(3.0);


        circle.printInfo();
        square.printInfo();
        triangle.printInfo();


        std::cout << "\nRotating shapes:\n";
        circle.rotate(45.0);
        square.rotate(30.0);
        triangle.rotate(120.0);


        std::cout << "\nAfter rotation:\n";
        circle.printInfo();
        square.printInfo();
        triangle.printInfo();



    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}