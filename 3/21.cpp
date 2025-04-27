#include <iostream>
#include <stdexcept>
#include <string>

// Базовый класс Shape
class Shape {
protected:
    double x;
    double y;

public:
    // Конструктор Shape
    Shape(double x, double y) : x(x), y(y) {}

    // Виртуальная функция translate()
    virtual void translate(double dx, double dy) {
        double newX = x + dx;
        double newY = y + dy;

        if (!isValidCoordinates(newX, newY)) {
            throw std::runtime_error("Недопустимые координаты после перемещения.");
        }

        x = newX;
        y = newY;

        std::cout << "Перемещение базовой фигуры в координаты: (" << x << ", " << y << ")" << std::endl;
    }

    // Виртуальная функция для проверки допустимости координат (может быть переопределена)
    virtual bool isValidCoordinates(double x, double y) const {
        // Базовая реализация - координаты всегда допустимы
        return true;
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

    // Переопределение функции isValidCoordinates()
    bool isValidCoordinates(double x, double y) const override {
        // Для круга: координаты центра должны быть неотрицательными
        return (x >= 0 && y >= 0);
    }

    // Переопределение функции translate() - можно добавить специфическую логику
    void translate(double dx, double dy) override {
        Shape::translate(dx, dy); // Сначала вызываем базовый translate()
        std::cout << "Перемещение круга с радиусом " << radius << " в координаты: (" << getX() << ", " << getY() << ")" << std::endl;
    }

    double getRadius() const {
        return radius;
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

    // Переопределение функции isValidCoordinates()
    bool isValidCoordinates(double x, double y) const override {
        // Для прямоугольника: координаты верхнего левого угла должны быть неотрицательными
        return (x >= 0 && y >= 0);
    }

    // Переопределение функции translate() - можно добавить специфическую логику
    void translate(double dx, double dy) override {
        Shape::translate(dx, dy); // Сначала вызываем базовый translate()
        std::cout << "Перемещение прямоугольника шириной " << width << " и высотой " << height
                  << " в координаты: (" << getX() << ", " << getY() << ")" << std::endl;
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
        Circle circle(1.0, 2.0, 3.0);
        circle.translate(2.0, 1.0); // Перемещение в (3, 3)

        Rectangle rectangle(4.0, 5.0, 6.0, 7.0);
        rectangle.translate(-5.0, -6.0); // Выбросит исключение, координаты станут отрицательными

    } catch (const std::runtime_error& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Общая ошибка: " << e.what() << std::endl;
    }

    return 0;
}