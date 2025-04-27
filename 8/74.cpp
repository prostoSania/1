#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_map>

class User {
protected:
    std::string username;
    std::string hashedPassword;

    virtual void validateCredentials(const std::string& inputUsername,
        const std::string& inputPassword) const {
        if (inputUsername.empty() || inputPassword.empty()) {
            throw std::invalid_argument("Username and password cannot be empty");
        }
    }

public:
    User(const std::string& name, const std::string& password)
        : username(name), hashedPassword(hashPassword(password)) {
    }

    virtual ~User() = default;

    virtual bool authenticate(const std::string& inputUsername,
        const std::string& inputPassword) const = 0;

    virtual std::string getUserType() const = 0;

    static std::string hashPassword(const std::string& password) {

        size_t hash = 0;
        for (char c : password) {
            hash = (hash * 31) + c;
        }
        return std::to_string(hash);
    }
};

class AdminUser : public User {
private:
    std::string adminSecretKey;

    void validateCredentials(const std::string& inputUsername,
        const std::string& inputPassword) const override {
        User::validateCredentials(inputUsername, inputPassword);

        if (inputPassword.length() < 12) {
            throw std::invalid_argument("Admin password must be at least 12 characters");
        }
    }

public:
    AdminUser(const std::string& name, const std::string& password,
        const std::string& secretKey)
        : User(name, password), adminSecretKey(secretKey) {
    }

    bool authenticate(const std::string& inputUsername,
        const std::string& inputPassword) const override {
        validateCredentials(inputUsername, inputPassword);

        if (inputUsername != username) {
            throw std::runtime_error("Invalid admin username");
        }

        if (hashPassword(inputPassword) != hashedPassword) {
            throw std::runtime_error("Invalid admin password");
        }

        std::cout << "Admin authentication successful" << std::endl;
        return true;
    }

    std::string getUserType() const override {
        return "Admin User";
    }
};

class RegularUser : public User {
private:
    static const std::unordered_map<std::string, std::string> userDatabase;

    void validateCredentials(const std::string& inputUsername,
        const std::string& inputPassword) const override {
        User::validateCredentials(inputUsername, inputPassword);

        if (inputPassword.length() < 8) {
            throw std::invalid_argument("Password must be at least 8 characters");
        }
    }

public:
    RegularUser(const std::string& name, const std::string& password)
        : User(name, password) {
    }

    bool authenticate(const std::string& inputUsername,
        const std::string& inputPassword) const override {
        validateCredentials(inputUsername, inputPassword);

        if (userDatabase.find(inputUsername) == userDatabase.end()) {
            throw std::runtime_error("User not found");
        }

        if (hashPassword(inputPassword) != userDatabase.at(inputUsername)) {
            throw std::runtime_error("Invalid password");
        }

        std::cout << "User authentication successful" << std::endl;
        return true;
    }

    std::string getUserType() const override {
        return "Regular User";
    }
};


const std::unordered_map<std::string, std::string> RegularUser::userDatabase = {
    {"user1", "12345678"}, 
    {"user2", "23456789"}  
};

void authenticateUser(const User& user, const std::string& username,
    const std::string& password) {
    try {
        std::cout << "Authenticating " << user.getUserType() << "... ";
        if (user.authenticate(username, password)) {
            std::cout << "Access granted!" << std::endl;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Authentication failed: " << e.what() << std::endl;
    }
}

int main() {
    try {
        AdminUser admin("admin1", "securePassword123", "SECRET_KEY");
        RegularUser user1("user1", "password1");
        RegularUser user2("user3", "password3"); 

        authenticateUser(admin, "admin1", "securePassword123");
        authenticateUser(user1, "user1", "password1");
        authenticateUser(user2, "user3", "wrongPassword");



    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}