#include <iostream>
#include <stdexcept>
#include <string>
#include <map>
#include <fstream>

class UserProfile {
protected:
    std::string username;
    std::map<std::string, std::string> profileData;

    virtual void validateBeforeSave() const {
        if (username.empty()) {
            throw std::invalid_argument("Username cannot be empty");
        }
    }

public:
    explicit UserProfile(const std::string& name) : username(name) {}
    virtual ~UserProfile() = default;

    virtual void save() = 0;
    virtual std::string getProfileType() const = 0;

    void setProfileData(const std::string& key, const std::string& value) {
        profileData[key] = value;
    }
};

class AdminProfile : public UserProfile {
private:
    int accessLevel;

    void validateBeforeSave() const override {
        UserProfile::validateBeforeSave();
        if (accessLevel < 1 || accessLevel > 5) {
            throw std::invalid_argument("Access level must be between 1 and 5");
        }
    }

public:
    AdminProfile(const std::string& name, int level)
        : UserProfile(name), accessLevel(level) {
    }

    void save() override {
        validateBeforeSave();

        std::ofstream file("admin_" + username + ".profile");
        if (!file.is_open()) {
            throw std::runtime_error("Failed to create admin profile file");
        }

        file << "AccessLevel: " << accessLevel << "\n";
        for (const auto& [key, value] : profileData) {
            file << key << ": " << value << "\n";
        }

        if (file.fail()) {
            throw std::runtime_error("Error writing admin profile data");
        }
    }

    std::string getProfileType() const override {
        return "Admin Profile";
    }
};

class RegularProfile : public UserProfile {
private:
    std::string email;

    void validateBeforeSave() const override {
        UserProfile::validateBeforeSave();
        if (email.empty() || email.find('@') == std::string::npos) {
            throw std::invalid_argument("Invalid email address");
        }
    }

public:
    RegularProfile(const std::string& name, const std::string& email)
        : UserProfile(name), email(email) {
    }

    void save() override {
        validateBeforeSave();

        std::ofstream file("user_" + username + ".profile");
        if (!file.is_open()) {
            throw std::runtime_error("Failed to create user profile file");
        }

        file << "Email: " << email << "\n";
        for (const auto& [key, value] : profileData) {
            file << key << ": " << value << "\n";
        }

        if (file.fail()) {
            throw std::runtime_error("Error writing user profile data");
        }
    }

    std::string getProfileType() const override {
        return "Regular Profile";
    }
};

void saveUserProfile(UserProfile& profile) {
    try {
        std::cout << "Saving " << profile.getProfileType() << " for "
            << profile.getProfileType() << std::endl;
        profile.save();
        std::cout << "Profile saved successfully!" << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Save failed: " << e.what() << std::endl;
    }
}

int main() {
    try {
        AdminProfile admin("admin1", 3);
        admin.setProfileData("Department", "IT");
        admin.setProfileData("Phone", "123-456-7890");

        RegularProfile user("user1", "user1@example.com");
        user.setProfileData("Age", "30");
        user.setProfileData("Address", "123 Main St");

        saveUserProfile(admin);
        saveUserProfile(user);



    }
    catch (const std::exception& e) {
        std::cerr << "Profile creation error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}