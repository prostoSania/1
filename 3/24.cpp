#include <iostream>
#include <stdexcept>
#include <cmath> // For sqrt and pow

// Базовый класс Shape
class Shape {
public:
    // Виртуальная функция getPerimeter()
    virtual double getPerimeter() const {
        throw std::runtime_error("Метод getPerimeter() не реализован для базового класса Shape.");
    }

    // Виртуальный деструктор
    virtual ~Shape() {}
};

// Производный класс Triangle
class Triangle : public Shape {
private:
    double sideA;
    double sideB;
    double sideC;

public:
    // Конструктор Triangle
    Triangle(double sideA, double sideB, double sideC) : sideA(sideA), sideB(sideB), sideC(sideC) {
        if (sideA <= 0 || sideB <= 0 || sideC <= 0) {
            throw std::invalid_argument("Длины сторон треугольника должны быть положительными.");
        }
        if (sideA + sideB <= sideC || sideA + sideC <= sideB || sideB + sideC <= sideA) {
            throw std::invalid_argument("Недопустимые длины сторон треугольника: не выполняется неравенство треугольника.");
        }
    }

    // Переопределение функции getPerimeter()
    double getPerimeter() const override {
        return sideA + sideB + sideC;
    }
};

// Производный класс Square
class Square : public Shape {
private:
    double side;

public:
    // Конструктор Square
    Square(double side) : side(side) {
        if (side <= 0) {
            throw std::invalid_argument("Длина стороны квадрата должна быть положительной.");
        }
    }

    // Переопределение функции getPerimeter()
    double getPerimeter() const override {
        return 4 * side;
    }
};

int main() {
    try {
        Triangle triangle(3.0, 4.0, 5.0);
        std::cout << "Периметр треугольника: " << triangle.getPerimeter() << std::endl;

        Square square(2.5);
        std::cout << "Периметр квадрата: " << square.getPerimeter() << std::endl;

        // Попытка создать треугольник с некорректными сторонами
        Triangle invalidTriangle(1.0, 2.0, 5.0); // Выбросит исключение

        // Попытка вызвать getPerimeter() базового класса
        Shape shape;
        shape.getPerimeter(); // Выбросит исключение
    } catch (const std::runtime_error& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Общая ошибка: " << e.what() << std::endl;
    }

    return 0;
}