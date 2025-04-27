#include <iostream>
#include <string>
#include <stdexcept>


class Person {
protected:
    std::string name;
    int age;

public:
    
    Person(const std::string& name, int age) : name(name), age(age) {
        if (name.empty()) {
            throw std::invalid_argument("Имя не может быть пустым.");
        }
        if (age <= 0) {
            throw std::invalid_argument("Возраст должен быть положительным числом.");
        }
    }

    
    virtual void display() const {
        std::cout << "Имя: " << name << ", Возраст: " << age << std::endl;
    }

    
    virtual ~Person() {}

    std::string getName() const {
        return name;
    }

    int getAge() const {
        return age;
    }
};


class Student : public Person {
private:
    std::string studentId;

public:
    
    Student(const std::string& name, int age, const std::string& studentId)
        : Person(name, age), studentId(studentId) {
        if (studentId.empty()) {
            throw std::invalid_argument("ID студента не может быть пустым.");
        }
    }

    
    void display() const override {
        Person::display(); 
        std::cout << "ID студента: " << studentId << std::endl;
    }

    std::string getStudentId() const {
        return studentId;
    }
};


class Teacher : public Person {
private:
    std::string subject;

public:
    
    Teacher(const std::string& name, int age, const std::string& subject)
        : Person(name, age), subject(subject) {
        if (subject.empty()) {
            throw std::invalid_argument("Предмет преподавания не может быть пустым.");
        }
    }

    
    void display() const override {
        Person::display(); 
        std::cout << "Предмет преподавания: " << subject << std::endl;
    }

    std::string getSubject() const {
        return subject;
    }
};

int main() {
    try {
        Student student("Иван Иванов", 20, "12345");
        student.display();

        Teacher teacher("Мария Петрова", 35, "Математика");
        teacher.display();

        
        Student invalidStudent("", 19, "54321"); 
        invalidStudent.display(); 

    } catch (const std::invalid_argument& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Общая ошибка: " << e.what() << std::endl;
    }

    return 0;
}