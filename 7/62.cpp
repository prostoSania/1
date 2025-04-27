#include <iostream>
#include <stdexcept>
#include <string>
#include <map>

class Shape {
protected:
    std::string color;

    void validateColor() const {
        static const std::map<std::string, bool> validColors = {
            {"red", true}, {"green", true}, {"blue", true},
            {"yellow", true}, {"black", true}, {"white", true}
        };

        if (validColors.find(color) == validColors.end()) {
            throw std::invalid_argument("Invalid color: " + color);
        }
    }

public:
    Shape(const std::string& col) : color(col) {
        validateColor();
    }

    virtual ~Shape() = default;

    virtual std::string getColor() const {
        return color;
    }

    virtual void setColor(const std::string& newColor) {
        color = newColor;
        validateColor();
    }

    virtual std::string getType() const = 0;
};

class Circle : public Shape {
private:
    double radius;

public:
    Circle(const std::string& col, double r) : Shape(col), radius(r) {
        if (radius <= 0) {
            throw std::invalid_argument("Radius must be positive");
        }
    }

    std::string getType() const override {
        return "Circle";
    }
};

class Square : public Shape {
private:
    double side;

public:
    Square(const std::string& col, double s) : Shape(col), side(s) {
        if (side <= 0) {
            throw std::invalid_argument("Side must be positive");
        }
    }

    std::string getType() const override {
        return "Square";
    }
};

class Triangle : public Shape {
private:
    double base, height;

public:
    Triangle(const std::string& col, double b, double h) : Shape(col), base(b), height(h) {
        if (base <= 0 || height <= 0) {
            throw std::invalid_argument("Base and height must be positive");
        }
    }

    std::string getType() const override {
        return "Triangle";
    }
};

void printShapeInfo(const Shape& shape) {
    try {
        std::cout << shape.getType() << " color: " << shape.getColor() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

int main() {
    try {
        Circle circle("red", 5.0);
        Square square("green", 4.0);
        Triangle triangle("blue", 3.0, 6.0);

        printShapeInfo(circle);
        printShapeInfo(square);
        printShapeInfo(triangle);


    }
    catch (const std::exception& e) {
        std::cerr << "Initialization error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}