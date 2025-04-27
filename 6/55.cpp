#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

class Notification {
protected:
    std::string recipient;
    std::string message;

    void validate() const {
        if (recipient.empty()) {
            throw std::invalid_argument("Recipient cannot be empty");
        }
        if (message.empty()) {
            throw std::invalid_argument("Message cannot be empty");
        }
    }

public:
    Notification(const std::string& recipient, const std::string& message)
        : recipient(recipient), message(message) {
    }

    virtual ~Notification() = default;

    virtual void send() = 0;

    virtual std::string getType() const = 0;

    void displayInfo() const {
        std::cout << getType() << " notification to: " << recipient
            << "\nMessage: " << message << std::endl;
    }
};


class EmailNotification : public Notification {
private:
    std::string subject;

public:
    EmailNotification(const std::string& recipient,
        const std::string& subject,
        const std::string& message)
        : Notification(recipient, message), subject(subject) {
    }

    void send() override {
        validate();

        if (recipient.find('@') == std::string::npos) {
            throw std::runtime_error("Invalid email address: " + recipient);
        }

        if (subject.empty()) {
            throw std::runtime_error("Email subject cannot be empty");
        }

        std::cout << "Sending email to: " << recipient << std::endl;
        std::cout << "Subject: " << subject << std::endl;
        std::cout << "Message: " << message << std::endl;


        if (rand() % 10 == 0) {
            throw std::runtime_error("Failed to send email to " + recipient);
        }
    }

    std::string getType() const override {
        return "Email";
    }
};


class SMSNotification : public Notification {
public:
    SMSNotification(const std::string& phoneNumber,
        const std::string& message)
        : Notification(phoneNumber, message) {
    }

    void send() override {
        validate();


        for (char c : recipient) {
            if (!isdigit(c)) {
                throw std::runtime_error("Invalid phone number: " + recipient);
            }
        }


        if (message.length() > 160) {
            throw std::runtime_error("SMS message too long (max 160 chars)");
        }

        std::cout << "Sending SMS to: " << recipient << std::endl;
        std::cout << "Message: " << message << std::endl;


        if (rand() % 20 == 0) {
            throw std::runtime_error("Failed to send SMS to " + recipient);
        }
    }

    std::string getType() const override {
        return "SMS";
    }
};


class PushNotification : public Notification {
private:
    std::string deviceId;

public:
    PushNotification(const std::string& deviceId,
        const std::string& message)
        : Notification(deviceId, message), deviceId(deviceId) {
    }

    void send() override {
        validate();


        if (deviceId.length() != 32) {
            throw std::runtime_error("Invalid device ID (must be 32 chars)");
        }

        std::cout << "Sending push to device: " << deviceId << std::endl;
        std::cout << "Message: " << message << std::endl;


        if (rand() % 7 == 0) {
            throw std::runtime_error("Failed to send push to device " + deviceId);
        }
    }

    std::string getType() const override {
        return "Push";
    }
};

void testNotification(Notification& notification) {
    try {
        std::cout << "\nTesting " << notification.getType() << " notification..." << std::endl;
        notification.displayInfo();
        notification.send();
        std::cout << "Notification sent successfully!" << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error sending notification: " << e.what() << std::endl;
    }
}

int main() {

    srand(static_cast<unsigned int>(time(nullptr)));

    try {

        EmailNotification email("user@example.com", "Important Update", "Hello, this is an email notification");
        SMSNotification sms("1234567890", "This is an SMS notification");
        PushNotification push("abc123def456ghi789jkl012mno345pqr", "You have a new push notification");


        testNotification(email);
        testNotification(sms);
        testNotification(push);

    }
    catch (const std::exception& e) {
        std::cerr << "Initialization error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}