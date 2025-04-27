#include <iostream>
#include <string>
#include <stdexcept>

// Базовый класс Shape
class Shape {
protected:
    std::string color;

public:
    // Конструктор Shape
    Shape(const std::string& color) : color(color) {
        if (color.empty()) {
            throw std::invalid_argument("Цвет не может быть пустым.");
        }
    }

    // Виртуальная функция getColor()
    virtual std::string getColor() const {
        if (color.empty())
        {
            throw std::runtime_error("Метод getColor() не реализован для базового класса Shape.");
        }
        return color;
    }

    // Виртуальный деструктор
    virtual ~Shape() {}
};

// Производный класс Circle
class Circle : public Shape {
public:
    // Конструктор Circle
    Circle(const std::string& color) : Shape(color) {}

    // Переопределение функции getColor()
    std::string getColor() const override {
        return "Круг, цвет: " + color;
    }
};

// Производный класс Square
class Square : public Shape {
public:
    // Конструктор Square
    Square(const std::string& color) : Shape(color) {}

    // Переопределение функции getColor()
    std::string getColor() const override {
        return "Квадрат, цвет: " + color;
    }
};

int main() {
    try {
        Circle circle("Красный");
        std::cout << circle.getColor() << std::endl;

        Square square("Синий");
        std::cout << square.getColor() << std::endl;

        // Попытка создать фигуру без цвета
        //Shape shape(""); // Выбросит исключение

        //Попытка getColor для базового класса.
        Shape shape("Желтый");
        std::cout << shape.getColor() << std::endl;

    } catch (const std::runtime_error& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Общая ошибка: " << e.what() << std::endl;
    }

    return 0;
}