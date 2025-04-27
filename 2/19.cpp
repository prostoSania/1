#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

// Базовый класс Course
class Course {
protected:
    std::string courseName;
    int maxStudents;
    std::vector<std::string> enrolledStudents;

public:
    // Конструктор Course
    Course(const std::string& courseName, int maxStudents) : courseName(courseName), maxStudents(maxStudents) {
        if (courseName.empty()) {
            throw std::invalid_argument("Название курса не может быть пустым.");
        }
        if (maxStudents <= 0) {
            throw std::invalid_argument("Максимальное количество студентов должно быть положительным числом.");
        }
    }

    // Виртуальная функция enroll()
    virtual void enroll(const std::string& studentName) {
        if (enrolledStudents.size() >= maxStudents) {
            throw std::runtime_error("Группа переполнена. Невозможно зачислить студента " + studentName + " на курс " + courseName + ".");
        }

        enrolledStudents.push_back(studentName);
        std::cout << "Студент " << studentName << " успешно зачислен на курс " << courseName << "." << std::endl;
    }

    // Виртуальный деструктор
    virtual ~Course() {}

    std::string getCourseName() const {
        return courseName;
    }

    int getMaxStudents() const {
        return maxStudents;
    }

    int getEnrolledCount() const {
        return enrolledStudents.size();
    }
};

// Производный класс OnlineCourse
class OnlineCourse : public Course {
private:
    std::string platform; // Платформа, на которой проводится курс (например, Coursera, Udemy)

public:
    // Конструктор OnlineCourse
    OnlineCourse(const std::string& courseName, int maxStudents, const std::string& platform)
        : Course(courseName, maxStudents), platform(platform) {
        if (platform.empty()) {
            throw std::invalid_argument("Платформа для онлайн-курса не может быть пустой.");
        }
    }

    // Переопределение функции enroll() - можно добавить проверки, специфичные для онлайн-курсов
    void enroll(const std::string& studentName) override {
        Course::enroll(studentName); // Сначала вызываем базовый enroll()
        std::cout << "Студент " << studentName << " получил доступ к онлайн-материалам курса " << getCourseName()
                  << " на платформе " << platform << "." << std::endl;
    }

    std::string getPlatform() const {
        return platform;
    }
};

// Производный класс OfflineCourse
class OfflineCourse : public Course {
private:
    std::string classroom; // Номер аудитории

public:
    // Конструктор OfflineCourse
    OfflineCourse(const std::string& courseName, int maxStudents, const std::string& classroom)
        : Course(courseName, maxStudents), classroom(classroom) {
        if (classroom.empty()) {
            throw std::invalid_argument("Номер аудитории для оффлайн-курса не может быть пустым.");
        }
    }

    // Переопределение функции enroll() - можно добавить проверки, специфичные для оффлайн-курсов
    void enroll(const std::string& studentName) override {
        Course::enroll(studentName); // Сначала вызываем базовый enroll()
        std::cout << "Студенту " << studentName << " необходимо посещать занятия курса " << getCourseName()
                  << " в аудитории " << classroom << "." << std::endl;
    }

    std::string getClassroom() const {
        return classroom;
    }
};

int main() {
    try {
        OnlineCourse onlineCourse("Введение в программирование", 5, "Coursera");
        onlineCourse.enroll("Иванов Иван");
        onlineCourse.enroll("Петров Петр");
        onlineCourse.enroll("Сидоров Сидор");
        onlineCourse.enroll("Смирнов Алексей");
        onlineCourse.enroll("Кузнецов Дмитрий");

        // Попытка зачислить еще одного студента (группа переполнена)
        onlineCourse.enroll("Попов Сергей"); // Выбросит исключение

        OfflineCourse offlineCourse("Математический анализ", 3, "101");
        offlineCourse.enroll("Андреев Андрей");
        offlineCourse.enroll("Федоров Федор");
        offlineCourse.enroll("Николаев Николай");
        offlineCourse.enroll("Зайцев Павел");  // Выбросит исключение

    } catch (const std::runtime_error& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Общая ошибка: " << e.what() << std::endl;
    }

    return 0;
}