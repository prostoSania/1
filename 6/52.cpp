#include <iostream>
#include <string>
#include <stdexcept>
#include <memory>

class Database {
protected:
    std::string connectionString;
    bool isConnected = false;

    void checkConnection() const {
        if (!isConnected) {
            throw std::runtime_error("Database is not connected");
        }
    }

public:
    explicit Database(const std::string& connStr) : connectionString(connStr) {}
    virtual ~Database() = default;

    virtual void connect() = 0;

    virtual void disconnect() = 0;

    virtual std::string query(const std::string& sql) = 0;

    virtual std::string getInfo() const = 0;
};


class MySQLDatabase : public Database {
public:
    explicit MySQLDatabase(const std::string& connStr) : Database(connStr) {}

    void connect() override {
        std::cout << "Connecting to MySQL database: " << connectionString << std::endl;

        isConnected = true;
    }

    void disconnect() override {
        std::cout << "Disconnecting from MySQL database" << std::endl;

        isConnected = false;
    }

    std::string query(const std::string& sql) override {
        checkConnection();

        if (sql.empty()) {
            throw std::invalid_argument("SQL query cannot be empty");
        }

        if (sql.find("DROP TABLE") != std::string::npos) {
            throw std::runtime_error("MySQL error: insufficient privileges for DROP TABLE");
        }

        std::cout << "Executing MySQL query: " << sql << std::endl;
        return "MySQL results for: " + sql;
    }

    std::string getInfo() const override {
        return "MySQL Database [" + connectionString + "]";
    }
};

class SQLiteDatabase : public Database {
private:
    std::string dbFilePath;

public:
    explicit SQLiteDatabase(const std::string& filePath)
        : Database("file:" + filePath), dbFilePath(filePath) {
    }

    void connect() override {
        std::cout << "Opening SQLite database file: " << dbFilePath << std::endl;

        isConnected = true;
    }

    void disconnect() override {
        std::cout << "Closing SQLite database file" << std::endl;

        isConnected = false;
    }

    std::string query(const std::string& sql) override {
        checkConnection();

        if (sql.empty()) {
            throw std::invalid_argument("SQL query cannot be empty");
        }


        if (sql.find("ATTACH DATABASE") != std::string::npos) {
            throw std::runtime_error("SQLite error: cannot attach database - file not found");
        }

        std::cout << "Executing SQLite query: " << sql << std::endl;
        return "SQLite results for: " + sql;
    }

    std::string getInfo() const override {
        return "SQLite Database [" + dbFilePath + "]";
    }
};

int main() {
    try {

        MySQLDatabase mysql("mysql://user:password@localhost/mydb");
        SQLiteDatabase sqlite("mydatabase.db");


        mysql.connect();
        sqlite.connect();


        std::cout << "\nMySQL query result:\n"
            << mysql.query("SELECT * FROM users") << std::endl;

        std::cout << "\nSQLite query result:\n"
            << sqlite.query("SELECT * FROM products") << std::endl;


        mysql.disconnect();
        sqlite.disconnect();

    }
    catch (const std::exception& e) {
        std::cerr << "Database error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}