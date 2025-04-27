#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <cmath>

class Shape {
public:
    virtual double area() const = 0;
    virtual ~Shape() = default;
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

    double area() const override {
        return M_PI * radius * radius;
    }
};

class Rectangle : public Shape {
private:
    double width;
    double height;

public:
    Rectangle(double w, double h) : width(w), height(h) {
        if (width <= 0 || height <= 0) {
            throw std::invalid_argument("Width and height must be positive");
        }
    }

    double area() const override {
        return width * height;
    }
};

class Triangle : public Shape {
private:
    double a, b, c;

public:
    Triangle(double side1, double side2, double side3) : a(side1), b(side2), c(side3) {
        if (a <= 0 || b <= 0 || c <= 0) {
            throw std::invalid_argument("All sides must be positive");
        }
        if (a + b <= c || a + c <= b || b + c <= a) {
            throw std::invalid_argument("Triangle inequality violated");
        }
    }

    double area() const override {
        // Heron's formula
        double s = (a + b + c) / 2;
        return sqrt(s * (s - a) * (s - b) * (s - c));
    }
};

int main() {
    try {
        Circle circle(5.0);
        std::cout << "Circle area: " << circle.area() << std::endl;

        Rectangle rectangle(4.0, 6.0);
        std::cout << "Rectangle area: " << rectangle.area() << std::endl;

        Triangle triangle(3.0, 4.0, 5.0);
        std::cout << "Triangle area: " << triangle.area() << std::endl;

        // Пример с некорректными параметрами
        // Triangle invalid_triangle(1.0, 1.0, 3.0); // Выбросит исключение
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}