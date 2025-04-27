#include <iostream>
#include <string>
#include <stdexcept>

// Базовый класс Payment
class Payment {
protected:
    double amount; //Сумма платежа

public:
    // Конструктор Payment
    Payment(double amount) : amount(amount) {
        if (amount <= 0) {
            throw std::invalid_argument("Сумма платежа должна быть положительным числом.");
        }
    }

    // Виртуальная функция processPayment()
    virtual void processPayment() const {
        std::cout << "Выполнение платежа на сумму: " << amount << std::endl;
        // Базовая реализация - просто вывод сообщения (переопределяется в производных классах)
    }

    // Виртуальный деструктор
    virtual ~Payment() {}

    double getAmount() const {
        return amount;
    }
};

// Производный класс CreditCardPayment
class CreditCardPayment : public Payment {
private:
    std::string cardNumber;
    std::string expiryDate;
    double availableCredit;

public:
    // Конструктор CreditCardPayment
    CreditCardPayment(double amount, const std::string& cardNumber, const std::string& expiryDate, double availableCredit)
        : Payment(amount), cardNumber(cardNumber), expiryDate(expiryDate), availableCredit(availableCredit) {
        if (cardNumber.empty()) {
            throw std::invalid_argument("Номер кредитной карты не может быть пустым.");
        }
        if (expiryDate.empty()) {
            throw std::invalid_argument("Срок действия кредитной карты не может быть пустым.");
        }
        if (availableCredit < amount) {
            throw std::runtime_error("Недостаточно средств на кредитной карте.");
        }
    }

    // Переопределение функции processPayment()
    void processPayment() const override {
        Payment::processPayment(); // Сначала вызываем базовую обработку
        std::cout << "Выполнение платежа с кредитной карты " << cardNumber << ", срок действия: " << expiryDate << std::endl;
    }

    std::string getCardNumber() const {
        return cardNumber;
    }

    std::string getExpiryDate() const {
        return expiryDate;
    }
};

// Производный класс PayPalPayment
class PayPalPayment : public Payment {
private:
    std::string emailAddress;
    double availableBalance;

public:
    // Конструктор PayPalPayment
    PayPalPayment(double amount, const std::string& emailAddress, double availableBalance)
        : Payment(amount), emailAddress(emailAddress), availableBalance(availableBalance) {
        if (emailAddress.empty()) {
            throw std::invalid_argument("Адрес электронной почты PayPal не может быть пустым.");
        }
        if (availableBalance < amount) {
            throw std::runtime_error("Недостаточно средств на счете PayPal.");
        }
    }

    // Переопределение функции processPayment()
    void processPayment() const override {
        Payment::processPayment(); // Сначала вызываем базовую обработку
        std::cout << "Выполнение платежа через PayPal с адреса " << emailAddress << std::endl;
    }

    std::string getEmailAddress() const {
        return emailAddress;
    }
};

int main() {
    try {
        CreditCardPayment creditCardPayment(50.0, "1234-5678-9012-3456", "12/24", 100.0);
        creditCardPayment.processPayment();

        PayPalPayment payPalPayment(30.0, "user@example.com", 75.0);
        payPalPayment.processPayment();

        // Попытка платежа с недостаточным балансом
        CreditCardPayment invalidPayment(200.0, "1111-2222-3333-4444", "10/25", 50.0); // Выбросит исключение
        invalidPayment.processPayment(); // Не выполнится

    } catch (const std::runtime_error& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Общая ошибка: " << e.what() << std::endl;
    }

    return 0;
}