#include <iostream>
#include <stdexcept>
#include <cmath> // Для M_PI и fmod
#include <string>

// Базовый класс Shape
class Shape {
public:
    // Виртуальная функция rotate()
    virtual void rotate(double angleDegrees) {
        // Приводим угол к диапазону 0-360 градусов
        double normalizedAngle = fmod(angleDegrees, 360.0);

        // Если угол отрицательный, добавляем 360, чтобы получить положительный эквивалент
        if (normalizedAngle < 0) {
            normalizedAngle += 360.0;
        }

        if (normalizedAngle != 0.0) {
             std::cout << "Поворот базовой фигуры на угол: " << normalizedAngle << " градусов." << std::endl;
        }
    }

    // Виртуальный деструктор
    virtual ~Shape() {}
};

// Производный класс Triangle
class Triangle : public Shape {
private:
    double angleA;
    double angleB;
    double angleC;

public:
    // Конструктор Triangle
    Triangle(double angleA, double angleB, double angleC) : angleA(angleA), angleB(angleB), angleC(angleC) {
        if (angleA <= 0 || angleB <= 0 || angleC <= 0) {
            throw std::invalid_argument("Все углы треугольника должны быть положительными.");
        }
        if (fabs(angleA + angleB + angleC - 180.0) > 1e-6) {
            // Проверяем, что сумма углов близка к 180 градусам (с учетом погрешности floating-point)
            throw std::invalid_argument("Сумма углов треугольника должна быть равна 180 градусам.");
        }
    }

    // Переопределение функции rotate()
    void rotate(double angleDegrees) override {
        // Приводим угол к диапазону 0-360 градусов
        double normalizedAngle = fmod(angleDegrees, 360.0);

        // Если угол отрицательный, добавляем 360, чтобы получить положительный эквивалент
        if (normalizedAngle < 0) {
            normalizedAngle += 360.0;
        }
        Shape::rotate(angleDegrees); //Вызываем базовую реализацию для логгирования поворота

        std::cout << "Поворот треугольника на угол: " << normalizedAngle << " градусов." << std::endl;
    }

    double getAngleA() const {
        return angleA;
    }

    double getAngleB() const {
        return angleB;
    }

    double getAngleC() const {
        return angleC;
    }
};

// Производный класс Rectangle
class Rectangle : public Shape {
private:
    double angle;

public:
    // Конструктор Rectangle
    Rectangle() : angle(0.0) {} // По умолчанию 0 градусов.  All angles in a rectangle are by definition, 90 degrees

    // Переопределение функции rotate()
    void rotate(double angleDegrees) override {
        // Приводим угол к диапазону 0-360 градусов
        double normalizedAngle = fmod(angleDegrees, 360.0);

        // Если угол отрицательный, добавляем 360, чтобы получить положительный эквивалент
        if (normalizedAngle < 0) {
            normalizedAngle += 360.0;
        }
        Shape::rotate(angleDegrees); //Вызываем базовую реализацию для логгирования поворота

        std::cout << "Поворот прямоугольника на угол: " << normalizedAngle << " градусов." << std::endl;
        angle = normalizedAngle; //Сохраняем угол
    }

    double getAngle() const {
        return angle;
    }
};

int main() {
    try {
        Triangle triangle(60.0, 60.0, 60.0);
        triangle.rotate(45.0);

        Rectangle rectangle;
        rectangle.rotate(-90.0);  // Поворот на -90 (эквивалентно 270)

        // Попытка создать треугольник с некорректными углами
        Triangle invalidTriangle(0.0, 90.0, 90.0); // Выбросит исключение

    } catch (const std::invalid_argument& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Общая ошибка: " << e.what() << std::endl;
    }

    return 0;
}