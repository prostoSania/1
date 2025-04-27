#include <iostream>
#include <stdexcept>
#include <string>
#include <ctime>
#include <cstdlib>

class PaymentGateway {
protected:
    std::string apiKey;
    double minAmount;
    double maxAmount;

    void validateAmount(double amount) const {
        if (amount < minAmount || amount > maxAmount) {
            throw std::invalid_argument("Amount must be between " +
                std::to_string(minAmount) +
                " and " +
                std::to_string(maxAmount));
        }
    }

    void validateApiKey() const {
        if (apiKey.empty()) {
            throw std::runtime_error("API key is not set");
        }
    }

public:
    PaymentGateway(const std::string& key, double min, double max)
        : apiKey(key), minAmount(min), maxAmount(max) {
    }

    virtual ~PaymentGateway() = default;

    virtual bool processPayment(double amount, const std::string& currency) = 0;

    virtual std::string getGatewayName() const = 0;
};

class StripeGateway : public PaymentGateway {
public:
    StripeGateway(const std::string& key)
        : PaymentGateway(key, 0.50, 10000.00) {
    }

    bool processPayment(double amount, const std::string& currency) override {
        validateApiKey();
        validateAmount(amount);

        if (currency != "USD" && currency != "EUR") {
            throw std::runtime_error("Stripe only supports USD and EUR");
        }

        std::cout << "Processing Stripe payment of " << amount << " " << currency << std::endl;

        // Simulate processing (10% chance of failure)
        if (rand() % 10 == 0) {
            throw std::runtime_error("Stripe payment processing failed");
        }

        return true;
    }

    std::string getGatewayName() const override {
        return "Stripe";
    }
};

class PayPalGateway : public PaymentGateway {
public:
    PayPalGateway(const std::string& key)
        : PaymentGateway(key, 1.00, 20000.00) {
    }

    bool processPayment(double amount, const std::string& currency) override {
        validateApiKey();
        validateAmount(amount);

        if (currency.length() != 3) {
            throw std::runtime_error("Invalid currency code");
        }

        std::cout << "Processing PayPal payment of " << amount << " " << currency << std::endl;

        // Simulate processing (15% chance of failure)
        if (rand() % 100 < 15) {
            throw std::runtime_error("PayPal payment processing failed");
        }

        return true;
    }

    std::string getGatewayName() const override {
        return "PayPal";
    }
};

class SquareGateway : public PaymentGateway {
public:
    SquareGateway(const std::string& key)
        : PaymentGateway(key, 0.10, 5000.00) {
    }

    bool processPayment(double amount, const std::string& currency) override {
        validateApiKey();
        validateAmount(amount);

        std::cout << "Processing Square payment of " << amount << " " << currency << std::endl;

        // Simulate processing (5% chance of failure)
        if (rand() % 100 < 5) {
            throw std::runtime_error("Square payment processing failed");
        }

        return true;
    }

    std::string getGatewayName() const override {
        return "Square";
    }
};

void processPaymentThroughGateway(PaymentGateway& gateway, double amount, const std::string& currency) {
    try {
        std::cout << "\nUsing " << gateway.getGatewayName() << " gateway..." << std::endl;
        bool success = gateway.processPayment(amount, currency);
        if (success) {
            std::cout << "Payment processed successfully!" << std::endl;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Payment error: " << e.what() << std::endl;
    }
}

int main() {
    srand(time(nullptr));

    try {
        StripeGateway stripe("sk_test_1234567890");
        PayPalGateway paypal("pp_test_1234567890");
        SquareGateway square("sq0_test_1234567890");

        processPaymentThroughGateway(stripe, 50.00, "USD");
        processPaymentThroughGateway(paypal, 75.50, "EUR");
        processPaymentThroughGateway(square, 10.25, "USD");


    }
    catch (const std::exception& e) {
        std::cerr << "Gateway initialization error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}