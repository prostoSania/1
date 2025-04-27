#include <iostream>
#include <stdexcept>
#include <string>
#include <chrono>
#include <ctime>

class Session {
protected:
    std::string sessionId;
    bool isActive;
    std::chrono::system_clock::time_point startTime;


    std::string generateSessionId() const {
        return std::to_string(std::time(nullptr)) + "-" + std::to_string(rand() % 1000);
    }

public:
    Session() : isActive(false), sessionId("") {}
    virtual ~Session() = default;


    virtual void start() {
        if (isActive) {
            throw std::runtime_error("Session is already active");
        }
        isActive = true;
        sessionId = generateSessionId();
        startTime = std::chrono::system_clock::now();
    }


    virtual void stop() {
        if (!isActive) {
            throw std::runtime_error("No active session to stop");
        }
        isActive = false;
        sessionId = "";
    }


    virtual std::string getInfo() const {
        if (!isActive) {
            return "Session is not active";
        }

        auto duration = std::chrono::system_clock::now() - startTime;
        auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration).count();

        return "Session ID: " + sessionId +
            ", Active for: " + std::to_string(seconds) + " seconds";
    }


    bool isSessionActive() const {
        return isActive;
    }
};

class UserSession : public Session {
private:
    std::string username;
    int maxDuration; 

public:
    UserSession(const std::string& username, int maxDuration = 30)
        : username(username), maxDuration(maxDuration) {
    }

    void start() override {
        if (username.empty()) {
            throw std::invalid_argument("Username cannot be empty");
        }
        Session::start();
        std::cout << "User session started for: " << username << std::endl;
    }

    void stop() override {
        Session::stop();
        std::cout << "User session ended for: " << username << std::endl;
    }

    std::string getInfo() const override {
        std::string info = Session::getInfo();
        if (isSessionActive()) {
            return "User " + username + " - " + info +
                ", Max duration: " + std::to_string(maxDuration) + " minutes";
        }
        return info;
    }


    bool isExpired() const {
        if (!isActive) return false;

        auto duration = std::chrono::system_clock::now() - startTime;
        auto minutes = std::chrono::duration_cast<std::chrono::minutes>(duration).count();

        return minutes > maxDuration;
    }
};

class AdminSession : public Session {
private:
    std::string adminId;
    int privilegeLevel;

public:
    AdminSession(const std::string& adminId, int privilegeLevel = 1)
        : adminId(adminId), privilegeLevel(privilegeLevel) {
    }

    void start() override {
        if (adminId.empty()) {
            throw std::invalid_argument("Admin ID cannot be empty");
        }
        if (privilegeLevel < 1 || privilegeLevel > 3) {
            throw std::invalid_argument("Invalid privilege level (1-3)");
        }
        Session::start();
        std::cout << "Admin session started (Level " << privilegeLevel << ")" << std::endl;
    }

    void stop() override {
        Session::stop();
        std::cout << "Admin session ended" << std::endl;
    }

    std::string getInfo() const override {
        std::string info = Session::getInfo();
        if (isSessionActive()) {
            return "Admin " + adminId + " (Level " + std::to_string(privilegeLevel) +
                ") - " + info;
        }
        return info;
    }

  
    void emergencyStop() {
        std::cout << "EMERGENCY STOP for admin session" << std::endl;
        Session::stop();
    }
};


void testSession(Session& session) {
    try {
        std::cout << "\nTesting session..." << std::endl;
        session.start();
        std::cout << session.getInfo() << std::endl;

        std::cout << "Performing operations..." << std::endl;


        session.stop();
    }
    catch (const std::exception& e) {
        std::cerr << "Session error: " << e.what() << std::endl;
    }
}

int main() {
    try {

        UserSession userSession("john_doe");
        AdminSession adminSession("admin1", 2);


        testSession(userSession);
        testSession(adminSession);


        AdminSession admin("superadmin", 3);
        admin.start();
        std::cout << admin.getInfo() << std::endl;
        admin.emergencyStop();



    }
    catch (const std::exception& e) {
        std::cerr << "Initialization error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}