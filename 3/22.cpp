#include <iostream>
#include <string>
#include <stdexcept>

// Базовый класс Database
class Database {
protected:
    std::string connectionString;

public:
    // Конструктор Database
    Database(const std::string& connectionString) : connectionString(connectionString) {}

    // Виртуальная функция connect()
    virtual void connect() const {
        std::cout << "Подключение к базе данных с помощью строки подключения: " << connectionString << std::endl;
        // Базовая реализация - просто вывод сообщения (в реальном коде здесь было бы подключение)
    }

    // Виртуальный деструктор
    virtual ~Database() {}

    std::string getConnectionString() const {
        return connectionString;
    }
};

// Производный класс MySQLDatabase
class MySQLDatabase : public Database {
private:
    std::string username;
    std::string password;

public:
    // Конструктор MySQLDatabase
    MySQLDatabase(const std::string& connectionString, const std::string& username, const std::string& password)
        : Database(connectionString), username(username), password(password) {}

    // Переопределение функции connect()
    void connect() const override {
        Database::connect(); // Сначала вызываем базовый connect()

        // Дополнительная логика для подключения к MySQL
        if (username.empty() || password.empty()) {
            throw std::runtime_error("Не указаны имя пользователя или пароль для MySQL.");
        }

        std::cout << "Подключение к MySQL с именем пользователя: " << username << std::endl;
        // Реальный код подключения к MySQL здесь
        // ...
        // В случае ошибки подключения - выбрасываем исключение
        // throw std::runtime_error("Не удалось подключиться к MySQL.");
    }
};

// Производный класс SQLiteDatabase
class SQLiteDatabase : public Database {
public:
    // Конструктор SQLiteDatabase
    SQLiteDatabase(const std::string& connectionString) : Database(connectionString) {}

    // Переопределение функции connect()
    void connect() const override {
        Database::connect(); // Сначала вызываем базовый connect()

        // Дополнительная логика для подключения к SQLite
        if (connectionString.empty()) {
            throw std::runtime_error("Пустая строка подключения для SQLite.");
        }

        std::cout << "Подключение к SQLite с файлом базы данных: " << connectionString << std::endl;
        // Реальный код подключения к SQLite здесь
        // ...
        // В случае ошибки подключения - выбрасываем исключение
        // throw std::runtime_error("Не удалось подключиться к SQLite.");
    }
};

int main() {
    try {
        MySQLDatabase mySQLDatabase("localhost", "admin", "password");
        mySQLDatabase.connect();

        SQLiteDatabase sqliteDatabase("mydatabase.db");
        sqliteDatabase.connect();

        // Попытка подключения к MySQL без имени пользователя и пароля
        MySQLDatabase invalidMySQL("localhost", "", ""); // Выбросит исключение
        invalidMySQL.connect();

    } catch (const std::runtime_error& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Общая ошибка: " << e.what() << std::endl;
    }

    return 0;
}