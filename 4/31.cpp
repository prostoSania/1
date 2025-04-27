#include <iostream>
#include <stdexcept>
#include <cmath> // For fabs

// Базовый класс Shape
class Shape {
protected:
    double x; // Координата X центра
    double y; // Координата Y центра

public:
    // Конструктор Shape
    Shape(double x, double y) : x(x), y(y) {}

    // Виртуальная функция reflect()
    virtual void reflect(char axis) {
        if (axis != 'x' && axis != 'y') {
            throw std::invalid_argument("Недопустимая ось отражения. Допустимые значения: 'x' или 'y'.");
        }

        std::cout << "Отражение базовой фигуры относительно оси " << axis << std::endl;

        if (axis == 'x') {
            y = -y; // Отражение относительно оси X
        } else {
            x = -x; // Отражение относительно оси Y
        }
    }

    // Виртуальный деструктор
    virtual ~Shape() {}

    double getX() const {
        return x;
    }

    double getY() const {
        return y;
    }
};

// Производный класс Circle
class Circle : public Shape {
private:
    double radius;

public:
    // Конструктор Circle
    Circle(double x, double y, double radius) : Shape(x, y), radius(radius) {
        if (radius <= 0) {
            throw std::invalid_argument("Радиус должен быть положительным.");
        }
    }

    // Переопределение функции reflect()
    void reflect(char axis) override {
        Shape::reflect(axis); // Сначала вызываем базовый reflect()
        std::cout << "Отражение круга относительно оси " << axis << " в координатах (" << getX() << ", " << getY() << ")" << std::endl;
    }
};

// Производный класс Rectangle
class Rectangle : public Shape {
private:
    double width;
    double height;

public:
    // Конструктор Rectangle
    Rectangle(double x, double y, double width, double height) : Shape(x, y), width(width), height(height) {
        if (width <= 0 || height <= 0) {
            throw std::invalid_argument("Ширина и высота должны быть положительными.");
        }
    }

    // Переопределение функции reflect()
    void reflect(char axis) override {
        Shape::reflect(axis); // Сначала вызываем базовый reflect()
        std::cout << "Отражение прямоугольника относительно оси " << axis << " в координатах (" << getX() << ", " << getY() << ")" << std::endl;
    }
};

int main() {
    try {
        Circle circle(1.0, 2.0, 3.0);
        std::cout << "Исходные координаты круга: (" << circle.getX() << ", " << circle.getY() << ")" << std::endl;
        circle.reflect('x');
        std::cout << "Координаты круга после отражения относительно оси X: (" << circle.getX() << ", " << circle.getY() << ")" << std::endl;

        Rectangle rectangle(4.0, 5.0, 6.0, 7.0);
        std::cout << "Исходные координаты прямоугольника: (" << rectangle.getX() << ", " << rectangle.getY() << ")" << std::endl;
        rectangle.reflect('y');
        std::cout << "Координаты прямоугольника после отражения относительно оси Y: (" << rectangle.getX() << ", " << rectangle.getY() << ")" << std::endl;

        // Попытка отражения относительно недопустимой оси
        // circle.reflect('z'); // Выбросит исключение

        //Пример отражения на 0.
        circle.reflect('x'); //До x = 1; y = -(-2); y = 2;
        std::cout << "Координаты круга после отражения относительно оси X: (" << circle.getX() << ", " << circle.getY() << ")" << std::endl;

        circle.reflect('x'); //До x = 1; y = -(2); y = -2;
        std::cout << "Координаты круга после отражения относительно оси X: (" << circle.getX() << ", " << circle.getY() << ")" << std::endl;

    } catch (const std::invalid_argument& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Общая ошибка: " << e.what() << std::endl;
    }

    return 0;
}