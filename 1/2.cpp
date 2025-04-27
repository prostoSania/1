#include <iostream>
#include <string>
#include <stdexcept>


class Animal {
public:
    
    virtual void speak() const {
        std::cout << "Animal makes a sound." << std::endl;
    }

    
    virtual ~Animal() {}
};


class Dog : public Animal {
private:
    std::string name;

public:
   
    Dog(const std::string& name) {
        if (name.empty()) {
            throw std::invalid_argument("Имя собаки не может быть пустым.");
        }
        this->name = name;
    }

    
    void speak() const override {
        std::cout << "Собака " << name << " говорит: Гав!" << std::endl;
    }

    std::string getName() const {
        return name;
    }
};


class Cat : public Animal {
private:
    std::string name;

public:
    
    Cat(const std::string& name) {
        if (name.empty()) {
            throw std::invalid_argument("Имя кошки не может быть пустым.");
        }
        this->name = name;
    }

    
    void speak() const override {
        std::cout << "Кошка " << name << " говорит: Мяу!" << std::endl;
    }

    std::string getName() const {
        return name;
    }
};

int main() {
    try {
        Dog dog("Бобик");
        dog.speak();

        Cat cat("Мурка");
        cat.speak();

        
        Dog invalidDog(""); 
        invalidDog.speak();  
    } catch (const std::invalid_argument& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Общая ошибка: " << e.what() << std::endl;
    }

    return 0;
}