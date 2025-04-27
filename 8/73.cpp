#include <iostream>
#include <stdexcept>
#include <vector>
#include <cmath>
#include <algorithm>

class Shape {
protected:
    virtual void validate() const = 0;

public:
    virtual ~Shape() = default;

    virtual bool getIntersection(const Shape& other) const = 0;

    virtual std::string getType() const = 0;
};

class Circle : public Shape {
private:
    double centerX, centerY;
    double radius;

    void validate() const override {
        if (radius <= 0) {
            throw std::invalid_argument("Radius must be positive");
        }
        if (std::isnan(centerX) || std::isnan(centerY)) {
            throw std::invalid_argument("Center coordinates cannot be NaN");
        }
    }

public:
    Circle(double x, double y, double r)
        : centerX(x), centerY(y), radius(r) {
        validate();
    }

    bool getIntersection(const Shape& other) const override;

    std::string getType() const override {
        return "Circle";
    }

    double getX() const { return centerX; }
    double getY() const { return centerY; }
    double getRadius() const { return radius; }
};

class Rectangle : public Shape {
private:
    double x, y;
    double width, height;

    void validate() const override {
        if (width <= 0 || height <= 0) {
            throw std::invalid_argument("Width and height must be positive");
        }
        if (std::isnan(x) || std::isnan(y)) {
            throw std::invalid_argument("Coordinates cannot be NaN");
        }
    }

public:
    Rectangle(double x, double y, double w, double h)
        : x(x), y(y), width(w), height(h) {
        validate();
    }

    bool getIntersection(const Shape& other) const override;

    std::string getType() const override {
        return "Rectangle";
    }

    double getX() const { return x; }
    double getY() const { return y; }
    double getWidth() const { return width; }
    double getHeight() const { return height; }
};

class Polygon : public Shape {
private:
    std::vector<std::pair<double, double>> vertices;

    void validate() const override {
        if (vertices.size() < 3) {
            throw std::invalid_argument("Polygon must have at least 3 vertices");
        }
        for (const auto& [x, y] : vertices) {
            if (std::isnan(x) || std::isnan(y)) {
                throw std::invalid_argument("Vertex coordinates cannot be NaN");
            }
        }
    }

public:
    Polygon(const std::vector<std::pair<double, double>>& verts)
        : vertices(verts) {
        validate();
    }

    bool getIntersection(const Shape& other) const override;

    std::string getType() const override {
        return "Polygon";
    }

    const std::vector<std::pair<double, double>>& getVertices() const {
        return vertices;
    }
};


bool Circle::getIntersection(const Shape& other) const {
    validate();
    other.validate();

    if (other.getType() == "Circle") {
        const Circle& otherCircle = dynamic_cast<const Circle&>(other);
        double dx = centerX - otherCircle.getX();
        double dy = centerY - otherCircle.getY();
        double distance = sqrt(dx * dx + dy * dy);
        return distance <= (radius + otherCircle.getRadius());
    }
    else if (other.getType() == "Rectangle") {
        const Rectangle& rect = dynamic_cast<const Rectangle&>(other);

        double closestX = std::max(rect.getX(), std::min(centerX, rect.getX() + rect.getWidth()));
        double closestY = std::max(rect.getY(), std::min(centerY, rect.getY() + rect.getHeight()));
        double dx = centerX - closestX;
        double dy = centerY - closestY;
        return (dx * dx + dy * dy) <= (radius * radius);
    }
    else if (other.getType() == "Polygon") {
        throw std::runtime_error("Circle-Polygon intersection not implemented");
    }
    else {
        throw std::invalid_argument("Unknown shape type");
    }
}


bool Rectangle::getIntersection(const Shape& other) const {
    validate();
    other.validate();

    if (other.getType() == "Rectangle") {
        const Rectangle& otherRect = dynamic_cast<const Rectangle&>(other);
        return !(x + width < otherRect.getX() ||
            otherRect.getX() + otherRect.getWidth() < x ||
            y + height < otherRect.getY() ||
            otherRect.getY() + otherRect.getHeight() < y);
    }
    else if (other.getType() == "Circle") {
        return other.getIntersection(*this); 
    }
    else if (other.getType() == "Polygon") {
        throw std::runtime_error("Rectangle-Polygon intersection not implemented");
    }
    else {
        throw std::invalid_argument("Unknown shape type");
    }
}

bool Polygon::getIntersection(const Shape& other) const {
    validate();
    other.validate();

    if (other.getType() == "Polygon") {
        throw std::runtime_error("Polygon-Polygon intersection not implemented");
    }
    else {
        return other.getIntersection(*this); 
    }
}

void testIntersection(const Shape& shape1, const Shape& shape2) {
    try {
        std::cout << "Testing intersection between "
            << shape1.getType() << " and "
            << shape2.getType() << ": ";
        bool intersects = shape1.getIntersection(shape2);
        std::cout << (intersects ? "YES" : "NO") << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

int main() {
    try {
        Circle circle(5, 5, 3);
        Rectangle rect(4, 4, 4, 4);
        Polygon poly({ {2,2}, {5,8}, {8,2} });

        testIntersection(circle, rect);
        testIntersection(circle, circle);
        testIntersection(rect, rect);


    }
    catch (const std::exception& e) {
        std::cerr << "Initialization error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}