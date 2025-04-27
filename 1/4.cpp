#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>


class FileHandler {
protected:
    std::string filename;
    std::ifstream file;

public:
    
    FileHandler(const std::string& filename) : filename(filename) {}

    
    virtual void open() {
        file.open(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Файл не найден: " + filename);
        }
        std::cout << "Файл открыт: " << filename << std::endl;
    }

    
    virtual std::string readLine() {
        throw std::logic_error("Функция readLine не поддерживается для данного типа файла.");
    }

    
    virtual void readBytes(char* buffer, size_t size) {
       throw std::logic_error("Функция readBytes не поддерживается для данного типа файла.");
    }

    
    virtual ~FileHandler() {
        if (file.is_open()) {
            file.close();
            std::cout << "Файл закрыт: " << filename << std::endl;
        }
    }

    std::string getFilename() const {
        return filename;
    }

    bool isOpen() const {
        return file.is_open();
    }
};


class TextFileHandler : public FileHandler {
public:
    
    TextFileHandler(const std::string& filename) : FileHandler(filename) {}

    
    std::string readLine() override {
        std::string line;
        if (file.is_open()) {
            if (std::getline(file, line)) {
                return line;
            } else {
                return ""; 
            }
        } else {
            throw std::runtime_error("Файл не открыт: " + filename);
        }
    }
};


class BinaryFileHandler : public FileHandler {
public:
    
    BinaryFileHandler(const std::string& filename) : FileHandler(filename) {}

    
    void readBytes(char* buffer, size_t size) override {
        if (file.is_open()) {
            file.read(buffer, size);
            if (file.gcount() != size) {
                 throw std::runtime_error("Не удалось прочитать запрошенное количество байт из файла: " + filename);
            }
        } else {
            throw std::runtime_error("Файл не открыт: " + filename);
        }
    }
};

int main() {
    try {
        TextFileHandler textFile("example.txt"); 
        textFile.open();
        std::string line = textFile.readLine();
        std::cout << "Прочитанная строка: " << line << std::endl;

        BinaryFileHandler binaryFile("example.bin"); 
        binaryFile.open();
        char buffer[10];
        binaryFile.readBytes(buffer, 10);
        std::cout << "Прочитанные байты: ";
        for (int i = 0; i < 10; ++i) {
            std::cout << static_cast<int>(buffer[i]) << " ";
        }
        std::cout << std::endl;

        
        FileHandler invalidFile("nonexistent.txt");
        invalidFile.open(); 

    } catch (const std::runtime_error& e) {
        std::cerr << "Ошибка времени выполнения: " << e.what() << std::endl;
    } catch (const std::logic_error& e) {
        std::cerr << "Логическая ошибка: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Общая ошибка: " << e.what() << std::endl;
    }

    return 0;
}