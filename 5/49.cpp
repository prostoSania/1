
#include <iostream>
#include <stdexcept>
#include <string>

// Базовый класс Task
class Task {
protected:
    bool initialized = false;
    std::string taskName;

    // Проверка инициализации задачи
    void checkInitialization() const {
        if (!initialized) {
            throw std::runtime_error("Task '" + taskName + "' is not initialized");
        }
    }

public:
    explicit Task(const std::string& name) : taskName(name) {}
    virtual ~Task() = default;

    // Виртуальная функция выполнения задачи
    virtual void execute() = 0;

    // Виртуальная функция инициализации
    virtual void initialize() {
        initialized = true;
    }

    std::string getName() const {
        return taskName;
    }
};

// Класс для задачи печати
class PrintTask : public Task {
private:
    std::string content;

public:
    PrintTask(const std::string& name, const std::string& content)
        : Task(name), content(content) {
    }

    void initialize() override {
        if (content.empty()) {
            throw std::invalid_argument("Print content cannot be empty");
        }
        Task::initialize();
    }

    void execute() override {
        checkInitialization();
        std::cout << "Printing: " << content << std::endl;
    }
};

// Класс для задачи отправки email
class EmailTask : public Task {
private:
    std::string recipient;
    std::string subject;
    std::string body;

public:
    EmailTask(const std::string& name, const std::string& recipient,
        const std::string& subject, const std::string& body)
        : Task(name), recipient(recipient), subject(subject), body(body) {
    }

    void initialize() override {
        if (recipient.empty()) {
            throw std::invalid_argument("Email recipient cannot be empty");
        }
        if (subject.empty()) {
            throw std::invalid_argument("Email subject cannot be empty");
        }
        Task::initialize();
    }

    void execute() override {
        checkInitialization();
        std::cout << "Sending email to: " << recipient << std::endl;
        std::cout << "Subject: " << subject << std::endl;
        std::cout << "Body: " << body << std::endl;
    }
};

// Класс для задачи работы с базой данных
class DatabaseTask : public Task {
private:
    std::string query;
    std::string connectionString;

public:
    DatabaseTask(const std::string& name, const std::string& query,
        const std::string& connectionString)
        : Task(name), query(query), connectionString(connectionString) {
    }

    void initialize() override {
        if (query.empty()) {
            throw std::invalid_argument("Database query cannot be empty");
        }
        if (connectionString.empty()) {
            throw std::invalid_argument("Connection string cannot be empty");
        }
        Task::initialize();
    }

    void execute() override {
        checkInitialization();
        std::cout << "Executing database query: " << query << std::endl;
        std::cout << "Using connection: " << connectionString << std::endl;
    }
};

int main() {
    try {
        // Создаем задачи
        PrintTask printTask("DocumentPrint", "Important document content");
        EmailTask emailTask("SendReport", "manager@company.com",
            "Monthly Report", "Here is the monthly report...");
        DatabaseTask dbTask("CleanupDB", "DELETE FROM temp_data WHERE date < NOW() - INTERVAL '30 days'",
            "host=localhost dbname=main user=admin");

        // Инициализируем задачи
        printTask.initialize();
        emailTask.initialize();
        dbTask.initialize();

        // Выполняем задачи
        std::cout << "Executing tasks:" << std::endl;
        printTask.execute();
        emailTask.execute();
        dbTask.execute();

        // Пример с неинициализированной задачей
        // DatabaseTask uninitializedTask("Test", "SELECT 1", "");
        // uninitializedTask.execute(); // Выбросит исключение

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}