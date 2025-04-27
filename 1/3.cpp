#include <iostream>
#include <stdexcept>
#include <string>


class BankAccount {
protected:
    double balance;
    std::string accountNumber;

public:
    
    BankAccount(double initialBalance, const std::string& accountNumber) : balance(initialBalance), accountNumber(accountNumber) {}

    
    virtual void withdraw(double amount) {
        if (amount <= 0) {
            throw std::invalid_argument("Сумма снятия должна быть положительной.");
        }
        if (balance < amount) {
            throw std::runtime_error("Недостаточно средств на счете.");
        }
        balance -= amount;
        std::cout << "Снято " << amount << " со счета " << accountNumber << ". Остаток: " << balance << std::endl;
    }

    
    virtual ~BankAccount() {}

    double getBalance() const {
        return balance;
    }

    std::string getAccountNumber() const {
        return accountNumber;
    }
};


class SavingsAccount : public BankAccount {
private:
    double interestRate;

public:
    
    SavingsAccount(double initialBalance, const std::string& accountNumber, double interestRate)
        : BankAccount(initialBalance, accountNumber), interestRate(interestRate) {}

    
    void applyInterest() {
        balance += balance * interestRate;
        std::cout << "Начислены проценты на сберегательный счет " << accountNumber << ". Новый баланс: " << balance << std::endl;
    }
};


class CheckingAccount : public BankAccount {
private:
    double overdraftLimit;

public:
    
    CheckingAccount(double initialBalance, const std::string& accountNumber, double overdraftLimit)
        : BankAccount(initialBalance, accountNumber), overdraftLimit(overdraftLimit) {}

    
    void withdraw(double amount) override {
        if (amount <= 0) {
            throw std::invalid_argument("Сумма снятия должна быть положительной.");
        }
        if (balance + overdraftLimit < amount) {
            throw std::runtime_error("Превышен лимит овердрафта.");
        }
        balance -= amount;
        std::cout << "Снято " << amount << " со счета " << accountNumber << ". Остаток: " << balance << std::endl;
    }
};

int main() {
    try {
        SavingsAccount savings(1000.0, "SAV123", 0.05);
        savings.applyInterest();
        savings.withdraw(200.0);

        CheckingAccount checking(500.0, "CHK456", 200.0);
        checking.withdraw(600.0); 

        
        checking.withdraw(200.0); 

    } catch (const std::invalid_argument& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    } catch (const std::runtime_error& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Общая ошибка: " << e.what() << std::endl;
    }

    return 0;
}