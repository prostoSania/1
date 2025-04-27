#include <iostream>
#include <stdexcept>
#include <string>
#include <ctime>
#include <iomanip>

class Transaction {
protected:
    std::string accountId;
    double amount;
    std::time_t timestamp;

    void validateAmount() const {
        if (amount <= 0) {
            throw std::invalid_argument("Amount must be positive");
        }
        if (std::isnan(amount)) {
            throw std::invalid_argument("Amount cannot be NaN");
        }
    }

    void validateAccount() const {
        if (accountId.empty()) {
            throw std::invalid_argument("Account ID cannot be empty");
        }
    }

public:
    Transaction(const std::string& account, double amt)
        : accountId(account), amount(amt), timestamp(std::time(nullptr)) {
        validateAccount();
        validateAmount();
    }

    virtual ~Transaction() = default;

    virtual void execute(double& balance) = 0;

    virtual std::string getType() const = 0;

    void printDetails() const {
        std::cout << "[" << std::put_time(std::localtime(&timestamp), "%F %T") << "] "
            << getType() << " on account " << accountId
            << " for amount " << amount << std::endl;
    }
};

class DepositTransaction : public Transaction {
public:
    DepositTransaction(const std::string& account, double amt)
        : Transaction(account, amt) {
    }

    void execute(double& balance) override {
        balance += amount;
        std::cout << "Deposit completed. New balance: " << balance << std::endl;
    }

    std::string getType() const override {
        return "DEPOSIT";
    }
};

class WithdrawalTransaction : public Transaction {
public:
    WithdrawalTransaction(const std::string& account, double amt)
        : Transaction(account, amt) {
    }

    void execute(double& balance) override {
        if (balance < amount) {
            throw std::runtime_error("Insufficient funds for withdrawal");
        }
        balance -= amount;
        std::cout << "Withdrawal completed. New balance: " << balance << std::endl;
    }

    std::string getType() const override {
        return "WITHDRAWAL";
    }
};

void processTransaction(Transaction& tx, double& balance) {
    try {
        tx.printDetails();
        tx.execute(balance);
    }
    catch (const std::exception& e) {
        std::cerr << "Transaction failed: " << e.what() << std::endl;
    }
}

int main() {
    double accountBalance = 1000.0;

    try {
        DepositTransaction deposit("ACC123456", 500.0);
        WithdrawalTransaction withdrawal("ACC123456", 200.0);


        processTransaction(deposit, accountBalance);
        processTransaction(withdrawal, accountBalance);


    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}