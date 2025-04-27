#include <iostream>
#include <stdexcept>
#include <cmath> // For M_PI

// Базовый класс Shape
class Shape {
public:
    // Виртуальная функция getArea()
    virtual double getArea() const {
        throw std::runtime_error("Метод getArea() не реализован для базового класса Shape.");
    }

    // Виртуальный деструктор
    virtual ~Shape() {}
};

// Производный класс Ellipse
class Ellipse : public Shape {
private:
    double semiMajorAxis; // Большая полуось
    double semiMinorAxis; // Малая полуось

public:
    // Конструктор Ellipse
    Ellipse(double semiMajorAxis, double semiMinorAxis) : semiMajorAxis(semiMajorAxis), semiMinorAxis(semiMinorAxis) {
        if (semiMajorAxis <= 0 || semiMinorAxis <= 0) {
            throw std::invalid_argument("Длины полуосей должны быть положительными.");
        }
    }

    // Переопределение функции getArea()
    double getArea() const override {
        return M_PI * semiMajorAxis * semiMinorAxis;
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

    // Переопределение функции getArea()
    double getArea() const override {
        return side * side;
    }
};

int main() {
    try {
        Ellipse ellipse(5.0, 3.0);
        std::cout << "Площадь эллипса: " << ellipse.getArea() << std::endl;

        Square square(4.0);
        std::cout << "Площадь квадрата: " << square.getArea() << std::endl;

        // Попытка создать эллипс с некорректными полуосями
        Ellipse invalidEllipse(-2.0, 1.0); // Выбросит исключение

    } catch (const std::runtime_error& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Общая ошибка: " << e.what() << std::endl;
    }

    return 0;
}