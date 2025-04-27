#include <iostream>
#include <string>
#include <stdexcept>

// Базовый класс Session
class Session {
protected:
    bool active;
    std::string sessionId;

public:
    // Конструктор Session
    Session(const std::string& sessionId) : active(false), sessionId(sessionId) {
        if (sessionId.empty()) {
            throw std::invalid_argument("Идентификатор сессии не может быть пустым.");
        }
    }

    // Виртуальная функция startSession()
    virtual void startSession() {
        if (active) {
            throw std::runtime_error("Невозможно начать уже активную сессию.");
        }
        std::cout << "Запуск базовой сессии с ID: " << sessionId << std::endl;
        active = true;
    }

    // Виртуальный деструктор
    virtual ~Session() {}

    bool isActive() const {
        return active;
    }

    std::string getSessionId() const {
        return sessionId;
    }
};

// Производный класс UserSession
class UserSession : public Session {
private:
    std::string userId;

public:
    // Конструктор UserSession
    UserSession(const std::string& sessionId, const std::string& userId) : Session(sessionId), userId(userId) {
        if (userId.empty()) {
            throw std::invalid_argument("Идентификатор пользователя не может быть пустым.");
        }
    }

    // Переопределение функции startSession()
    void startSession() override {
        if (isActive()) {
            throw std::runtime_error("Невозможно начать уже активную сессию пользователя.");
        }
        std::cout << "Проверка прав пользователя..." << std::endl;
        Session::startSession(); // Сначала вызываем базовый startSession()
        std::cout << "Сессия пользователя с ID " << userId << " запущена." << std::endl;
    }
};

// Производный класс AdminSession
class AdminSession : public Session {
private:
    std::string adminId;
    std::string role;

public:
    // Конструктор AdminSession
    AdminSession(const std::string& sessionId, const std::string& adminId, const std::string& role)
        : Session(sessionId), adminId(adminId), role(role) {
        if (adminId.empty()) {
            throw std::invalid_argument("Идентификатор администратора не может быть пустым.");
        }
        if (role.empty()) {
            throw std::invalid_argument("Роль администратора не может быть пустой.");
        }
    }

    // Переопределение функции startSession()
    void startSession() override {
        if (isActive()) {
            throw std::runtime_error("Невозможно начать уже активную сессию администратора.");
        }
        std::cout << "Проверка прав администратора с ролью " << role << "..." << std::endl;
        Session::startSession(); // Сначала вызываем базовый startSession()
        std::cout << "Сессия администратора с ID " << adminId << " запущена." << std::endl;
    }
};

int main() {
    try {
        UserSession userSession("session123", "user456");
        userSession.startSession();

        AdminSession adminSession("adminSession", "admin789", "СуперАдмин");
        adminSession.startSession();

        // Попытка запустить уже запущенную сессию
        userSession.startSession(); // Выбросит исключение

    } catch (const std::runtime_error& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Общая ошибка: " << e.what() << std::endl;
    }

    return 0;
}