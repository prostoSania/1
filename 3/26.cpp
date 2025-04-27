#include <iostream>
#include <string>
#include <stdexcept>

// Базовый класс Transaction
class Transaction {
protected:
    double amount;
    bool committed;

public:
    // Конструктор Transaction
    Transaction(double amount) : amount(amount), committed(false) {
        if (amount <= 0) {
            throw std::invalid_argument("Сумма транзакции должна быть положительной.");
        }
    }

    // Виртуальная функция commit()
    virtual void commit() {
        if (committed) {
            throw std::runtime_error("Транзакция уже выполнена.");
        }
        std::cout << "Выполнение базовой транзакции на сумму: " << amount << std::endl;
        committed = true;
    }

    // Виртуальный деструктор
    virtual ~Transaction() {}

    double getAmount() const {
        return amount;
    }

    bool isCommitted() const {
        return committed;
    }
};

// Производный класс BankTransaction
class BankTransaction : public Transaction {
private:
    std::string accountNumber;

public:
    // Конструктор BankTransaction
    BankTransaction(double amount, const std::string& accountNumber) : Transaction(amount), accountNumber(accountNumber) {
        if (accountNumber.empty()) {
            throw std::invalid_argument("Номер счета не может быть пустым.");
        }
    }

    // Переопределение функции commit()
    void commit() override {
        if (isCommitted()) {
            throw std::runtime_error("Транзакция уже выполнена.");
        }
        Transaction::commit(); // Сначала вызываем базовый commit()
        std::cout << "Выполнение банковской транзакции на счет: " << accountNumber << std::endl;

        // Имитация ошибки банковской транзакции (например, недостаточно средств)
        if (amount > 10000) {
            throw std::runtime_error("Недостаточно средств на счете для выполнения банковской транзакции.");
        }
    }
};

// Производный класс CryptoTransaction
class CryptoTransaction : public Transaction {
private:
    std::string walletAddress;

public:
    // Конструктор CryptoTransaction
    CryptoTransaction(double amount, const std::string& walletAddress) : Transaction(amount), walletAddress(walletAddress) {
        if (walletAddress.empty()) {
            throw std::invalid_argument("Адрес кошелька не может быть пустым.");
        }
    }

    // Переопределение функции commit()
    void commit() override {
        if (isCommitted()) {
            throw std::runtime_error("Транзакция уже выполнена.");
        }
        Transaction::commit(); // Сначала вызываем базовый commit()
        std::cout << "Выполнение крипто-транзакции на кошелек: " << walletAddress << std::endl;

        // Имитация ошибки крипто-транзакции (например, неверный адрес кошелька)
        if (walletAddress == "invalid_address") {
            throw std::runtime_error("Неверный адрес кошелька для крипто-транзакции.");
        }
    }
};

int main() {
    try {
        BankTransaction bankTransaction(5000.0, "1234567890");
        bankTransaction.commit();

        CryptoTransaction cryptoTransaction(100.0, "valid_wallet");
        cryptoTransaction.commit();

        // Попытка выполнить транзакцию на слишком большую сумму (для банковской транзакции)
        BankTransaction invalidBankTransaction(20000.0, "0987654321");
        invalidBankTransaction.commit();

        // Попытка выполнить транзакцию на неверный адрес кошелька (для крипто-транзакции)
        CryptoTransaction invalidCryptoTransaction(50.0, "invalid_address");
        invalidCryptoTransaction.commit();

        // Попытка повторного выполнения транзакции
        bankTransaction.commit(); // Выбросит исключение

    } catch (const std::runtime_error& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Общая ошибка: " << e.what() << std::endl;
    }

    return 0;
}