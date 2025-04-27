#include <iostream>
#include <stdexcept>
#include <string>


class Vehicle {
protected:
    std::string model;

public:
    
    Vehicle(const std::string& model) : model(model) {}

    
    virtual double fuelEfficiency(double distance, double fuelConsumed) const {
        if (distance <= 0 || fuelConsumed <= 0) {
            throw std::invalid_argument("Расстояние и расход топлива должны быть положительными числами.");
        }
        return (fuelConsumed / distance) * 100.0; 
    }

    
    virtual ~Vehicle() {}

    std::string getModel() const {
        return model;
    }
};


class Car : public Vehicle {
private:
    int numberOfDoors;

public:
    
    Car(const std::string& model, int numberOfDoors) : Vehicle(model), numberOfDoors(numberOfDoors) {
        if (numberOfDoors <= 0) {
            throw std::invalid_argument("Количество дверей должно быть положительным числом.");
        }
    }

    
    void displayCarInfo() const {
        std::cout << "Автомобиль: " << getModel() << ", Количество дверей: " << numberOfDoors << std::endl;
    }
};


class Truck : public Vehicle {
private:
    double cargoCapacity; 

public:
    
    Truck(const std::string& model, double cargoCapacity) : Vehicle(model), cargoCapacity(cargoCapacity) {
        if (cargoCapacity <= 0) {
            throw std::invalid_argument("Грузоподъемность должна быть положительным числом.");
        }
    }

    
    double fuelEfficiency(double distance, double fuelConsumed, double cargoWeight) const {
         if (distance <= 0 || fuelConsumed <= 0) {
            throw std::invalid_argument("Расстояние и расход топлива должны быть положительными числами.");
        }

         if(cargoWeight < 0) {
             throw std::invalid_argument("Вес груза должен быть неотрицательным.");
         }
        
        double baseEfficiency = Vehicle::fuelEfficiency(distance, fuelConsumed); 
        double weightFactor = 1 + (cargoWeight / cargoCapacity); 
        return baseEfficiency * weightFactor;
    }

    
    void displayTruckInfo() const {
        std::cout << "Грузовик: " << getModel() << ", Грузоподъемность: " << cargoCapacity << " тонн" << std::endl;
    }
};

int main() {
    try {
        Car car("Toyota Camry", 4);
        car.displayCarInfo();
        std::cout << "Расход топлива: " << car.fuelEfficiency(100, 8) << " л/100км" << std::endl;

        Truck truck("Volvo FH16", 40.0); 
        truck.displayTruckInfo();
        std::cout << "Расход топлива (без груза): " << truck.fuelEfficiency(100, 30, 0) << " л/100км" << std::endl;
        std::cout << "Расход топлива (с грузом 20 тонн): " << truck.fuelEfficiency(100, 30, 20) << " л/100км" << std::endl;

        
        Truck invalidTruck("InvalidTruck", 50.0);
        std::cout << "Расход топлива: " << invalidTruck.fuelEfficiency(0, 25, 10) << " л/100км" << std::endl; 

    } catch (const std::invalid_argument& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Общая ошибка: " << e.what() << std::endl;
    }

    return 0;
}