#include <iostream>
#include <stdexcept>
#include <string>


class Shape {
public:
    
    virtual void draw() const {
        std::cout << "Drawing a generic shape." << std::endl;
    }

    
    virtual ~Shape() {}
};


class Triangle : public Shape {
private:
    double base;
    double height;

public:
    
    Triangle(double base, double height) : base(base), height(height) {
        if (base <= 0 || height <= 0) {
            throw std::invalid_argument("Основание и высота треугольника должны быть положительными.");
        }
    }

    
    void draw() const override {
        std::cout << "Drawing a triangle with base " << base << " and height " << height << "." << std::endl;
        
    }

    double getBase() const {
        return base;
    }

    double getHeight() const {
        return height;
    }
};


class Square : public Shape {
private:
    double side;

public:
    
    Square(double side) : side(side) {
        if (side <= 0) {
            throw std::invalid_argument("Сторона квадрата должна быть положительной.");
        }
    }

    
    void draw() const override {
        std::cout << "Drawing a square with side " << side << "." << std::endl;
        
    }

    double getSide() const {
        return side;
    }
};

int main() {
    try {
        Triangle triangle(5.0, 4.0);
        triangle.draw();

        Square square(3.0);
        square.draw();

        
        Triangle invalidTriangle(-2.0, 1.0); 
        invalidTriangle.draw(); 

    } catch (const std::invalid_argument& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Общая ошибка: " << e.what() << std::endl;
    }

    return 0;
}