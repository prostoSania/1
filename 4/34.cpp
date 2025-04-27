#include <iostream>
#include <string>
#include <stdexcept>

// Базовый класс EmailService
class EmailService {
public:
    // Виртуальная функция sendEmail()
    virtual void sendEmail(const std::string& recipient, const std::string& subject, const std::string& body) const {
        throw std::runtime_error("Метод sendEmail() не реализован для базового класса EmailService.");
    }

    // Виртуальный деструктор
    virtual ~EmailService() {}
};

// Производный класс SMTPService
class SMTPService : public EmailService {
private:
    std::string smtpServer;
    int port;
    std::string senderEmail;
    std::string password;

public:
    // Конструктор SMTPService
    SMTPService(const std::string& smtpServer, int port, const std::string& senderEmail, const std::string& password)
        : smtpServer(smtpServer), port(port), senderEmail(senderEmail), password(password) {
        if (smtpServer.empty() || senderEmail.empty() || password.empty()) {
            throw std::invalid_argument("Необходимо указать SMTP сервер, адрес отправителя и пароль.");
        }
        if (port <= 0 || port > 65535) {
            throw std::invalid_argument("Недопустимый номер порта.");
        }
    }

    // Переопределение функции sendEmail()
    void sendEmail(const std::string& recipient, const std::string& subject, const std::string& body) const override {
        std::cout << "Отправка письма через SMTP сервер: " << smtpServer << ":" << port << std::endl;
        std::cout << "Отправитель: " << senderEmail << std::endl;
        std::cout << "Получатель: " << recipient << std::endl;
        std::cout << "Тема: " << subject << std::endl;
        std::cout << "Содержание: " << body << std::endl;

        // Имитация ошибки отправки (например, неверные учетные данные)
        if (senderEmail == "invalid@example.com" || password == "wrong_password") {
            throw std::runtime_error("Не удалось отправить письмо через SMTP: неверные учетные данные.");
        }
    }
};

// Производный класс APIService
class APIService : public EmailService {
private:
    std::string apiEndpoint;
    std::string apiKey;

public:
    // Конструктор APIService
    APIService(const std::string& apiEndpoint, const std::string& apiKey) : apiEndpoint(apiEndpoint), apiKey(apiKey) {
        if (apiEndpoint.empty() || apiKey.empty()) {
            throw std::invalid_argument("Необходимо указать URL API и ключ API.");
        }
    }

    // Переопределение функции sendEmail()
    void sendEmail(const std::string& recipient, const std::string& subject, const std::string& body) const override {
        std::cout << "Отправка письма через API: " << apiEndpoint << std::endl;
        std::cout << "Получатель: " << recipient << std::endl;
        std::cout << "Тема: " << subject << std::endl;
        std::cout << "Содержание: " << body << std::endl;

        // Имитация ошибки отправки (например, неверный ключ API)
        if (apiKey == "invalid_key") {
            throw std::runtime_error("Не удалось отправить письмо через API: неверный ключ API.");
        }
    }
};

int main() {
    try {
        SMTPService smtp("smtp.example.com", 587, "user@example.com", "password123");
        smtp.sendEmail("recipient@example.com", "Привет", "Это тестовое письмо.");

        APIService api("https://api.emailservice.com/send", "valid_api_key");
        api.sendEmail("another@example.com", "Важно", "Срочное сообщение.");

        // Попытка отправить письмо через SMTP с неверными учетными данными
        SMTPService invalidSMTP("smtp.example.com", 587, "invalid@example.com", "wrong_password");
        invalidSMTP.sendEmail("recipient@example.com", "Ошибка", "Не удалось отправить."); // Выбросит исключение

    } catch (const std::runtime_error& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Общая ошибка: " << e.what() << std::endl;
    }

    return 0;
}