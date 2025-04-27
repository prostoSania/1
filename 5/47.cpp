
#include <iostream>
#include <stdexcept>
#include <vector>
#include <cmath>
#include <algorithm>

// Структура для представления ограничивающего прямоугольника
struct BoundingBox {
    double xMin, yMin, xMax, yMax;
    
    void print() const {
        std::cout << "BoundingBox: (" << xMin << ", " << yMin << ") to (" 
                  << xMax << ", " << yMax << ")" << std::endl;
    }
};

// Базовый абстрактный класс Shape
class Shape {
public:
    virtual ~Shape() = default;
    
    // Виртуальная функция получения ограничивающего прямоугольника
    virtual BoundingBox getBoundingBox() const = 0;
    
    // Виртуальная функция проверки корректности фигуры
    virtual void validate() const = 0;
    
    // Виртуальная функция вывода информации
    virtual void printInfo() const = 0;
};

// Класс Circle (окружность)
class Circle : public Shape {
private:
    double centerX, centerY, radius;
    
public:
    Circle(double x, double y, double r) 
        : centerX(x), centerY(y), radius(r) {
        validate();
    }
    
    void validate() const override {
        if (radius <= 0) {
            throw std::invalid_argument("Circle radius must be positive");
        }
        if (std::isnan(centerX)) {
            throw std::invalid_argument("Circle center X coordinate is invalid");
        }
    }
    
    BoundingBox getBoundingBox() const override {
        return {
            centerX - radius,
            centerY - radius,
            centerX + radius,
            centerY + radius
        };
    }
    
    void printInfo() const override {
        std::cout << "Circle: center=(" << centerX << ", " << centerY 
                  << "), radius=" << radius << std::endl;
    }
};

// Класс Rectangle (прямоугольник)
class Rectangle : public Shape {
private:
    double x1, y1, x2, y2;
    
public:
    Rectangle(double x1, double y1, double x2, double y2)
        : x1(x1), y1(y1), x2(x2), y2(y2) {
        validate();
    }
    
    void validate() const override {
        if (x1 == x2 || y1 == y2) {
            throw std::invalid_argument("Rectangle has zero width or height");
        }
        if (std::isnan(x1) || std::isnan(y1) || std::isnan(x2) || std::isnan(y2)) {
            throw std::invalid_argument("Rectangle coordinates are invalid");
        }
    }
    
    BoundingBox getBoundingBox() const override {
        return {
            std::min(x1, x2),
            std::min(y1, y2),
            std::max(x1, x2),
            std::max(y1, y2)
        };
    }
    
    void printInfo() const override {
        std::cout << "Rectangle: from (" << x1 << ", " << y1 
                  << ") to (" << x2 << ", " << y2 << ")" << std::endl;
    }
};

// Класс Polygon (многоугольник)
class Polygon : public Shape {
private:
    std::vector<std::pair<double, double>> vertices;
    
public:
    Polygon(const std::vector<std::pair<double, double>>& verts)
        : vertices(verts) {
        validate();
    }
    
    void validate() const override {
        if (vertices.size() < 3) {
            throw std::invalid_argument("Polygon must have at least 3 vertices");
        }
        
        for (const auto& [x, y] : vertices) {
            if (std::isnan(x) || std::isnan(y)) {
                throw std::invalid_argument("Polygon vertex coordinates are invalid");
            }
        }
    }
    
    BoundingBox getBoundingBox() const override {
        if (vertices.empty()) {
            throw std::runtime_error("Cannot compute bounding box for empty polygon");
        }
        
        BoundingBox bb = {
            vertices[0].first,
            vertices[0].second,
            vertices[0].first,
            vertices[0].second
        };
        
        for (const auto& [x, y] : vertices) {
            bb.xMin = std::min(bb.xMin, x);
            bb.yMin = std::min(bb.yMin, y);
            bb.xMax = std::max(bb.xMax, x);
            bb.yMax = std::max(bb.yMax, y);
        }
        
        return bb;
    }
    
    void printInfo() const override {
        std::cout << "Polygon with " << vertices.size() << " vertices:" << std::endl;
        for (const auto& [x, y] : vertices) {
            std::cout << "  (" << x << ", " << y << ")" << std::endl;
        }
    }
};

int main() {
    try {
        // Создаем фигуры
        Circle circle(5.0, 5.0, 3.0);
        Rectangle rect(1.0, 1.0, 4.0, 5.0);
        Polygon poly({{0.0, 0.0}, {2.0, 0.0}, {2.0, 2.0}, {1.0, 3.0}, {0.0, 2.0}});
        
        // Выводим информацию о фигурах
        circle.printInfo();
        circle.getBoundingBox().print();
        
        rect.printInfo();
        rect.getBoundingBox().print();
        
        poly.printInfo();
        poly.getBoundingBox().print();
        
        // Примеры с ошибками (можно раскомментировать для теста)
        // Circle invalidCircle(1.0, 1.0, -1.0); // Отрицательный радиус
        // Rectangle invalidRect(1.0, 1.0, 1.0, 1.0); // Нулевая площадь
        // Polygon invalidPoly({{0.0, 0.0}, {1.0, 1.0}}); // Всего 2 вершины
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}