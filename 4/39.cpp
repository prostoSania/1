#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

// Базовый класс Logger
class Logger {
public:
    // Виртуальная функция log()
    virtual void log(const std::string& message) const {
        throw std::runtime_error("Метод log() не реализован для базового класса Logger.");
    }

    // Виртуальный деструктор
    virtual ~Logger() {}
};

// Производный класс FileLogger
class FileLogger : public Logger {
private:
    std::string filePath;

public:
    // Конструктор FileLogger
    FileLogger(const std::string& filePath) : filePath(filePath) {
        if (filePath.empty()) {
            throw std::invalid_argument("Путь к файлу не может быть пустым.");
        }
    }

    // Переопределение функции log()
    void log(const std::string& message) const override {
        std::ofstream file(filePath, std::ios::app); // Открываем файл для добавления
        if (!file.is_open()) {
            throw std::runtime_error("Не удалось открыть файл для записи: " + filePath);
        }
        file << message << std::endl;
    }
};

// Производный класс ConsoleLogger
class ConsoleLogger : public Logger {
public:
    // Конструктор ConsoleLogger
    ConsoleLogger() {}

    // Переопределение функции log()
    void log(const std::string& message) const override {
        std::cout << message << std::endl;
    }
};

int main() {
    try {
        FileLogger fileLogger("app.log");
        fileLogger.log("Сообщение в файл.");

        ConsoleLogger consoleLogger;
        consoleLogger.log("Сообщение в консоль.");

        // Попытка создать FileLogger с неверным путем
        FileLogger invalidFileLogger(""); // Выбросит исключение

    } catch (const std::runtime_error& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Общая ошибка: " << e.what() << std::endl;
    }

    return 0;
}