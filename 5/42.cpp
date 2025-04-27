#include <iostream>
#include <stdexcept>
#include <string>

class Employee {
protected:
    std::string name;
    double hoursWorked;

public:
    Employee(const std::string& name, double hoursWorked)
        : name(name), hoursWorked(hoursWorked) {
        if (hoursWorked < 0) {
            throw std::invalid_argument("Hours worked cannot be negative");
        }
    }

    virtual double calculateSalary() const = 0;
    virtual ~Employee() = default;

    std::string getName() const { return name; }
    double getHoursWorked() const { return hoursWorked; }
};

class FullTimeEmployee : public Employee {
private:
    double monthlySalary;

public:
    FullTimeEmployee(const std::string& name, double hoursWorked, double monthlySalary)
        : Employee(name, hoursWorked), monthlySalary(monthlySalary) {
        if (monthlySalary < 0) {
            throw std::invalid_argument("Salary cannot be negative");
        }
    }

    double calculateSalary() const override {
        return monthlySalary; 
    }
};

class PartTimeEmployee : public Employee {
private:
    double hourlyRate;

public:
    PartTimeEmployee(const std::string& name, double hoursWorked, double hourlyRate)
        : Employee(name, hoursWorked), hourlyRate(hourlyRate) {
        if (hourlyRate < 0) {
            throw std::invalid_argument("Hourly rate cannot be negative");
        }
    }

    double calculateSalary() const override {
        return hoursWorked * hourlyRate;
    }
};

int main() {
    try {
        FullTimeEmployee fullTime("Ivan", 160, 50000);
        PartTimeEmployee partTime("Anna", 80, 500);   

        std::cout << "Full-time employee " << fullTime.getName()
            << " salary: " << fullTime.calculateSalary() << "\n";

        std::cout << "Part-time employee " << partTime.getName()
            << " salary: " << partTime.calculateSalary() << "\n";

    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    return 0;
}