#include <iostream>
#include <stdexcept>
#include <string>
#include <cmath>  


class Shape {
public:
    
    virtual void scale(double factor) {
        if (factor <= 0) {
            throw std::invalid_argument("Коэффициент масштабирования должен быть положительным.");
        }
        std::cout << "Масштабирование базовой фигуры на коэффициент: " << factor << std::endl;
    }

    
    virtual ~Shape() {}
};


class Circle : public Shape {
private:
    double radius;

public:
    
    Circle(double radius) : radius(radius) {
        if (radius <= 0) {
            throw std::invalid_argument("Радиус должен быть положительным.");
        }
    }

    
    void scale(double factor) override {
        if (factor <= 0) {
            throw std::invalid_argument("Коэффициент масштабирования должен быть положительным.");
        }
        radius *= factor;
        std::cout << "Масштабирование круга на коэффициент: " << factor << ". Новый радиус: " << radius << std::endl;
    }

    double getRadius() const {
        return radius;
    }

    double area() const {
        return M_PI * radius * radius;
    }
};


class Square : public Shape {
private:
    double side;

public:
    
    Square(double side) : side(side) {
        if (side <= 0) {
            throw std::invalid_argument("Длина стороны должна быть положительной.");
        }
    }

    
    void scale(double factor) override {
        if (factor <= 0) {
            throw std::invalid_argument("Коэффициент масштабирования должен быть положительным.");
        }
        side *= factor;
        std::cout << "Масштабирование квадрата на коэффициент: " << factor << ". Новая длина стороны: " << side << std::endl;
    }

    double getSide() const {
        return side;
    }

    double area() const {
        return side * side;
    }
};

int main() {
    try {
        Circle circle(5.0);
        std::cout << "Площадь круга: " << circle.area() << std::endl;
        circle.scale(2.0);
        std::cout << "Новая площадь круга: " << circle.area() << std::endl;

        Square square(3.0);
        std::cout << "Площадь квадрата: " << square.area() << std::endl;
        square.scale(0.5);
        std::cout << "Новая площадь квадрата: " << square.area() << std::endl;

        
        Square invalidSquare(4.0);
        invalidSquare.scale(-1.0); 

    } catch (const std::invalid_argument& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Общая ошибка: " << e.what() << std::endl;
    }

    return 0;
}