#include <iostream>
#include <string>
#include <stdexcept>

// Базовый класс ExceptionHandler
class ExceptionHandler {
public:
    // Виртуальная функция handle()
    virtual void handle(const std::exception& e) const {
        std::cerr << "Общая обработка исключения: " << e.what() << std::endl;
        // Базовая реализация - просто вывод сообщения об ошибке в stderr
    }

    // Виртуальный деструктор
    virtual ~ExceptionHandler() {}
};

// Производный класс FileExceptionHandler
class FileExceptionHandler : public ExceptionHandler {
private:
    std::string filePath;

public:
    // Конструктор FileExceptionHandler
    FileExceptionHandler(const std::string& filePath) : filePath(filePath) {}

    // Переопределение функции handle()
    void handle(const std::exception& e) const override {
        std::cerr << "Ошибка файла (" << filePath << "): " << e.what() << std::endl;
        // Дополнительная логика, специфичная для ошибок файлов: запись в лог, уведомление администратора и т.п.

        // Здесь можно было бы записать информацию об ошибке в файл
        // std::ofstream logFile("file_error.log", std::ios::app);
        // logFile << "Ошибка файла (" << filePath << "): " << e.what() << std::endl;
        // logFile.close();
    }
};

// Производный класс NetworkExceptionHandler
class NetworkExceptionHandler : public ExceptionHandler {
private:
    std::string serverAddress;

public:
    // Конструктор NetworkExceptionHandler
    NetworkExceptionHandler(const std::string& serverAddress) : serverAddress(serverAddress) {}

    // Переопределение функции handle()
    void handle(const std::exception& e) const override {
        std::cerr << "Ошибка сети (" << serverAddress << "): " << e.what() << std::endl;
        // Дополнительная логика, специфичная для сетевых ошибок: попытка переподключения, fallback и т.п.

        // Здесь можно было бы попытаться переподключиться к серверу
        // try {
        //    reconnectToServer(serverAddress);
        // } catch (const std::exception& reconnectEx) {
        //    std::cerr << "Не удалось переподключиться к серверу: " << reconnectEx.what() << std::endl;
        // }
    }
};

// Функция, которая может выбрасывать исключения (для демонстрации)
void simulateFileError() {
    throw std::runtime_error("Ошибка при чтении файла: файл поврежден.");
}

// Функция, которая может выбрасывать исключения (для демонстрации)
void simulateNetworkError() {
    throw std::runtime_error("Не удалось подключиться к серверу.");
}

int main() {
    try {
        simulateFileError();
    } catch (const std::exception& e) {
        FileExceptionHandler fileHandler("data.txt");
        fileHandler.handle(e);
    }

    try {
        simulateNetworkError();
    } catch (const std::exception& e) {
        NetworkExceptionHandler networkHandler("192.168.1.100");
        networkHandler.handle(e);
    }

    return 0;
}