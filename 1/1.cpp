#include <iostream>
#include <stdexcept> 
#include <cmath>     
#include <corecrt_math_defines.h>


class Shape {
public:
    
    virtual double area() const {
        return 0.0; 
    }

    
    virtual ~Shape() {}
};


class Circle : public Shape {
private:
    double radius;

public:
    
    Circle(double radius) {
        if (radius < 0) {
            throw std::invalid_argument("Радиус не может быть отрицательным.");
        }
        this->radius = radius;
    }

    
    double area() const override {
        return M_PI * radius * radius;
    }

    double getRadius() const {
        return radius;
    }
};


class Rectangle : public Shape {
private:
    double width;
    double height;

public:
    
    Rectangle(double width, double height) {
        if (width < 0 || height < 0) {
            throw std::invalid_argument("Ширина и высота не могут быть отрицательными.");
        }
        this->width = width;
        this->height = height;
    }

    
    double area() const override {
        return width * height;
    }

    double getWidth() const {
        return width;
    }

    double getHeight() const {
        return height;
    }
};

int main() {
    try {
        Circle circle(5.0);
        std::cout << "Площадь круга: " << circle.area() << std::endl;

        Rectangle rectangle(4.0, 6.0);
        std::cout << "Площадь прямоугольника: " << rectangle.area() << std::endl;

        
        Circle invalidCircle(-2.0);  
        std::cout << "Площадь invalidCircle: " << invalidCircle.area() << std::endl; 
    } catch (const std::invalid_argument& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Общая ошибка: " << e.what() << std::endl;
    }

    return 0;
}