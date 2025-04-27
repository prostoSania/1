#include <iostream>
#include <string>
#include <stdexcept>

// Базовый класс UserProfile
class UserProfile {
protected:
    std::string username;

public:
    // Конструктор UserProfile
    UserProfile(const std::string& username) : username(username) {
        if (username.empty()) {
            throw std::invalid_argument("Имя пользователя не может быть пустым.");
        }
    }

    // Виртуальная функция updateProfile()
    virtual void updateProfile(const std::string& newUsername) {
        if (newUsername.empty()) {
            throw std::invalid_argument("Новое имя пользователя не может быть пустым.");
        }
        std::cout << "Обновление профиля пользователя: " << username << " на " << newUsername << std::endl;
        username = newUsername;
    }

    // Виртуальный деструктор
    virtual ~UserProfile() {}

    std::string getUsername() const {
        return username;
    }
};

// Производный класс AdminProfile
class AdminProfile : public UserProfile {
private:
    std::string role;

public:
    // Конструктор AdminProfile
    AdminProfile(const std::string& username, const std::string& role) : UserProfile(username), role(role) {
        if (role.empty()) {
            throw std::invalid_argument("Роль администратора не может быть пустой.");
        }
    }

    // Переопределение функции updateProfile()
    void updateProfile(const std::string& newUsername) override {
        // Дополнительная логика для обновления профиля администратора (например, проверка прав)
        std::cout << "Проверка прав администратора на обновление профиля..." << std::endl;
        UserProfile::updateProfile(newUsername); // Сначала вызываем базовый updateProfile()
        std::cout << "Роль администратора осталась: " << role << std::endl;
    }
};

// Производный класс GuestProfile
class GuestProfile : public UserProfile {
public:
    // Конструктор GuestProfile
    GuestProfile(const std::string& username) : UserProfile(username) {}

    // Переопределение функции updateProfile() - запрещаем обновление профиля гостя
    void updateProfile(const std::string& newUsername) override {
        throw std::runtime_error("Невозможно обновить профиль гостя.");
    }
};

int main() {
    try {
        AdminProfile admin("admin123", "СуперАдмин");
        admin.updateProfile("newAdmin");

        GuestProfile guest("guest456");
        // guest.updateProfile("newGuest"); // Выбросит исключение

        // Попытка создать профиль с пустым именем пользователя
        UserProfile invalidUser(""); // Выбросит исключение

    } catch (const std::runtime_error& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Общая ошибка: " << e.what() << std::endl;
    }

    return 0;
}