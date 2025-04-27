#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <ctime>

class Logger {
protected:

    std::string getCurrentTime() const {
        time_t now = time(nullptr);
        char buf[80];
        strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&now));
        return buf;
    }


    void validateMessage(const std::string& message) const {
        if (message.empty()) {
            throw std::invalid_argument("Log message cannot be empty");
        }
    }

public:
    virtual ~Logger() = default;


    virtual void log(const std::string& message) = 0;
};


class FileLogger : public Logger {
private:
    std::string filename;
    std::ofstream logFile;


    void checkFileState() const {
        if (!logFile.is_open()) {
            throw std::runtime_error("Log file is not open: " + filename);
        }
        if (logFile.fail()) {
            throw std::runtime_error("File operation failed: " + filename);
        }
    }

public:
    explicit FileLogger(const std::string& filename) : filename(filename) {
        logFile.open(filename, std::ios::app);
        if (!logFile.is_open()) {
            throw std::runtime_error("Failed to open log file: " + filename);
        }
    }

    ~FileLogger() override {
        if (logFile.is_open()) {
            logFile.close();
        }
    }

    void log(const std::string& message) override {
        validateMessage(message);
        checkFileState();

        logFile << "[" << getCurrentTime() << "] " << message << std::endl;
        checkFileState();
    }
};


class ConsoleLogger : public Logger {
public:
    void log(const std::string& message) override {
        validateMessage(message);

        std::cout << "[" << getCurrentTime() << "] " << message << std::endl;
        if (std::cout.fail()) {
            throw std::runtime_error("Console output failed");
        }
    }
};


void processWithLogging(Logger& logger) {
    try {
        logger.log("Application started");
        logger.log("Performing critical operation...");
        logger.log("Operation completed successfully");

    }
    catch (const std::exception& e) {
        std::cerr << "Logging error: " << e.what() << std::endl;
    }
}

int main() {
    try {
        FileLogger fileLogger("app.log");
        ConsoleLogger consoleLogger;

        std::cout << "Logging to file:" << std::endl;
        processWithLogging(fileLogger);

        std::cout << "\nLogging to console:" << std::endl;
        processWithLogging(consoleLogger);

    }
    catch (const std::exception& e) {
        std::cerr << "Initialization error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}