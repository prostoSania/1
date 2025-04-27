#include <iostream>
#include <string>
#include <stdexcept>

// Базовый класс Task
class Task {
protected:
    bool initialized;

public:
    // Конструктор Task
    Task() : initialized(false) {}

    // Виртуальная функция execute()
    virtual void execute() const {
        if (!initialized) {
            throw std::runtime_error("Попытка выполнения неинициализированной задачи.");
        }
        std::cout << "Выполнение базовой задачи." << std::endl;
    }

    // Функция для инициализации задачи
    void initialize() {
        initialized = true;
    }

    // Виртуальный деструктор
    virtual ~Task() {}
};

// Производный класс PrintTask
class PrintTask : public Task {
private:
    std::string message;

public:
    // Конструктор PrintTask
    PrintTask(const std::string& message) : message(message) {}

    // Переопределение функции execute()
    void execute() const override {
        if (!initialized) {
            throw std::runtime_error("Попытка выполнения неинициализированной задачи печати.");
        }
        Task::execute(); // Сначала вызываем базовую execute()
        std::cout << "Печать сообщения: " << message << std::endl;
    }
};

// Производный класс EmailTask
class EmailTask : public Task {
private:
    std::string recipient;
    std::string subject;
    std::string body;

public:
    // Конструктор EmailTask
    EmailTask(const std::string& recipient, const std::string& subject, const std::string& body)
        : recipient(recipient), subject(subject), body(body) {}

    // Переопределение функции execute()
    void execute() const override {
        if (!initialized) {
            throw std::runtime_error("Попытка выполнения неинициализированной задачи отправки электронной почты.");
        }
        Task::execute(); // Сначала вызываем базовую execute()
        std::cout << "Отправка электронной почты на адрес: " << recipient << std::endl;
        std::cout << "Тема: " << subject << std::endl;
        std::cout << "Содержание: " << body << std::endl;
    }
};

int main() {
    try {
        PrintTask printTask("Hello, world!");
        // printTask.initialize(); // Закомментировали инициализацию - будет исключение
        printTask.execute(); // Выбросит исключение

        EmailTask emailTask("user@example.com", "Важное сообщение", "Это текст сообщения.");
        emailTask.initialize();
        emailTask.execute();

        // Попытка выполнить неинициализированную задачу
        Task task;
        task.execute(); // Выбросит исключение

    } catch (const std::runtime_error& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Общая ошибка: " << e.what() << std::endl;
    }

    return 0;
}