#include <iostream>
#include <stdexcept>
#include <string>
#include <fstream>

class ExceptionHandler {
public:
    virtual ~ExceptionHandler() = default;

    virtual void handle(const std::exception& e) = 0;

    virtual std::string getHandlerType() const = 0;
};

class FileExceptionHandler : public ExceptionHandler {
public:
    void handle(const std::exception& e) override {
        std::cerr << "File Error: " << e.what() << std::endl;

        std::ofstream logFile("file_errors.log", std::ios::app);
        if (logFile.is_open()) {
            logFile << "File Error: " << e.what() << std::endl;
        }

        throw std::runtime_error("File operation failed");
    }

    std::string getHandlerType() const override {
        return "File Exception Handler";
    }
};

class NetworkExceptionHandler : public ExceptionHandler {
public:
    void handle(const std::exception& e) override {
        std::cerr << "Network Error: " << e.what() << std::endl;


        throw std::runtime_error("Network operation failed");
    }

    std::string getHandlerType() const override {
        return "Network Exception Handler";
    }
};

class InputExceptionHandler : public ExceptionHandler {
public:
    void handle(const std::exception& e) override {
        std::cerr << "Input Error: " << e.what() << std::endl;


        throw std::runtime_error("Invalid input detected");
    }

    std::string getHandlerType() const override {
        return "Input Exception Handler";
    }
};

void processWithHandler(ExceptionHandler& handler, const std::function<void()>& operation) {
    try {
        operation();
    }
    catch (const std::exception& e) {
        try {
            handler.handle(e);
        }
        catch (const std::exception& handlerError) {
            std::cerr << "Handler failed: " << handlerError.what() << std::endl;
        }
    }
}

int main() {
    FileExceptionHandler fileHandler;
    NetworkExceptionHandler networkHandler;
    InputExceptionHandler inputHandler;


    try {

        processWithHandler(fileHandler, []() {
            throw std::runtime_error("File not found: data.txt");
            });
    }
    catch (...) {}

    try {

        processWithHandler(networkHandler, []() {
            throw std::runtime_error("Connection timeout");
            });
    }
    catch (...) {}

    try {

        processWithHandler(inputHandler, []() {
            throw std::invalid_argument("Invalid user input");
            });
    }
    catch (...) {}

    return 0;
}