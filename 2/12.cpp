#include <iostream>
#include <string>
#include <stdexcept>


class User {
protected:
    std::string username;
    std::string password;

public:
    
    User(const std::string& username, const std::string& password) : username(username), password(password) {}

    
    virtual void login(const std::string& enteredPassword) const {
        if (enteredPassword != password) {
            throw std::runtime_error("Неверный пароль.");
        }
        std::cout << "Пользователь " << username << " успешно вошел в систему." << std::endl;
    }

    
    virtual ~User() {}

    std::string getUsername() const {
        return username;
    }
};


class AdminUser : public User {
private:
    std::string adminRole;

public:
    
    AdminUser(const std::string& username, const std::string& password, const std::string& adminRole)
        : User(username, password), adminRole(adminRole) {}

    void login(const std::string& enteredPassword) const override {
        User::login(enteredPassword); /

        if (adminRole != "superuser") {
            std::cout << "Внимание: Роль администратора не 'superuser'." << std::endl;
        }

        std::cout << "Администратор " << username << " успешно вошел в систему с ролью " << adminRole << "." << std::endl;
    }

    std::string getAdminRole() const {
        return adminRole;
    }
};


class RegularUser : public User {
private:
    std::string userGroup;

public:
    
    RegularUser(const std::string& username, const std::string& password, const std::string& userGroup)
        : User(username, password), userGroup(userGroup) {}

    
    void login(const std::string& enteredPassword) const override {
        User::login(enteredPassword); 
        std::cout << "Обычный пользователь " << username << " из группы " << userGroup << " успешно вошел в систему." << std::endl;
    }

    std::string getUserGroup() const {
        return userGroup;
    }
};

int main() {
    try {
        AdminUser admin("admin", "adminpass", "superuser");
        admin.login("adminpass");

        RegularUser user("user1", "userpass", "users");
        user.login("userpass");

        
        RegularUser invalidUser("user2", "wrongpass", "guests");
        invalidUser.login("incorrect"); 

    } catch (const std::runtime_error& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Общая ошибка: " << e.what() << std::endl;
    }

    return 0;
}