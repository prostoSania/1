#include <iostream>
#include <string>
#include <stdexcept>

// Базовый класс PaymentProcessor
class PaymentProcessor {
protected:
    double balance;

public:
    // Конструктор PaymentProcessor
    PaymentProcessor(double balance) : balance(balance) {
        if (balance < 0) {
            throw std::invalid_argument("Начальный баланс не может быть отрицательным.");
        }
    }

    // Виртуальная функция processPayment()
    virtual void processPayment(double amount) {
        if (amount <= 0) {
            throw std::invalid_argument("Сумма платежа должна быть положительной.");
        }
        if (balance < amount) {
            throw std::runtime_error("Недостаточно средств для выполнения платежа.");
        }
        std::cout << "Выполнение базового платежа на сумму: " << amount << std::endl;
        balance -= amount;
    }

    // Виртуальный деструктор
    virtual ~PaymentProcessor() {}

    double getBalance() const {
        return balance;
    }
};

// Производный класс CreditCardProcessor
class CreditCardProcessor : public PaymentProcessor {
private:
    std::string cardNumber;
    double creditLimit;

public:
    // Конструктор CreditCardProcessor
    CreditCardProcessor(double balance, const std::string& cardNumber, double creditLimit)
        : PaymentProcessor(balance), cardNumber(cardNumber), creditLimit(creditLimit) {
        if (cardNumber.empty()) {
            throw std::invalid_argument("Номер кредитной карты не может быть пустым.");
        }
        if (creditLimit < 0) {
            throw std::invalid_argument("Кредитный лимит не может быть отрицательным.");
        }
    }

    // Переопределение функции processPayment()
    void processPayment(double amount) override {
        if (amount <= 0) {
            throw std::invalid_argument("Сумма платежа должна быть положительной.");
        }
        if (getBalance() + creditLimit < amount) {
            throw std::runtime_error("Превышен кредитный лимит для выполнения платежа.");
        }
        PaymentProcessor::processPayment(amount); // Сначала вызываем базовый processPayment()
        std::cout << "Выполнение платежа с кредитной карты: " << cardNumber << std::endl;
    }
};

// Производный класс DebitCardProcessor
class DebitCardProcessor : public PaymentProcessor {
private:
    std::string accountNumber;

public:
    // Конструктор DebitCardProcessor
    DebitCardProcessor(double balance, const std::string& accountNumber)
        : PaymentProcessor(balance), accountNumber(accountNumber) {
        if (accountNumber.empty()) {
            throw std::invalid_argument("Номер счета не может быть пустым.");
        }
    }

    // Переопределение функции processPayment()
    void processPayment(double amount) override {
        PaymentProcessor::processPayment(amount); // Сначала вызываем базовый processPayment()
        std::cout << "Выполнение платежа с дебетовой карты: " << accountNumber << std::endl;
    }
};

int main() {
    try {
        CreditCardProcessor creditCard(1000.0, "1234-5678-9012-3456", 500.0);
        creditCard.processPayment(750.0);
        std::cout << "Текущий баланс (кредитная карта): " << creditCard.getBalance() << std::endl;

        DebitCardProcessor debitCard(500.0, "9876543210");
        debitCard.processPayment(200.0);
        std::cout << "Текущий баланс (дебетовая карта): " << debitCard.getBalance() << std::endl;

        // Попытка выполнить платеж, превышающий кредитный лимит
        creditCard.processPayment(1600.0); // Выбросит исключение

    } catch (const std::runtime_error& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Общая ошибка: " << e.what() << std::endl;
    }

    return 0;
}