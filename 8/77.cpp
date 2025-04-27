#include <iostream>
#include <stdexcept>
#include <string>
#include <ctime>
#include <cstdlib>

class NotificationService {
protected:
    std::string recipient;
    std::string message;
    std::time_t timestamp;

    void validateRecipient() const {
        if (recipient.empty()) {
            throw std::invalid_argument("Recipient cannot be empty");
        }
    }

    void validateMessage() const {
        if (message.empty()) {
            throw std::invalid_argument("Message cannot be empty");
        }
        if (message.length() > 1000) {
            throw std::invalid_argument("Message too long");
        }
    }

public:
    NotificationService(const std::string& to, const std::string& msg)
        : recipient(to), message(msg), timestamp(std::time(nullptr)) {
    }

    virtual ~NotificationService() = default;

    virtual void sendNotification() = 0;

    virtual std::string getServiceType() const = 0;

    void printNotificationInfo() const {
        std::cout << "[" << std::put_time(std::localtime(&timestamp), "%F %T") << "] "
            << getServiceType() << " to: " << recipient << std::endl;
    }
};

class EmailNotificationService : public NotificationService {
private:
    std::string subject;
    std::string from;

    void validateEmail() const {
        if (recipient.find('@') == std::string::npos) {
            throw std::invalid_argument("Invalid email address");
        }
    }

public:
    EmailNotificationService(const std::string& to, const std::string& msg,
        const std::string& subj, const std::string& fromAddr)
        : NotificationService(to, msg), subject(subj), from(fromAddr) {
    }

    void sendNotification() override {
        validateRecipient();
        validateMessage();
        validateEmail();

        std::cout << "Sending email from " << from << " to " << recipient << std::endl;
        std::cout << "Subject: " << subject << std::endl;
        std::cout << "Message: " << message << std::endl;


        if (rand() % 10 == 0) {
            throw std::runtime_error("Failed to send email");
        }
    }

    std::string getServiceType() const override {
        return "Email Notification";
    }
};

class SMSNotificationService : public NotificationService {
private:
    void validatePhoneNumber() const {
        if (recipient.length() < 10) {
            throw std::invalid_argument("Invalid phone number");
        }
    }

public:
    SMSNotificationService(const std::string& to, const std::string& msg)
        : NotificationService(to, msg) {
    }

    void sendNotification() override {
        validateRecipient();
        validateMessage();
        validatePhoneNumber();

        std::cout << "Sending SMS to " << recipient << std::endl;
        std::cout << "Message: " << message << std::endl;


        if (rand() % 100 < 15) {
            throw std::runtime_error("Failed to send SMS");
        }
    }

    std::string getServiceType() const override {
        return "SMS Notification";
    }
};

class PushNotificationService : public NotificationService {
private:
    std::string deviceId;

    void validateDeviceId() const {
        if (deviceId.empty() || deviceId.length() != 32) {
            throw std::invalid_argument("Invalid device ID");
        }
    }

public:
    PushNotificationService(const std::string& devId, const std::string& msg)
        : NotificationService(devId, msg), deviceId(devId) {
    }

    void sendNotification() override {
        validateRecipient();
        validateMessage();
        validateDeviceId();

        std::cout << "Sending push to device " << deviceId << std::endl;
        std::cout << "Message: " << message << std::endl;


        if (rand() % 100 < 5) {
            throw std::runtime_error("Failed to send push notification");
        }
    }

    std::string getServiceType() const override {
        return "Push Notification";
    }
};

void sendTestNotification(NotificationService& service) {
    try {
        service.printNotificationInfo();
        service.sendNotification();
        std::cout << "Notification sent successfully!" << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Notification failed: " << e.what() << std::endl;
    }
}

int main() {
    srand(time(nullptr));

    try {
        EmailNotificationService email("user@example.com",
            "Hello via email!",
            "Important Notification",
            "system@example.com");

        SMSNotificationService sms("+1234567890",
            "Hello via SMS!");

        PushNotificationService push("abc123def456ghi789jkl012mno345pqr",
            "Hello via push!");

        sendTestNotification(email);
        sendTestNotification(sms);
        sendTestNotification(push);



    }
    catch (const std::exception& e) {
        std::cerr << "Initialization error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}