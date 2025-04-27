#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <sstream>

// Базовый класс FileReader
class FileReader {
protected:
    std::string filePath;

public:
    // Конструктор FileReader
    FileReader(const std::string& filePath) : filePath(filePath) {
        if (filePath.empty()) {
            throw std::invalid_argument("Путь к файлу не может быть пустым.");
        }
    }

    // Виртуальная функция read()
    virtual std::string read() const {
        throw std::runtime_error("Метод read() не реализован для базового класса FileReader.");
    }

    // Виртуальный деструктор
    virtual ~FileReader() {}

    std::string getFilePath() const {
        return filePath;
    }
};

// Производный класс TextFileReader
class TextFileReader : public FileReader {
public:
    // Конструктор TextFileReader
    TextFileReader(const std::string& filePath) : FileReader(filePath) {}

    // Переопределение функции read()
    std::string read() const override {
        std::ifstream file(filePath);
        if (!file.is_open()) {
            throw std::runtime_error("Не удалось открыть файл: " + filePath);
        }

        std::stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }
};

// Производный класс BinaryFileReader
class BinaryFileReader : public FileReader {
public:
    // Конструктор BinaryFileReader
    BinaryFileReader(const std::string& filePath) : FileReader(filePath) {}

    // Переопределение функции read()
    std::string read() const override {
        std::ifstream file(filePath, std::ios::binary);
        if (!file.is_open()) {
            throw std::runtime_error("Не удалось открыть бинарный файл: " + filePath);
        }

        std::stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }
};

int main() {
    // Create dummy files for testing
    std::ofstream textFile("example.txt");
    textFile << "This is a text file.";
    textFile.close();

    std::ofstream binaryFile("example.bin", std::ios::binary);
    binaryFile << "Binary Data";
    binaryFile.close();

    try {
        TextFileReader textReader("example.txt");
        std::cout << "Содержимое текстового файла: " << textReader.read() << std::endl;

        BinaryFileReader binaryReader("example.bin");
        std::cout << "Содержимое бинарного файла: " << binaryReader.read() << std::endl;

        // Попытка прочитать несуществующий файл
        TextFileReader invalidReader("nonexistent_file.txt");
        invalidReader.read(); // Выбросит исключение

    } catch (const std::runtime_error& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Общая ошибка: " << e.what() << std::endl;
    }

    return 0;
}