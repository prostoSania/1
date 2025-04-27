#include <iostream>
#include <stdexcept>
#include <string>
#include <random>


class NetworkRequest {
protected:
    std::string url;
    int timeout;


    bool simulateNetworkError() const {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, 5);
        return dis(gen) == 1; 
    }

public:
    NetworkRequest(const std::string& url, int timeout = 5000)
        : url(url), timeout(timeout) {
        if (url.empty()) {
            throw std::invalid_argument("URL cannot be empty");
        }
        if (timeout <= 0) {
            throw std::invalid_argument("Timeout must be positive");
        }
    }

    virtual ~NetworkRequest() = default;


    virtual std::string send() {
        if (simulateNetworkError()) {
            throw std::runtime_error("Network error occurred");
        }
        return "Generic response from " + url;
    }

    virtual std::string getProtocol() const = 0;

    void displayInfo() const {
        std::cout << getProtocol() << " request to: " << url
            << " (timeout: " << timeout << "ms)" << std::endl;
    }
};


class HttpRequest : public NetworkRequest {
private:
    std::string method;

public:
    HttpRequest(const std::string& url, const std::string& method = "GET",
        int timeout = 5000)
        : NetworkRequest(url, timeout), method(method) {
        if (method != "GET" && method != "POST" && method != "PUT" && method != "DELETE") {
            throw std::invalid_argument("Invalid HTTP method");
        }
    }

    std::string send() override {
        try {

            NetworkRequest::send();

            std::cout << "Sending HTTP " << method << " request to " << url << std::endl;
            return "HTTP " + method + " response from " + url;
        }
        catch (const std::exception& e) {
            throw std::runtime_error("HTTP request failed: " + std::string(e.what()));
        }
    }

    std::string getProtocol() const override {
        return "HTTP";
    }
};

class FtpRequest : public NetworkRequest {
private:
    std::string ftpCommand;

public:
    FtpRequest(const std::string& url, const std::string& command = "GET",
        int timeout = 10000)
        : NetworkRequest(url, timeout), ftpCommand(command) {
        if (command != "GET" && command != "PUT" && command != "LIST" && command != "DELETE") {
            throw std::invalid_argument("Invalid FTP command");
        }
    }

    std::string send() override {
        try {

            NetworkRequest::send();

            std::cout << "Executing FTP " << ftpCommand << " command on " << url << std::endl;
            return "FTP " + ftpCommand + " response from " + url;
        }
        catch (const std::exception& e) {
            throw std::runtime_error("FTP operation failed: " + std::string(e.what()));
        }
    }

    std::string getProtocol() const override {
        return "FTP";
    }
};

int main() {
    try {

        HttpRequest httpReq("http://example.com/api/data", "GET");
        FtpRequest ftpReq("ftp://example.com/files/data.txt", "GET");

        httpReq.displayInfo();
        ftpReq.displayInfo();

        std::cout << "\nSending requests...\n";
        std::string httpResponse = httpReq.send();
        std::string ftpResponse = ftpReq.send();

        std::cout << "\nReceived responses:\n";
        std::cout << "HTTP: " << httpResponse << std::endl;
        std::cout << "FTP: " << ftpResponse << std::endl;


    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}