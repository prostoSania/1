#include <iostream>
#include <stdexcept>
#include <string>
#include <regex>

class DataValidator {
public:
    virtual ~DataValidator() = default;

    virtual void validate(const std::string& data) const = 0;

    virtual std::string getValidatorType() const = 0;
};

class EmailValidator : public DataValidator {
private:
    const std::regex emailRegex{
        R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)"
    };

public:
    void validate(const std::string& email) const override {
        if (email.empty()) {
            throw std::invalid_argument("Email cannot be empty");
        }

        if (!std::regex_match(email, emailRegex)) {
            throw std::invalid_argument("Invalid email format: " + email);
        }
    }

    std::string getValidatorType() const override {
        return "Email Validator";
    }
};

class PhoneValidator : public DataValidator {
private:
    const std::regex phoneRegex{
        R"(^\+?(\d[\d-. ]+)?(\([\d-. ]+\))?[\d-. ]+\d$)"
    };

public:
    void validate(const std::string& phone) const override {
        if (phone.empty()) {
            throw std::invalid_argument("Phone number cannot be empty");
        }

        if (!std::regex_match(phone, phoneRegex)) {
            throw std::invalid_argument("Invalid phone number format: " + phone);
        }
    }

    std::string getValidatorType() const override {
        return "Phone Validator";
    }
};

class AgeValidator : public DataValidator {
public:
    void validate(const std::string& ageStr) const override {
        if (ageStr.empty()) {
            throw std::invalid_argument("Age cannot be empty");
        }

        try {
            int age = std::stoi(ageStr);
            if (age < 0 || age > 120) {
                throw std::invalid_argument("Age must be between 0 and 120");
            }
        }
        catch (const std::invalid_argument&) {
            throw std::invalid_argument("Invalid age value: " + ageStr);
        }
    }

    std::string getValidatorType() const override {
        return "Age Validator";
    }
};

void testValidator(DataValidator& validator, const std::string& testData) {
    try {
        std::cout << "Testing " << validator.getValidatorType()
            << " with data: " << testData << std::endl;
        validator.validate(testData);
        std::cout << "Validation passed!" << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Validation failed: " << e.what() << std::endl;
    }
}

int main() {
    EmailValidator emailValidator;
    PhoneValidator phoneValidator;
    AgeValidator ageValidator;

    testValidator(emailValidator, "test@example.com");
    testValidator(emailValidator, "invalid-email");

    testValidator(phoneValidator, "+1234567890");
    testValidator(phoneValidator, "not-a-phone");

    testValidator(ageValidator, "30");
    testValidator(ageValidator, "150");
    testValidator(ageValidator, "not-a-number");

    return 0;
}