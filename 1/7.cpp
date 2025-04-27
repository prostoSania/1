#include <iostream>
#include <stdexcept>


class Calculator {
public:
    
    virtual double calculate(double a, double b) const {
        return 0.0; 
    }

    
    virtual ~Calculator() {}
};


class Addition : public Calculator {
public:
    
    double calculate(double a, double b) const override {
        return a + b;
    }
};


class Division : public Calculator {
public:
    
    double calculate(double a, double b) const override {
        if (b == 0) {
            throw std::runtime_error("Деление на ноль недопустимо.");
        }
        return a / b;
    }
};

int main() {
    try {
        Addition addition;
        std::cout << "Сумма: " << addition.calculate(5.0, 3.0) << std::endl;

        Division division;
        std::cout << "Деление: " << division.calculate(10.0, 2.0) << std::endl;

        
        std::cout << "Деление на ноль: " << division.calculate(7.0, 0.0) << std::endl; 

    } catch (const std::runtime_error& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Общая ошибка: " << e.what() << std::endl;
    }

    return 0;
}