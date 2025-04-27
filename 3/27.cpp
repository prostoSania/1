#include <iostream>
#include <string>
#include <stdexcept>

// Базовый класс Notification
class Notification {
protected:
    std::string message;

public:
    // Конструктор Notification
    Notification(const std::string& message) : message(message) {
        if (message.empty()) {
            throw std::invalid_argument("Текст сообщения не может быть пустым.");
        }
    }

    // Виртуальная функция send()
    virtual void send() const {
        std::cout << "Отправка базового уведомления: " << message << std::endl;
        // Базовая реализация - просто вывод сообщения (переопределяется в производных классах)
    }

    // Виртуальный деструктор
    virtual ~Notification() {}

    std::string getMessage() const {
        return message;
    }
};

// Производный класс EmailNotification
class EmailNotification : public Notification {
private:
    std::string recipient;
    std::string subject;

public:
    // Конструктор EmailNotification
    EmailNotification(const std::string& message, const std::string& recipient, const std::string& subject)
        : Notification(message), recipient(recipient), subject(subject) {
        if (recipient.empty()) {
            throw std::invalid_argument("Адрес электронной почты не может быть пустым.");
        }
        if (subject.empty()) {
            throw std::invalid_argument("Тема письма не может быть пустой.");
        }
    }

    // Переопределение функции send()
    void send() const override {
        Notification::send(); // Сначала вызываем базовый send()
        std::cout << "Отправка электронной почты на адрес: " << recipient << std::endl;
        std::cout << "Тема: " << subject << std::endl;
        // Имитация ошибки отправки (например, неверный адрес)
        if (recipient == "invalid_email") {
            throw std::runtime_error("Не удалось отправить электронное письмо на указанный адрес.");
        }
    }
};

// Производный класс SMSNotification
class SMSNotification : public Notification {
private:
    std::string phoneNumber;

public:
    // Конструктор SMSNotification
    SMSNotification(const std::string& message, const std::string& phoneNumber)
        : Notification(message), phoneNumber(phoneNumber) {
        if (phoneNumber.empty()) {
            throw std::invalid_argument("Номер телефона не может быть пустым.");
        }
    }

    // Переопределение функции send()
    void send() const override {
        Notification::send(); // Сначала вызываем базовый send()
        std::cout << "Отправка SMS на номер: " << phoneNumber << std::endl;
        // Имитация ошибки отправки (например, неверный номер)
        if (phoneNumber == "invalid_number") {
            throw std::runtime_error("Не удалось отправить SMS на указанный номер телефона.");
        }
    }
};

int main() {
    try {
        EmailNotification emailNotification("Привет!", "user@example.com", "Важное сообщение");
        emailNotification.send();

        SMSNotification smsNotification("Вам новое сообщение!", "+79991234567");
        smsNotification.send();

        // Попытка отправить письмо на неверный адрес
        EmailNotification invalidEmail("Ошибка!", "invalid_email", "Ошибка");
        invalidEmail.send();

        // Попытка отправить SMS на неверный номер
        SMSNotification invalidSMS("Ошибка!", "invalid_number");
        invalidSMS.send();

    } catch (const std::runtime_error& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Общая ошибка: " << e.what() << std::endl;
    }

    return 0;
}