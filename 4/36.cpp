#include <iostream>
#include <vector>
#include <stdexcept>

// Структура для представления вершины
struct Point {
    double x;
    double y;
};

// Базовый класс Shape
class Shape {
public:
    // Виртуальная функция getVertices()
    virtual std::vector<Point> getVertices() const {
        throw std::runtime_error("Метод getVertices() не реализован для базового класса Shape.");
    }

    // Виртуальный деструктор
    virtual ~Shape() {}
};

// Производный класс Triangle
class Triangle : public Shape {
private:
    Point a;
    Point b;
    Point c;

public:
    // Конструктор Triangle
    Triangle(Point a, Point b, Point c) : a(a), b(b), c(c) {
        // Проверка на вырожденный треугольник (все точки на одной прямой)
        double area = 0.5 * ((b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y));
        if (area == 0) {
            throw std::invalid_argument("Точки образуют вырожденный треугольник.");
        }
    }

    // Переопределение функции getVertices()
    std::vector<Point> getVertices() const override {
        return {a, b, c};
    }
};

// Производный класс Pentagon
class Pentagon : public Shape {
private:
    std::vector<Point> vertices;

public:
    // Конструктор Pentagon
    Pentagon(const std::vector<Point>& vertices) : vertices(vertices) {
        if (vertices.size() != 5) {
            throw std::invalid_argument("Пятиугольник должен иметь ровно 5 вершин.");
        }
    }

    // Переопределение функции getVertices()
    std::vector<Point> getVertices() const override {
        return vertices;
    }
};

int main() {
    try {
        Triangle triangle({{0.0, 0.0}, {1.0, 0.0}, {0.0, 1.0}});
        std::vector<Point> triangleVertices = triangle.getVertices();
        std::cout << "Вершины треугольника:" << std::endl;
        for (const auto& vertex : triangleVertices) {
            std::cout << "(" << vertex.x << ", " << vertex.y << ")" << std::endl;
        }

        Pentagon pentagon({{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.5, 1.5}, {0.0, 1.0}}});
        std::vector<Point> pentagonVertices = pentagon.getVertices();
        std::cout << "Вершины пятиугольника:" << std::endl;
        for (const auto& vertex : pentagonVertices) {
            std::cout << "(" << vertex.x << ", " << vertex.y << ")" << std::endl;
        }

        // Попытка создать вырожденный треугольник
        // Triangle invalidTriangle({{0.0, 0.0}, {1.0, 0.0}, {2.0, 0.0}}); // Выбросит исключение

    } catch (const std::runtime_error& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Общая ошибка: " << e.what() << std::endl;
    }

    return 0;
}