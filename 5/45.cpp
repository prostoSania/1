
#include <iostream>
#include <stdexcept>
#include <string>

class BankAccount {
protected:
    std::string accountNumber;
    double balance;

public:
    BankAccount(const std::string& accNum, double initialBalance)
        : accountNumber(accNum), balance(initialBalance) {
        if (initialBalance < 0) {
            throw std::invalid_argument("Initial balance cannot be negative");
        }
    }

    virtual ~BankAccount() = default;

    virtual void transfer(double amount, BankAccount& recipient) {
        if (amount <= 0) {
            throw std::invalid_argument("Transfer amount must be positive");
        }
        if (balance < amount) {
            throw std::runtime_error("Insufficient funds for transfer");
        }

        withdraw(amount);
        recipient.deposit(amount);
    }

    virtual void withdraw(double amount) {
        if (amount <= 0) {
            throw std::invalid_argument("Withdrawal amount must be positive");
        }
        if (balance < amount) {
            throw std::runtime_error("Insufficient funds for withdrawal");
        }
        balance -= amount;
    }

    virtual void deposit(double amount) {
        if (amount <= 0) {
            throw std::invalid_argument("Deposit amount must be positive");
        }
        balance += amount;
    }

    double getBalance() const { return balance; }
    std::string getAccountNumber() const { return accountNumber; }

    virtual void displayInfo() const {
        std::cout << "Account: " << accountNumber
            << ", Balance: $" << balance << std::endl;
    }
};

class SavingsAccount : public BankAccount {
private:
    double interestRate;
    static constexpr double WITHDRAWAL_LIMIT = 1000.0;

public:
    SavingsAccount(const std::string& accNum, double initialBalance, double rate)
        : BankAccount(accNum, initialBalance), interestRate(rate) {
        if (rate < 0) {
            throw std::invalid_argument("Interest rate cannot be negative");
        }
    }

    void transfer(double amount, BankAccount& recipient) override {
        if (amount > WITHDRAWAL_LIMIT) {
            throw std::runtime_error("Savings account transfer exceeds limit of $"
                + std::to_string(WITHDRAWAL_LIMIT));
        }
        BankAccount::transfer(amount, recipient);
    }

    void applyInterest() {
        balance += balance * interestRate;
    }

    void displayInfo() const override {
        std::cout << "Savings ";
        BankAccount::displayInfo();
        std::cout << "Interest rate: " << (interestRate * 100) << "%" << std::endl;
    }
};

class CheckingAccount : public BankAccount {
private:
    static constexpr double TRANSACTION_FEE = 1.50;

public:
    CheckingAccount(const std::string& accNum, double initialBalance)
        : BankAccount(accNum, initialBalance) {
    }

    void transfer(double amount, BankAccount& recipient) override {
        if (balance < amount + TRANSACTION_FEE) {
            throw std::runtime_error("Insufficient funds for transfer + fee");
        }

        BankAccount::transfer(amount, recipient);
        balance -= TRANSACTION_FEE; 
    }

    void displayInfo() const override {
        std::cout << "Checking ";
        BankAccount::displayInfo();
        std::cout << "Transaction fee: $" << TRANSACTION_FEE << std::endl;
    }
};

int main() {
    try {

        SavingsAccount savings("SAV123", 5000.0, 0.03);
        CheckingAccount checking("CHK456", 3000.0);

        savings.displayInfo();
        checking.displayInfo();


        std::cout << "\nTransferring $500 from savings to checking:\n";
        savings.transfer(500.0, checking);

        savings.displayInfo();
        checking.displayInfo();

        savings.applyInterest();
        std::cout << "\nAfter applying interest to savings account:\n";
        savings.displayInfo();


    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}