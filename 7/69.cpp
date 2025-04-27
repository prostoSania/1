#include <iostream>
#include <stdexcept>
#include <string>
#include <ctime>
#include <cstdlib>

class EmailService {
protected:
    std::string sender;
    std::string recipient;
    std::string subject;
    std::string body;

    void validateEmail(const std::string& email) const {
        if (email.empty() || email.find('@') == std::string::npos) {
            throw std::invalid_argument("Invalid email address: " + email);
        }
    }

    void validateContent() const {
        if (subject.empty()) {
            throw std::invalid_argument("Email subject cannot be empty");
        }
        if (body.empty()) {
            throw std::invalid_argument("Email body cannot be empty");
        }
    }

public:
    EmailService(const std::string& from, const std::string& to,
        const std::string& subj, const std::string& content)
        : sender(from), recipient(to), subject(subj), body(content) {
        validateEmail(sender);
        validateEmail(recipient);
        validateContent();
    }

    virtual ~EmailService() = default;

    virtual void sendEmail() = 0;

    virtual std::string getServiceType() const = 0;
};

class SMTPService : public EmailService {
private:
    std::string smtpServer;
    int port;

public:
    SMTPService(const std::string& from, const std::string& to,
        const std::string& subj, const std::string& content,
        const std::string& server, int portNum)
        : EmailService(from, to, subj, content), smtpServer(server), port(portNum) {
    }

    void sendEmail() override {
        std::cout << "Connecting to SMTP server " << smtpServer
            << " on port " << port << "..." << std::endl;


        if (rand() % 100 < 15) {
            throw std::runtime_error("SMTP connection failed");
        }

        std::cout << "Email sent via SMTP from " << sender
            << " to " << recipient << std::endl;
    }

    std::string getServiceType() const override {
        return "SMTP Email Service";
    }
};

class APIService : public EmailService {
private:
    std::string apiEndpoint;
    std::string apiKey;

public:
    APIService(const std::string& from, const std::string& to,
        const std::string& subj, const std::string& content,
        const std::string& endpoint, const std::string& key)
        : EmailService(from, to, subj, content), apiEndpoint(endpoint), apiKey(key) {
    }

    void sendEmail() override {
        std::cout << "Calling email API at " << apiEndpoint << "..." << std::endl;


        if (rand() % 100 < 10) {
            throw std::runtime_error("API request failed");
        }

        std::cout << "Email sent via API from " << sender
            << " to " << recipient << std::endl;
    }

    std::string getServiceType() const override {
        return "API Email Service";
    }
};

class MockEmailService : public EmailService {
public:
    MockEmailService(const std::string& from, const std::string& to,
        const std::string& subj, const std::string& content)
        : EmailService(from, to, subj, content) {
    }

    void sendEmail() override {
        std::cout << "Mock email service (no actual sending)" << std::endl;
        std::cout << "From: " << sender << std::endl;
        std::cout << "To: " << recipient << std::endl;
        std::cout << "Subject: " << subject << std::endl;
        std::cout << "Body: " << body << std::endl;
    }

    std::string getServiceType() const override {
        return "Mock Email Service (testing)";
    }
};

void sendTestEmail(EmailService& service) {
    try {
        std::cout << "\nUsing " << service.getServiceType() << std::endl;
        service.sendEmail();
        std::cout << "Email sent successfully!" << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Failed to send email: " << e.what() << std::endl;
    }
}

int main() {
    srand(time(nullptr));

    try {
        SMTPService smtp("user@example.com", "recipient@domain.com",
            "Important message", "Hello via SMTP!",
            "smtp.example.com", 587);

        APIService api("user@example.com", "recipient@domain.com",
            "API message", "Hello via API!",
            "https://api.emailservice.com/send", "secret-key");

        MockEmailService mock("user@example.com", "recipient@domain.com",
            "Test message", "Hello in test mode!");

        sendTestEmail(smtp);
        sendTestEmail(api);
        sendTestEmail(mock);


    }
    catch (const std::exception& e) {
        std::cerr << "Initialization error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}