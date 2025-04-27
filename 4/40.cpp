#include <iostream>
#include <string>
#include <stdexcept>
#include <sstream>

// Базовый класс DataProcessor
class DataProcessor {
public:
    // Виртуальная функция processData()
    virtual std::string processData(const std::string& data) const {
        throw std::runtime_error("Метод processData() не реализован для базового класса DataProcessor.");
    }

    // Виртуальный деструктор
    virtual ~DataProcessor() {}
};

// Производный класс CSVProcessor
class CSVProcessor : public DataProcessor {
private:
    char delimiter;

public:
    // Конструктор CSVProcessor
    CSVProcessor(char delimiter = ',') : delimiter(delimiter) {}

    // Переопределение функции processData()
    std::string processData(const std::string& data) const override {
        std::stringstream ss(data);
        std::string token;
        std::string result;
        while (std::getline(ss, token, delimiter)) {
            result += "[" + token + "]";
        }

        if (result.empty()) {
            throw std::runtime_error("Не удалось обработать CSV данные. Возможно, неверный разделитель или пустые данные.");
        }

        return "CSV: " + result;
    }
};

// Производный класс JSONProcessor
class JSONProcessor : public DataProcessor {
public:
    // Конструктор JSONProcessor
    JSONProcessor() {}

    // Переопределение функции processData()
    std::string processData(const std::string& data) const override {
        if (data.empty()) {
            throw std::runtime_error("JSON данные не могут быть пустыми.");
        }

        // Очень упрощенная проверка на JSON (в реальном коде нужна полноценная валидация)
        if (data[0] != '{' || data[data.length() - 1] != '}') {
            throw std::runtime_error("Некорректный формат JSON (должен начинаться и заканчиваться фигурными скобками).");
        }

        return "JSON: " + data;
    }
};

int main() {
    try {
        CSVProcessor csvProcessor(';');
        std::cout << csvProcessor.processData("значение1;значение2;значение3") << std::endl;

        JSONProcessor jsonProcessor;
        std::cout << jsonProcessor.processData("{\"name\":\"John\", \"age\":30}") << std::endl;

        // Попытка обработать некорректные CSV данные
        CSVProcessor invalidCsvProcessor;
        invalidCsvProcessor.processData(""); // Выбросит исключение

        // Попытка обработать некорректные JSON данные
        JSONProcessor invalidJsonProcessor;
        invalidJsonProcessor.processData("not a json"); // Выбросит исключение

    } catch (const std::runtime_error& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Общая ошибка: " << e.what() << std::endl;
    }

    return 0;
}