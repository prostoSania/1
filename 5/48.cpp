
#include <iostream>
#include <string>
#include <exception>


class Exception : public std::exception {
protected:
    std::string message;

public:
    Exception(const std::string& msg) : message(msg) {}
    virtual ~Exception() = default;


    virtual const char* what() const noexcept override {
        return message.c_str();
    }
};


class FileNotFoundException : public Exception {
public:
    FileNotFoundException(const std::string& filename)
        : Exception("File not found: " + filename) {
    }
};


class InvalidInputException : public Exception {
public:
    InvalidInputException(const std::string& details)
        : Exception("Invalid input: " + details) {
    }
};


class NetworkException : public Exception {
public:
    NetworkException(const std::string& operation, const std::string& details)
        : Exception("Network error during " + operation + ": " + details) {
    }
};


void processOperation(int operationType) {
    try {
        if (operationType == 1) {
            throw FileNotFoundException("data.txt");
        }
        else if (operationType == 2) {
            throw InvalidInputException("negative value");
        }
        else if (operationType == 3) {
            throw NetworkException("data transfer", "connection timeout");
        }
        else {
            std::cout << "Operation completed successfully" << std::endl;
        }
    }
    catch (const Exception& e) {
        std::cerr << "Caught exception: " << e.what() << std::endl;
    }
}

int main() {
    std::cout << "Testing exception hierarchy:" << std::endl;


    processOperation(1); // FileNotFoundException
    processOperation(2); // InvalidInputException
    processOperation(3); // NetworkException
    processOperation(0); // Успешное выполнение

    return 0;
}