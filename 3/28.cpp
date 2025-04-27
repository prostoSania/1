#include <iostream>
#include <stdexcept>
#include <vector>

// Структура для представления ограничивающего прямоугольника
struct BoundingBox {
    double minX;
    double minY;
    double maxX;
    double maxY;
};

// Базовый класс Shape
class Shape {
public:
    // Виртуальная функция getBoundingBox()
    virtual BoundingBox getBoundingBox() const {
        throw std::runtime_error("Метод getBoundingBox() не реализован для базового класса Shape.");
    }

    // Виртуальный деструктор
    virtual ~Shape() {}
};

// Производный класс Circle
class Circle : public Shape {
private:
    double x;      // Координата X центра
    double y;      // Координата Y центра
    double radius; // Радиус

public:
    // Конструктор Circle
    Circle(double x, double y, double radius) : x(x), y(y), radius(radius) {
        if (radius <= 0) {
            throw std::invalid_argument("Радиус должен быть положительным.");
        }
    }

    // Переопределение функции getBoundingBox()
    BoundingBox getBoundingBox() const override {
        BoundingBox bbox;
        bbox.minX = x - radius;
        bbox.minY = y - radius;
        bbox.maxX = x + radius;
        bbox.maxY = y + radius;
        return bbox;
    }
};

// Производный класс Polygon
class Polygon : public Shape {
private:
    std::vector<std::pair<double, double>> vertices; // Список вершин многоугольника

public:
    // Конструктор Polygon
    Polygon(const std::vector<std::pair<double, double>>& vertices) : vertices(vertices) {
        if (vertices.size() < 3) {
            throw std::invalid_argument("Многоугольник должен иметь не менее 3 вершин.");
        }
    }

    // Переопределение функции getBoundingBox()
    BoundingBox getBoundingBox() const override {
        if (vertices.empty()) {
            throw std::runtime_error("Невозможно вычислить ограничивающий прямоугольник для многоугольника без вершин.");
        }

        BoundingBox bbox;
        bbox.minX = vertices[0].first;
        bbox.minY = vertices[0].second;
        bbox.maxX = vertices[0].first;
        bbox.maxY = vertices[0].second;

        for (const auto& vertex : vertices) {
            if (vertex.first < bbox.minX) bbox.minX = vertex.first;
            if (vertex.second < bbox.minY) bbox.minY = vertex.second;
            if (vertex.first > bbox.maxX) bbox.maxX = vertex.first;
            if (vertex.second > bbox.maxY) bbox.maxY = vertex.second;
        }
        return bbox;
    }
};

int main() {
    try {
        Circle circle(1.0, 2.0, 3.0);
        BoundingBox circleBox = circle.getBoundingBox();
        std::cout << "Ограничивающий прямоугольник круга: (" << circleBox.minX << ", " << circleBox.minY << ") - ("
                  << circleBox.maxX << ", " << circleBox.maxY << ")" << std::endl;

        Polygon polygon({{0.0, 0.0}, {1.0, 0.0}, {0.0, 1.0}});
        BoundingBox polygonBox = polygon.getBoundingBox();
        std::cout << "Ограничивающий прямоугольник многоугольника: (" << polygonBox.minX << ", " << polygonBox.minY << ") - ("
                  << polygonBox.maxX << ", " << polygonBox.maxY << ")" << std::endl;

        // Попытка создать круг с некорректным радиусом
        Circle invalidCircle(0.0, 0.0, -1.0); // Выбросит исключение

        //Попытка получить BoundingBox базового класса
        Shape shape;
        shape.getBoundingBox();

    } catch (const std::runtime_error& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Общая ошибка: " << e.what() << std::endl;
    }

    return 0;
}