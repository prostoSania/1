#include <iostream>
#include <stdexcept>
#include <string>
#include <chrono>
#include <thread>

class TaskManager {
public:
    virtual ~TaskManager() = default;

    virtual void runTask() = 0;

    virtual std::string getTaskType() const = 0;
};

class ScheduledTask : public TaskManager {
private:
    std::string taskName;
    std::chrono::seconds delay;
    bool executed;

public:
    ScheduledTask(const std::string& name, int seconds)
        : taskName(name), delay(seconds), executed(false) {
    }

    void runTask() override {
        if (executed) {
            throw std::runtime_error("Task already executed: " + taskName);
        }

        std::cout << "Scheduling task '" << taskName << "' in " << delay.count() << " seconds..." << std::endl;
        std::this_thread::sleep_for(delay);

        std::cout << "Executing scheduled task: " << taskName << std::endl;
        executed = true;

        if (taskName.empty()) {
            throw std::runtime_error("Task name cannot be empty");
        }
    }

    std::string getTaskType() const override {
        return "Scheduled Task";
    }
};

class ImmediateTask : public TaskManager {
private:
    std::string taskName;
    bool executed;

public:
    ImmediateTask(const std::string& name)
        : taskName(name), executed(false) {
    }

    void runTask() override {
        if (executed) {
            throw std::runtime_error("Task already executed: " + taskName);
        }

        std::cout << "Executing immediate task: " << taskName << std::endl;
        executed = true;

        if (taskName.empty()) {
            throw std::runtime_error("Task name cannot be empty");
        }
    }

    std::string getTaskType() const override {
        return "Immediate Task";
    }
};

void executeTask(TaskManager& task) {
    try {
        std::cout << "\nRunning " << task.getTaskType() << std::endl;
        task.runTask();
        std::cout << "Task completed successfully" << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Task failed: " << e.what() << std::endl;
    }
}

int main() {
    try {
        ScheduledTask scheduled("Database Backup", 3);
        ImmediateTask immediate("System Check");

        executeTask(scheduled);
        executeTask(immediate);

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}