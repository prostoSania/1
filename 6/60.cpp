#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;


class User {
protected:
    string username;
    string email;


    void validateBasicInfo() const {
        if (username.empty()) {
            throw invalid_argument("Username cannot be empty");
        }
        if (email.empty() || email.find('@') == string::npos) {
            throw invalid_argument("Invalid email address");
        }
    }

public:
    User(const string& username, const string& email)
        : username(username), email(email) {
    }

    virtual ~User() = default;


    virtual void updateProfile(const vector<pair<string, string>>& updates) = 0;


    virtual void printProfile() const = 0;

    string getUsername() const { return username; }
    string getEmail() const { return email; }
};


class RegularUser : public User {
private:
    string fullName;
    int age;
    string address;

public:
    RegularUser(const string& username, const string& email,
        const string& fullName, int age, const string& address)
        : User(username, email), fullName(fullName), age(age), address(address) {
    }

    void updateProfile(const vector<pair<string, string>>& updates) override {
        validateBasicInfo();

        for (const auto& [field, value] : updates) {
            if (field == "fullName") {
                if (value.empty()) throw invalid_argument("Full name cannot be empty");
                fullName = value;
            }
            else if (field == "age") {
                int newAge = stoi(value);
                if (newAge < 13 || newAge > 120) throw invalid_argument("Age must be between 13 and 120");
                age = newAge;
            }
            else if (field == "address") {
                address = value;
            }
            else if (field == "email") {
                if (value.find('@') == string::npos) throw invalid_argument("Invalid email address");
                email = value;
            }
            else {
                throw invalid_argument("Invalid field for RegularUser: " + field);
            }
        }
    }

    void printProfile() const override {
        cout << "Regular User Profile:\n"
            << "  Username: " << username << "\n"
            << "  Email: " << email << "\n"
            << "  Full Name: " << fullName << "\n"
            << "  Age: " << age << "\n"
            << "  Address: " << address << endl;
    }
};


class AdminUser : public User {
private:
    string department;
    int accessLevel;
    vector<string> permissions;

public:
    AdminUser(const string& username, const string& email,
        const string& department, int accessLevel, const vector<string>& permissions)
        : User(username, email), department(department),
        accessLevel(accessLevel), permissions(permissions) {
    }

    void updateProfile(const vector<pair<string, string>>& updates) override {
        validateBasicInfo();

        for (const auto& [field, value] : updates) {
            if (field == "department") {
                if (value.empty()) throw invalid_argument("Department cannot be empty");
                department = value;
            }
            else if (field == "accessLevel") {
                int newLevel = stoi(value);
                if (newLevel < 1 || newLevel > 5) throw invalid_argument("Access level must be 1-5");
                accessLevel = newLevel;
            }
            else if (field == "email") {
                if (value.find('@') == string::npos) throw invalid_argument("Invalid email address");
                email = value;
            }
            else if (field == "addPermission") {
                permissions.push_back(value);
            }
            else if (field == "removePermission") {
                auto it = find(permissions.begin(), permissions.end(), value);
                if (it == permissions.end()) {
                    throw invalid_argument("Permission not found: " + value);
                }
                permissions.erase(it);
            }
            else {
                throw invalid_argument("Invalid field for AdminUser: " + field);
            }
        }
    }

    void printProfile() const override {
        cout << "Admin User Profile:\n"
            << "  Username: " << username << "\n"
            << "  Email: " << email << "\n"
            << "  Department: " << department << "\n"
            << "  Access Level: " << accessLevel << "\n"
            << "  Permissions: ";
        for (const auto& perm : permissions) {
            cout << perm << ", ";
        }
        cout << endl;
    }
};


void testProfileUpdate(User& user, const vector<pair<string, string>>& updates) {
    try {
        cout << "\nBefore update:" << endl;
        user.printProfile();

        user.updateProfile(updates);

        cout << "After update:" << endl;
        user.printProfile();
    }
    catch (const exception& e) {
        cerr << "Update error: " << e.what() << endl;
    }
}

int main() {
    try {

        RegularUser regular("johndoe", "john@example.com",
            "John Doe", 30, "123 Main St");
        AdminUser admin("admin", "admin@company.com",
            "IT", 3, { "users.manage", "content.edit" });


        testProfileUpdate(regular, { {"fullName", "John H. Doe"}, {"age", "31"} });
        testProfileUpdate(admin, { {"department", "Security"}, {"addPermission", "system.config"} });


    }
    catch (const exception& e) {
        cerr << "Initialization error: " << e.what() << endl;
        return 1;
    }

    return 0;
}