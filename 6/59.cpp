#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <cmath>

using namespace std;

class Shape {
public:
    virtual ~Shape() = default;


    virtual void transform(double factorX, double factorY) = 0;


    virtual void validateTransformation(double factorX, double factorY) const {
        if (factorX <= 0 || factorY <= 0) {
            throw invalid_argument("Transformation factors must be positive");
        }
        if (isnan(factorX) || isnan(factorY)) {
            throw invalid_argument("Transformation factors cannot be NaN");
        }
        if (isinf(factorX) || isinf(factorY)) {
            throw invalid_argument("Transformation factors cannot be infinite");
        }
    }


    virtual void printInfo() const = 0;
};


class Circle : public Shape {
private:
    double centerX, centerY;
    double radius;

public:
    Circle(double x, double y, double r) : centerX(x), centerY(y), radius(r) {
        if (radius <= 0) {
            throw invalid_argument("Radius must be positive");
        }
    }

    void transform(double factorX, double factorY) override {
        validateTransformation(factorX, factorY);


        double avgFactor = (factorX + factorY) / 2.0;
        radius *= avgFactor;

        cout << "Circle scaled by average factor: " << avgFactor << endl;
    }

    void printInfo() const override {
        cout << "Circle: center=(" << centerX << ", " << centerY
            << "), radius=" << radius << endl;
    }
};


class Square : public Shape {
private:
    double centerX, centerY;
    double side;
    double rotationAngle; 

public:
    Square(double x, double y, double s, double angle = 0)
        : centerX(x), centerY(y), side(s), rotationAngle(angle) {
        if (side <= 0) {
            throw invalid_argument("Side length must be positive");
        }
    }

    void transform(double factorX, double factorY) override {
        validateTransformation(factorX, factorY);


        side *= (factorX + factorY) / 2.0;

        cout << "Square transformed with factors X: " << factorX
            << ", Y: " << factorY << endl;
    }

    void printInfo() const override {
        cout << "Square: center=(" << centerX << ", " << centerY
            << "), side=" << side
            << ", rotation=" << rotationAngle * 180.0 / M_PI << "°" << endl;
    }
};


class Polygon : public Shape {
private:
    vector<pair<double, double>> vertices;

public:
    Polygon(const vector<pair<double, double>>& verts) : vertices(verts) {
        if (vertices.size() < 3) {
            throw invalid_argument("Polygon must have at least 3 vertices");
        }
    }

    void transform(double factorX, double factorY) override {
        validateTransformation(factorX, factorY);


        for (auto& vertex : vertices) {
            vertex.first *= factorX;
            vertex.second *= factorY;
        }

        cout << "Polygon transformed with factors X: " << factorX
            << ", Y: " << factorY << endl;
    }

    void printInfo() const override {
        cout << "Polygon with " << vertices.size() << " vertices:" << endl;
        for (const auto& vertex : vertices) {
            cout << "  (" << vertex.first << ", " << vertex.second << ")" << endl;
        }
    }
};


void testTransformation(Shape& shape, double factorX, double factorY) {
    try {
        cout << "\nBefore transformation:" << endl;
        shape.printInfo();

        shape.transform(factorX, factorY);

        cout << "After transformation:" << endl;
        shape.printInfo();
    }
    catch (const exception& e) {
        cerr << "Transformation error: " << e.what() << endl;
    }
}

int main() {
    try {

        Circle circle(0, 0, 5.0);
        Square square(1, 1, 4.0, M_PI / 4);
        Polygon polygon({ {0,0}, {2,0}, {2,2}, {1,3}, {0,2} });


        testTransformation(circle, 1.5, 1.5); 
        testTransformation(square, 1.2, 0.8);  
        testTransformation(polygon, 1.1, 1.3); 



    }
    catch (const exception& e) {
        cerr << "Initialization error: " << e.what() << endl;
        return 1;
    }

    return 0;
}